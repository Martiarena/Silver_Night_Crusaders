//Script for enemies bosses
//Especially ones with slaves

#include "data/scripts/library/spawn.h"
#include "data/scripts/library/target.h"
#include "data/scripts/library/basic.h"

void layer(int layer)
{// Set's enemy's layer
    void self = getlocalvar("self");
    changeentityproperty(self, "setlayer", layer);
}

void suicide2()
{ // Suicide by damaging self!!
    void self = getlocalvar("self");

    damageentity(self, self, 1000, 0, openborconstant("ATK_NORMAL2"));
}

void killgun(int Num, int Flag)
{ // Kill bound gun based on number
    void self = getlocalvar("self");
    void Gun = getentityvar(self, Num);

    if(Gun!=NULL()){
      bindentity(Gun, NULL());
      if(Flag==1){
        damageentity(Gun, self, 1000, 0, openborconstant("ATK_NORMAL"));
      } else {
        killentity(Gun);
      }
    }
}

void givescore(int Add)
{// Gives score to players
    void P1 = getplayerproperty(0, "entity");
    void P2 = getplayerproperty(1, "entity");

    if(P1!=NULL()){
      int P1Score = getplayerproperty(0, "score");
      changeplayerproperty(0, "score", P1Score+Add);
    }

    if(P2!=NULL()){
      int P2Score = getplayerproperty(1, "score");
      changeplayerproperty(1, "score", P2Score+Add);
    }
}

void immunity(int Def)
{// Sets immunity to all used attacktypes
    void self = getlocalvar("self");
    int DId = openborconstant("ATK_NORMAL");

    changeentityproperty(self,"defense", DId, Def);

    if (Def == 0){ // Immunity?                  
      setentityvar(self, 7, 1);
    } else {
      setentityvar(self, 7, NULL());
    }
}

void spawnChainPoint(void vName, int Num, float fX, float fY, float fZ)
{	//Spawns chain point next to caller and set them as child.
	//
	//vName: Model name of entity to be spawned in.
	//fX: X location adjustment.
	//fY: Y location adjustment.
        //fZ: Z location adjustment.

	void self = getlocalvar("self"); //Get calling entity.
	void vSpawn; //Spawn object.
	
	vSpawn = spawn01(vName, fX, fY, fZ); //Spawn in entity.

        setentityvar(self, Num, vSpawn); // Stores spawned chain point for chain links
	changeentityproperty(vSpawn, "parent", self); //Set caller as parent.
    
	return vSpawn; //Return spawn.
}

void spawnChainLink(void vName, int Num, float Ratio, float fX, float fY, int Layer)
{	//Spawns chain link next to caller, set them as child, give it the other chain point and set chain ratio
	//
	//vName: Model name of entity to be spawned in.
	//fX: X location adjustment.
	//fY: Y location adjustment.
        //fZ: Z location adjustment.

	void self = getlocalvar("self"); //Get calling entity.
	void vSpawn; //Spawn object.
      void vCPoint = getentityvar(self, Num);
	
	vSpawn = spawn01(vName, fX, fY, 0); //Spawn in entity.

	changeentityproperty(vSpawn, "parent", self); //Set caller as parent
	changeentityproperty(vSpawn, "setlayer", Layer); //Set chain link's layer
      setentityvar(vSpawn, 0, vCPoint); // Gives chain point to chain link
      setentityvar(vSpawn, 2, Ratio); // Gives chain link its chain ratio
      setentityvar(vSpawn, 3, fX); // Gives chain link x distance
      setentityvar(vSpawn, 4, fY); // Gives chain link y distance
    
	return vSpawn; //Return spawn.
}

void spawnGun(void Name, float dx, float dy, float dz, int Num)
{ // Spawn gun, store it and bind it
   void self = getlocalvar("self");
   void Spawn;

   Spawn = spawn01(Name, dx, dy, 0);
   setentityvar(self, Num, Spawn); // Stores spawned gun to be killed later
   bindentity(Spawn, self, dx, dz, dy, 0, 0); // Bind spawned gun
}

void spawnMover(void Name, float dx, float dy, float dz, int Num)
{ // Spawn mover, store it and bind it
   void self = getlocalvar("self");
   int Aggro = getentityproperty(self,"aggression");
   void Spawn;

   Spawn = spawn01(Name, dx, dy, 0);
   changeentityproperty(Spawn, "aggression", Aggro);
   setentityvar(self, Num, Spawn); // Stores spawned gun to be killed later
   bindentity(self, Spawn, dx, dz, dy, 0, 0); // Bind self to spawned gun
}

void getxy()
{// Attain current x and y coordinate and store them in entity variables
    void self = getlocalvar("self");
    float x = getentityproperty(self,"x"); //Get entity's x coordinate
    float y = getentityproperty(self,"a"); //Get entity's a coordinate

    setentityvar(self, 5, x); // Stores x coordinate
    setentityvar(self, 6, y); // Stores y coordinate
}

void attack0(void Ani)
{// Attack interruption if there's player
    void self = getlocalvar("self");
    void target = findtarget(self); //Find player

    if(target!=NULL()){
      performattack(self, openborconstant(Ani)); //Attack!
    }
}

void attack1(int RxMin, int RxMax, int RyMin, int RyMax, void Ani)
{// Attack interruption with range check
    void self = getlocalvar("self");
    void target = findtarget(self); //Get nearest player
    float x = getentityproperty(self, "x");
    float y = getentityproperty(self, "a");
    int dir = getentityproperty(self, "direction");

    if(target!=NULL()){
      float Tx = getentityproperty(target, "x");
      float Ty = getentityproperty(target, "a");
      float Disx = Tx - x;
      float Disy = Ty - y;

      if( Disx >= RxMin && Disx <= RxMax && Disy >= RyMin && Disy <= RyMax && dir == 1) // Target within range on right facing?
      {
        performattack(self, openborconstant(Ani)); //Change the animation
      } else if( Disx >= -RxMax && Disx <= -RxMin && Disy >= RyMin && Disy <= RyMax && dir == 0) // Target within range on left facing?
      {
        performattack(self, openborconstant(Ani)); //Change the animation
      }
    }
}

void targetdashT(float Time, float dx, float dy)
{// Targetting opponent then dash
// Entity will reach opponent within specified time
// Time = specified time
// dx = x added distance
// dy = y added distance

    void self = getlocalvar("self");
    float Vx;
    float Vy;

    setlocalvar("T"+self, findtarget(self)); //Get nearest player

    void target = getlocalvar("T"+self);
    Vx = target1T(target, Time, dx, dy, "x", 1);
    Vy = target1T(target, Time, dx, dy, "y", 1);

    changeentityproperty(self, "velocity", Vx, 0, Vy); //Move towards target!
    setlocalvar("T"+self, NULL()); //Clears variable
}

void SltargetT(int Num, float Time, float dx, float dy)
{// Targetting slave before leaping or dashing.
// Num = Slave number
// Time = specified time
// dx = x added distance
// dy = y added distance

    void self = getlocalvar("self");
    void Slave = getentityvar(self, Num);

    setlocalvar("x"+self, target1T(Slave, Time, dx, dy, "x", 0) );
    setlocalvar("y"+self, target1T(Slave, Time, dx, dy, "y", 0) );
}

void returner(float Time)
{// Return to previously stored coordinates
// Entity will reach coordinate within specified time
// Time = specified time

    void self = getlocalvar("self");
    float Tx = getentityvar(self,5);
    float Ty = getentityvar(self,6);
    float Vx;
    float Vy;

    Vx = target0T(Time, Tx, Ty, 0, 0, "x", 0);
    Vy = target0T(Time, Tx, Ty, 0, 0, "y", 0);

    changeentityproperty(self, "velocity", Vx, 0, Vy); //Return!
}

void dashSl(int Num, int I)
{// Dash Slave with previously attained speed!
// Num = Slave number
// I = Inverted flag
    void self = getlocalvar("self");
    void Slave = getentityvar(self, Num);
    float Vx = getlocalvar("x"+self);
    float Vy = getlocalvar("y"+self);

    if( Vx!=NULL() && Vy!=NULL() && I==0){
      changeentityproperty(Slave, "velocity", Vx, 0, Vy); //Move slave towards target!
    } else if( Vx!=NULL() && Vy!=NULL() && I==1){
      changeentityproperty(Slave, "velocity", -Vx, 0, -Vy); //Move slave away from target!
    }
}

void dasherSl(int Num, float Vx, float Vy)
{// Dash Slave with desired speed!
// Num = Slave number
// Vx = X Velocity
// Vy = Y Velocity
    void self = getlocalvar("self");
    void Slave = getentityvar(self, Num);
    int dir = getentityproperty(self,"direction");

    if(dir==0){ // Facing left?
      Vx = -Vx ;
    }

    changeentityproperty(Slave, "velocity", Vx, 0, Vy); //Move!
}

void anichangeSl(int Num, void Ani)
{// Change Slave's animation
// Num = Slave number
// Ani = Desired animation
    void self = getlocalvar("self");
    void Slave = getentityvar(self, Num);

    changeentityproperty(Slave, "animation", openborconstant(Ani));
}

void shooter3(void Shot, float dx, float dy, float Vx, float Vy, int Dir, int Map)
{ // Shooting special projectile with speed, map and direction
   void self = getlocalvar("self");
   int Direction = getentityproperty(self, "direction");
   void vShot;

   if (Direction == 0){ //Is entity facing left?                  
      Vx = -Vx; //Reverse Vx direction to match facing
   }

   vShot = shooter(Shot, dx, dy, Vx, Vy);
   changeentityproperty(vShot, "direction", Dir);
   changeentityproperty(vShot, "map", Map);
}

void tosserM(void Bomb, float dx, float dy, float Vx, float Vy)
{ // Tossing special bomb with speed control and same remap
   void self = getlocalvar("self");
   int  iMap = getentityproperty(self, "map");
   void vShot;

   vShot = tosser(Bomb, dx, dy, Vx, Vy);
   changeentityproperty(vShot, "map", iMap);
}

void ulurT()
{// Play ulur.wav if there's player
    void self = getlocalvar("self");
    int  SFX = loadsample("data/sounds/ulur.wav");
    setlocalvar("T"+self, findtarget(self)); //Get player

    void target = getlocalvar("T"+self);

    if ( target != NULL() ){
      playsample(SFX, 0, 120, 120, 100, 0);
    }
    setlocalvar("T"+self, NULL());
}
