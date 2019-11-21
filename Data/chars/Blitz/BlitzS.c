#include "data/scripts/player.c"

void clearE()
{// Clears entity variables
    void self = getlocalvar("self");
    setentityvar(self, 0, NULL());
}

void keyflip(int Inv)
{// Change hero's facing direction if left or right is pressed
    void self = getlocalvar("self");
    int iPIndex = getentityproperty(self,"playerindex"); //Get player index

    if (Inv == 0){
      if (playerkeys(iPIndex, 0, "moveleft")){ // Left is pressed?
        changeentityproperty(self, "direction", 0); //Face left
      } else if (playerkeys(iPIndex, 0, "moveright")){ // Right is pressed?
        changeentityproperty(self, "direction", 1); //Face right
      }
    } else if (Inv == 1){
      if (playerkeys(iPIndex, 0, "moveleft")){ // Left is pressed?
        changeentityproperty(self, "direction", 1); //Face right
      } else if (playerkeys(iPIndex, 0, "moveright")){ // Right is pressed?
        changeentityproperty(self, "direction", 0); //Face left
      }
    }
}

void keymove(float Vx, float Vz)
{// Move hero if direction button is pressed
      void self = getlocalvar("self");
      int iPIndex = getentityproperty(self,"playerindex"); //Get player index
	float xdir = 0;
	float zdir = 0;

      if (playerkeys(iPIndex, 0, "moveleft")){// Left is pressed?
	  xdir = -Vx;
	} else if(playerkeys(iPIndex, 0, "moveright")){// Right is pressed?
	  xdir = Vx;
      }

	if(playerkeys(iPIndex, 0, "moveup")){// Up is pressed?
	  zdir = -Vz;
	} else if(playerkeys(iPIndex, 0, "movedown")){// Down is pressed?
	  zdir = Vz;
      }

	changeentityproperty(self, "velocity", xdir, zdir);
}

void keyshoot(void Shot, float dx, float dy, float Vx, float Vy)
{// Shoot projectile based on pressed direction button
      void self = getlocalvar("self");
      int Dir = getentityproperty(self, "direction");
      int iPIndex = getentityproperty(self,"playerindex"); //Get player index
	float xdir;
	float ydir;

      if(playerkeys(iPIndex, 0, "moveup")){// Up is pressed?
	  ydir = Vy;

        if(playerkeys(iPIndex, 0, "moveleft") || playerkeys(iPIndex, 0, "moveright")){
	  xdir = Vx;
        } else {
	  xdir = 0;
        }

      } else if(playerkeys(iPIndex, 0, "movedown")){// Down is pressed?
	  ydir = -Vy;

        if(playerkeys(iPIndex, 0, "moveleft") || playerkeys(iPIndex, 0, "moveright")){
	  xdir = Vx;
        } else {
	  xdir = 0;
        }

      } else {
	  xdir = Vx;
	  ydir = 0;
      }

      shooter2(Shot, dx, dy, xdir, ydir);
}
