//Script for chain and serpent body slaves
//Also for simple homing enemies

#include "data/scripts/library/spawn.h"
#include "data/scripts/library/target.h"
#include "data/scripts/library/basic.h"


void groundchange(void Ani)
{// Check altitude. If projectile is on ground, change animation!
    void self = getlocalvar("self");
    int x = getentityproperty(self,"x");
    int z = getentityproperty(self,"z");
    int y = getentityproperty(self,"a");

    int H = checkhole(x,z,y-100);

    if( y <= 1 && H != 1){ // On ground but not on hole?
      changeentityproperty(self, "animation", openborconstant(Ani));
    }
}

void suicidePar()
{ // Suicide if Parent dies
    void self = getlocalvar("self");
    void Parent = getentityproperty(self, "parent");
    int  Health = getentityproperty(Parent, "health");

    if (Health <= 0){
      damageentity(self, self, 1000, 0, openborconstant("ATK_NORMAL"));
    }
}

void suicidePoint()
{ // Suicide if Chain Point dies
    void self = getlocalvar("self");
    void CPoint = getentityvar(self, 0);
    int  Health = getentityproperty(CPoint, "health");

    if (Health <= 0){
      damageentity(self, self, 1000, 0, openborconstant("ATK_NORMAL"));
    }
}

void mapPar()
{ // Match remap with Parent's
    void self = getlocalvar("self");
    void Parent = getentityproperty(self, "parent");
    int  Map = getentityproperty(Parent, "map");

    changeentityproperty(self, "map", Map); //Adjust remap
}

void mapPoint()
{ // Match remap with Chain Point's
    void self = getlocalvar("self");
    void CPoint = getentityvar(self, 0);
    int  Map = getentityproperty(CPoint, "map");

    changeentityproperty(self, "map", Map); //Adjust remap
}

void dirspeed()
{ // Match facing direction with x velocity
    void self = getlocalvar("self");
    float Vx = getentityproperty(self, "xdir");

    if (Vx < 0){
      changeentityproperty(self, "direction", 0); //Face left!
    } else if (Vx > 0){
      changeentityproperty(self, "direction", 1); //Face right!
    }
}

void changemap(int iMap)
{// Change remap
    void self = getlocalvar("self");

    changeentityproperty(self, "map", iMap); //Change remap
}

void targetdash(float Velx, float Vely, float dx, float dy, int Stop)
{// Targetting opponent then dash
// Velx = x Velocity
// Vely = y Velocity
// dx = x added distance
// dy = y added distance
// Stop = flag to stop moving if no target is found

    void self = getlocalvar("self");
    float Vx;
    float Vy;

    setlocalvar("T"+self, findtarget(self)); //Get nearest player

    void target = getlocalvar("T"+self);
    Vx = target1(target, Velx, Vely, dx, dy, Stop, "x", 1);
    Vy = target1(target, Velx, Vely, dx, dy, Stop, "y", 1);

    changeentityproperty(self, "velocity", Vx, 0, Vy); //Move towards target!
    setlocalvar("T"+self, NULL()); //Clears variable
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

void targetPar(float Velx, float Vely, float dx, float dy, int Stop)
{// Targetting parent before dashing
// Velx = x Velocity
// Vely = y Velocity
// dx = x added distance
// dy = y added distance
// Stop = flag to stop moving if there's no parent

    void self = getlocalvar("self");
    void Parent = getentityproperty(self, "parent");

    setlocalvar("x"+self, target1(Parent, Velx, Vely, dx, dy, Stop, "x", 0) );
    setlocalvar("y"+self, target1(Parent, Velx, Vely, dx, dy, Stop, "y", 0) );
}

void targetParT(float Time, float dx, float dy)
{// Targetting parent before dashing
// Produced velocity will be required speed to get to target within specified time
// Time = Specified time
// dx = x added distance
// dy = y added distance

    void self = getlocalvar("self");
    void Parent = getentityproperty(self, "parent");

    setlocalvar("x"+self, target1T(Parent, Time, dx, dy, "x", 0) );
    setlocalvar("y"+self, target1T(Parent, Time, dx, dy, "y", 0) );
}

void targetPardashT(float Time, float dx, float dy)
{// Targetting parent before dashing
// Time = Specified time
// dx = x added distance
// dy = y added distance

    void self = getlocalvar("self");
    void Parent = getentityproperty(self, "parent");

    float Vx = target1T(Parent, Time, dx, dy, "x", 0);
    float Vy = target1T(Parent, Time, dx, dy, "y", 0);

    changeentityproperty(self, "velocity", Vx, 0, Vy); //Move towards parent!
}

void distancer(float Time, int Rx, int Ry, int FLink)
{// Checks distance between self and links
// If it is out of range, move to keep distance
// Time = desired time
// Rx = x distance
// Ry = y distance

    void self = getlocalvar("self");
    float x = getentityproperty(self, "x");
    float y = getentityproperty(self, "a");
    float Disx, Disy;
    float Vx,Vy;
    void Link;

    if(FLink==0){ //Get 1st Link
      Link = getentityvar(self, 0);
    } else if(FLink==1){ //Get 2nd Link
      Link = getentityvar(self, 1);
    }

    if(Link!=NULL()){
      float Tx = getentityproperty(Link, "x");
      float Ty = getentityproperty(Link, "a");
      Disx = Tx - x;
      Disy = Ty - y;
    } else {
      Disx = 0;
      Disy = 0;
    }

    if(Disx < 0){
      Disx = -Disx;
    }
    if(Disy < 0){
      Disy = -Disy;
    }

    if(Disx > Rx || Disy > Ry){
      Vx = target1T(Link, Time, 0, 0, "x", 0);
      Vy = target1T(Link, Time, 0, 0, "y", 0);

      changeentityproperty(self, "velocity", Vx, 0, Vy); //Move!
    } else {
      changeentityproperty(self, "velocity", 0, 0, 0);
    }
}

void chain(void Pos)
{// Find coordinate between 2 coordinates based on Ratio 
// The 2 entities are Parent's coordinates and chain point
    void self = getlocalvar("self");
    void Parent = getentityproperty(self, "parent");
    void CPoint = getentityvar(self, 0);
    float Ratio = getentityvar(self, 2);
    float Px = getentityproperty(Parent, "x") + getentityvar(self, 3);
    float Py = getentityproperty(Parent, "a") + getentityvar(self, 4);
    float Ox = getentityproperty(CPoint, "x");
    float Oy = getentityproperty(CPoint, "a"); 
    float Tx;
    float Ty; 

    float Disx = Px - Ox;
    float Disy = Py - Oy;

//Get in between coords based on Ratio
    Tx = (Ox-Px)*Ratio + Px;
    Ty = (Oy-Py)*Ratio + Py;

    if(Pos == "x"){
      return Tx;
    }
    if(Pos == "y"){
      return Ty;
    }
}

void telechain()
{// Teleport to between 2 coordinates
    void self = getlocalvar("self");
    float Tx = chain("x");
    float Ty = chain("y");
    float z = getentityproperty(self,"z"); //Get entity's z coordinate

    changeentityproperty(self, "position", Tx, z, Ty); //Teleport!
}

void dashF()
{// Dash with current speed + Parent's speed!
    void self = getlocalvar("self");
    void Parent = getentityproperty(self, "parent");
    float Vx = getentityproperty(self, "xdir");
    float Vy = getentityproperty(self, "tossv");
    float PVx = getentityproperty(Parent, "xdir");
    float PVy = getentityproperty(Parent, "tossv");

    changeentityproperty(self, "velocity", Vx+PVx, 0, Vy+PVy); //Move!
}

void attack0(void Ani)
{// Attack interruption
    void self = getlocalvar("self");

    performattack(self, openborconstant(Ani)); //Attack!
}

void groundkill()
{// Check altitude. If projectile is on ground, suicide!
    void self = getlocalvar("self");
    int x = getentityproperty(self,"x");
    int z = getentityproperty(self,"z");
    int y = getentityproperty(self,"a");

    int H = checkhole(x,z,y-100);

    if(y <= 3 && H != 1){ // On ground but not on hole?
      killentity(self); //Suicide!
    }
}

void suicide()
{ // Suicide!!
    void self = getlocalvar("self");

    killentity(self); //Suicide!
}