//Script for lesser enemies

#include "data/scripts/library/spawn.h"
#include "data/scripts/library/target.h"
#include "data/scripts/library/basic.h"

void layer(int layer)
{// Set's enemy's layer
    void self = getlocalvar("self");
    changeentityproperty(self, "setlayer", layer);
}

void deathPar()
{ // Damage Parent on death
    void self = getlocalvar("self");
    void Parent = getentityproperty(self,"parent");
    int MHealth = getentityproperty(self,"maxhealth");

    if (Parent != NULL()){
      damageentity(Parent, self, MHealth, 0, openborconstant("ATK_NORMAL2"));
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

void mapchange(int Map)
{ // Animation changer
    void self = getlocalvar("self");

    changeentityproperty(self, "map", Map);
}

void spawnM(void Name, float dx, float dy, float dz)
{ // Spawn certain entity and matches its map with own's map
   void self = getlocalvar("self");
   int map = getentityproperty(self,"map");
   void Spawn;

   Spawn = spawn01(Name, dx, dy, 0);
   changeentityproperty(Spawn, "map", map);
}

void dasherP( float Vx, float Vy, float Vz , int Flip)
{// Dash with desired speed!
// Won't apply if enemy is in midair
    void self = getlocalvar("self");
    int dir = getentityproperty(self,"direction");
    int y = getentityproperty(self, "a");
    int b = getentityproperty(self, "base");

    if(dir==0 && Flip==1){ // Facing left?
      Vx = -Vx ;
    }

    if(y <= b){
      changeentityproperty(self, "velocity", Vx, Vz, Vy); //Move!
    }
}

void attack0(void Ani)
{// Attack interruption
    void self = getlocalvar("self");

    performattack(self, openborconstant(Ani)); //Attack!
}

void attackM(void Ani, int Remap)
{// Attack interruption if there's player
// Only occurs if remap matches
    void self = getlocalvar("self");
    int Map = getentityproperty(self, "map");
    void target = findtarget(self); //Find player

    if(target!=NULL() && Map==Remap){
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

/* ---- CUSTOM ---- */

void attack2(int RMin, int RMax, void Ani, int Flip)
{// Attack interruption with range check
// Diagonal targetting
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

      if(Flip==1){
        Disy = -Disy;
      }

      if( Disx >= Disy + RMin && Disx <= Disy + RMax && dir == 1) 
      {
        performattack(self, openborconstant(Ani)); //Change the animation
      } else if( Disx >= -Disy - RMax && Disx <= -Disy - RMin && dir == 0)
      {
        performattack(self, openborconstant(Ani)); //Change the animation
      }
    }
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
