#include "data/scripts/library/spawn.h"
#include "data/scripts/library/basic.h"
#include "data/scripts/library/target.h"
#include "data/scripts/fscript.c"
#include "data/scripts/keyfly.c"

void mpcost( int Cost)
{// Spend some MP
    void self = getlocalvar("self");
    int MP = getentityproperty(self,"mp");

    changeentityproperty(self, "mp", MP-Cost); //Spend!
}

void limiter(int Limit)
{// Prevents hero from performing the animation if his/her MP is less than Limit
    void self = getlocalvar("self");
    int MP = getentityproperty(self,"mp"); //Get entity's MP
    int y = getentityproperty(self,"a"); //Get entity's altitude
    int b = getentityproperty(self, "base"); //Get entity's base

   if(MP<=Limit) // Don't have enough MP?
   {
     if(y > b) // Mid air?
     {
       changeentityproperty(self, "animation", openborconstant("ANI_JUMP") );
     } else{
       setidle(self); //Don't play the animation
     }
   }
}

void limiterSub()
{// Prevents hero from performing the animation if he/she doesn't have any subweapon
   void self = getlocalvar("self");
   int iPI = getentityproperty(self,"playerindex"); //Get player index
   int SubWeapon = getglobalvar(iPI+"0");
   int y = getentityproperty(self,"a"); //Get entity's altitude
   int b = getentityproperty(self, "base"); //Get entity's base

   if( SubWeapon == NULL() ) // Don't have subweapon?
   {
     if(y > b) // Mid air?
     {
       changeentityproperty(self, "animation", openborconstant("ANI_JUMP") );     
     } else{
       setidle(self); //Don't play the animation
     }
   }
}

void floater( int Time )
{// Floats in Time centiseconds
    void self = getlocalvar("self");
    int eTime = openborvariant("elapsed_time");

    changeentityproperty(self, "tosstime", eTime + 2*Time);
}

void keyint(void Ani, int Frame, void Key, int Hflag)
{// Change current animation if proper key is pressed or released
// Animation is changed to attack mode

    void self = getlocalvar("self");
    int Dir = getentityproperty(self, "direction");
    int iPIndex = getentityproperty(self,"playerindex"); //Get player index
    void iRKey;

      if (Key=="U"){ //Up Required?
        iRKey = playerkeys(iPIndex, 0, "moveup"); // "Up"
      } else if (Key=="D"){ //Down Required?
        iRKey = playerkeys(iPIndex, 0, "movedown"); // "Down"
      } else if (Key=="L"){ //Left Required?
        iRKey = playerkeys(iPIndex, 0, "moveleft"); // "Left"
      } else if (Key=="R"){ //Right Required?
        iRKey = playerkeys(iPIndex, 0, "moveright"); // "Right"
      } else if (Key=="F"){ //Forward Required?
        if (Dir == 0){ // Facing Left?
          iRKey = playerkeys(iPIndex, 0, "moveleft"); // "Left"
        } else { // Facing Right
          iRKey = playerkeys(iPIndex, 0, "moveright"); // "Right"
        }
      } else if (Key=="B"){ //Backward Required?
        if (Dir == 1){ // Facing Right?
          iRKey = playerkeys(iPIndex, 0, "moveleft"); // "Left"
        } else { // Facing Left
          iRKey = playerkeys(iPIndex, 0, "moveright"); // "Right"
        }
      } else if (Key=="J"){ //Jump Required?
        iRKey = playerkeys(iPIndex, 0, "jump"); // "Jump"
      } else if (Key=="A"){ //Attack Required?
        iRKey = playerkeys(iPIndex, 0, "attack"); // "Attack"
      } else if (Key=="S"){ //Special Required?
        iRKey = playerkeys(iPIndex, 0, "special"); // "Special"
      }

      if (Hflag==1){ //Not holding the button case?
        iRKey = !iRKey; //Take the opposite condition
      }

      if (iRKey){
        if (Ani=="ANI_IDLE"){ // Going idle?
          setidle(self, openborconstant("ANI_IDLE")); //Be idle!
        } else {
          performattack(self, openborconstant(Ani)); //Change the animation
        }
        updateframe(self, Frame); //Change frame
      }
}

void keymove(float Vx)
{// Move hero if direction button is pressed
      void self = getlocalvar("self");
      int iPIndex = getentityproperty(self,"playerindex"); //Get player index
  float xdir = 0;

      if (playerkeys(iPIndex, 0, "moveleft")){// Left is pressed?
    xdir = -Vx;
  } else if(playerkeys(iPIndex, 0, "moveright")){// Right is pressed?
    xdir = Vx;
      }

  changeentityproperty(self, "velocity", xdir);
}

void Triafire(float dx, float dy)
{
  void self = getlocalvar("self");
  int iPI = getentityproperty(self,"playerindex"); //Get player index
  int SubWeapon = getglobalvar(iPI+"0");

  shooterAnim("Fire_sh", dx, dy, 0.4, 1.8, "ANI_FOLLOW2");
  shooter2("Fire_sh", dx, dy, 1, 0);
  shooterAnim("Fire_sh", dx, dy, 0.4, -1.8, "ANI_FOLLOW5");
}

void SubWeapon(float dx, float dy)
{ // Shooting/tossing specific subweapon based on current subweapon
   void self = getlocalvar("self");
   int iPI = getentityproperty(self,"playerindex"); //Get player index
   int SubWeapon = getglobalvar(iPI+"0");

   if (SubWeapon == 1){ //--- Knife
      shooterAnim("PKnife", dx, dy, 1.4, 2.8, "ANI_FOLLOW2");
      shooterAnim("PKnife", dx, dy, 1.8, 1.5, "ANI_FOLLOW3");
      shooter2("PKnife", dx, dy, 2, 0);
      shooterAnim("PKnife", dx, dy, 1.8, -1.5, "ANI_FOLLOW4");
      shooterAnim("PKnife", dx, dy, 1.4, -2.8, "ANI_FOLLOW5");
   } else if (SubWeapon == 2){ //--- Axe
     tosser2("PAxe", dx, dy, 0.6, 4);
   } else if (SubWeapon == 3){ //--- Holy Cross
     shooter("PCross", dx, dy, 0, 1, 0, 0);
   } else if (SubWeapon == 4){ //--- Holy water
    tosser("Pholywater", dx, dy, 0, 0.3, 2, 0); 
   } else if (SubWeapon == 5){ //--- Bomba
    tosser("PBomb", dx, dy, 0, 0.6, 2, 0); 
   } else if (SubWeapon == 6){ //--- Bible
     shooter2("PBible", dx, dy+200, 0.3, 0);
   } else if (SubWeapon == 7){ //--- Boomerade
     shooter2("PBomrade", dx, dy-5, 2, 2);
   }

}

void shooterAnim(void Shot, float dx, float dy, float Vx, float Vy, void Ani)
{ // Shooting special projectile with speed & animation control
   void self = getlocalvar("self");
   int Direction = getentityproperty(self, "direction");
   void vShot;

   if (Direction == 0){ //Is entity facing left?                  
      Vx = -Vx; //Reverse Vx direction to match facing
   }

   vShot = spawn01(Shot, dx, dy, 0);
   changeentityproperty(vShot, "velocity", Vx, 0, Vy);
   changeentityproperty(vShot, "owner", self);
   changeentityproperty(vShot, "animation", openborconstant(Ani));
}

void keyfly(float V)
{// Move hero if direction button is pressed
      void self = getlocalvar("self");
      int iPIndex = getentityproperty(self,"playerindex"); //Get player index
      int a = getentityproperty(self,"a"); //Get player's altitude
    float xdir = 0;
    float ydir = 0;

      if (playerkeys(iPIndex, 0, "moveleft")){// Left is pressed?
      xdir = -V;
    } else if(playerkeys(iPIndex, 0, "moveright")){// Right is pressed?
      xdir = V;
      }

    if(playerkeys(iPIndex, 0, "moveup") && (a <= 360)){// Up is pressed?
      ydir = V;
    } else if(playerkeys(iPIndex, 0, "movedown") && (a >= 0)){// Down is pressed?
      ydir = -V;
      }

    changeentityproperty(self, "velocity", xdir, 0, ydir);
}