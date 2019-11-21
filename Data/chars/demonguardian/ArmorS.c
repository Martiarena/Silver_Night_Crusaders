//Script for armors

#include "data/scripts/library/spawn.h"
#include "data/scripts/library/target.h"
#include "data/scripts/library/basic.h"

void immunity(int Def)
{// Sets immunity to all used attacktypes
    void self = getlocalvar("self");
    int iTyp1 = openborconstant("ATK_NORMAL");
    int iTyp2 = openborconstant("ATK_NORMAL2");
    int iTyp3 = openborconstant("ATK_NORMAL3");
    int iTyp4 = openborconstant("ATK_NORMAL4");
    int iTypS = openborconstant("ATK_SHOCK");
    int iTypB = openborconstant("ATK_BURN");

    changeentityproperty(self,"defense", iTyp1, Def);
    changeentityproperty(self,"defense", iTyp2, Def);
    changeentityproperty(self,"defense", iTyp3, Def);
    changeentityproperty(self,"defense", iTyp4, Def);
    changeentityproperty(self,"defense", iTypS, Def);
    changeentityproperty(self,"defense", iTypB, Def);
}

void attack1(int RxMin, int RxMax, int RyMin, int RyMax, void Ani)
{// Attack interruption with range check
// Straight targetting
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

void shooter3(void Shot, float dx, float dy, float Vx, float Vy, int Dir, int Map)
{ // Shooting special projectile with speed, map and direction
   void self = getlocalvar("self");
   void vShot;

   vShot = spawn01(Shot, dx, dy, 0);
   changeentityproperty(vShot, "velocity", Vx, 0, Vy);
   changeentityproperty(vShot, "owner", self);
   changeentityproperty(vShot, "direction", Dir);
   changeentityproperty(vShot, "map", Map);
}

void shootB(void Shot, float dx, float dy, int Num)
{ // Shooting targetted projectile with extra features
   void self = getlocalvar("self");
   float Vx = getlocalvar("x"+self);
   float Vy = getlocalvar("y"+self);
   void vShot;

   if( Vx!=NULL() && Vy!=NULL() ){
     vShot = shooter2(Shot, dx, dy, Vx, Vy);
     setentityvar(self, Num, vShot); // Stores spawned projectile to be killed later
     changeentityproperty(vShot, "parent", self); //Set caller as parent
     changeentityproperty(vShot, "velocity", Vx, 0, 2*Vy); //Move projectile towards target!
   }
}

void killP(int Num, int Flag)
{ // Kill projectile based on number
    void self = getlocalvar("self");
    void Proj = getentityvar(self, Num);

    if(Proj!=NULL()){
      if(Flag==1){
        damageentity(Proj, self, 1000, 0, openborconstant("ATK_NORMAL"));
      } else {
        killentity(Proj);
      }
    }
}
