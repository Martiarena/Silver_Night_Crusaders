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