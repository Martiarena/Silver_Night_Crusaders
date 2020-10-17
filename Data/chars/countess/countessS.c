#include "data/scripts/library/spawn.h"
#include "data/scripts/library/target.h"
#include "data/scripts/library/basic.h"

void spawn03(void Name, float dx, float dy, float dz, int Dir)
{ // Spawn entity based on screen edge + direction set
   void self = getlocalvar("self");
   void Spawn;

   Spawn = spawn02(Name, dx, dy, dz);
   changeentityproperty(Spawn, "direction", Dir); //Set direction
}

void spawn04(void Name, float dx, float dy, float dz)
{ // Spawn entity based on screen edge and current facing direction
   void self = getlocalvar("self");
   int Dir = getentityproperty(self,"direction");

   if(Dir==0){
     if(dx>=160){
       spawn03(Name, dx, dy, dz, 0);
     } else {
       spawn03(Name, dx, dy, dz, 1);
     }
   } else if(Dir==1){
     if(dx>=160){
       spawn03(Name, 320-dx, dy, dz, 1);
     } else {
       spawn03(Name, 320-dx, dy, dz, 0);
     }
   }
}

void spawnT2(void Name, float dx, float dy, int Dir)
{ // Spawn entity based on screen edge and it's directed at player
   void self = getlocalvar("self");
   void Spawn;
   setlocalvar("T"+self, findtarget(self)); //Get nearest player

   void target = getlocalvar("T"+self);

   if(target!=NULL() ){
     int Ty = getentityproperty(target,"a"); //Get player's a coordinate
     Spawn = spawn02(Name, dx, Ty+dy, 0);
   } else {
     int y = getentityproperty(self,"a");
     Spawn = spawn02(Name, dx, y+dy, 0);
   }
   changeentityproperty(Spawn, "direction", Dir); //Set direction
}

void attack0(void Ani)
{// Attack interruption
    void self = getlocalvar("self");

    performattack(self, openborconstant(Ani)); //Attack!
}

void randomtele(int Rx, int da)
{ // Teleport randomly onscreen
    void self = getlocalvar("self");
    int z = getentityproperty(self,"z"); //Get character's z coordinate
    int XPos = openborvariant("xpos"); //Get screen edge's position
    int iDX;

    if(Rx!=0){
      iDX = rand()%Rx;
    } else {
      iDX = 0;
    }

    changeentityproperty(self, "position",XPos+160+iDX, z, da); //Teleport!
}
