void main()
{
    int iPlIndex = getlocalvar("player"); //Get calling player
    void vSelf = getplayerproperty(iPlIndex , "entity"); //Get calling entity
    void vAniID = getentityproperty(vSelf,"animationID"); //Get current animation ID
    void vAniPos = getentityproperty(vSelf, "animpos"); //Get current animation frame
    int iDir = getentityproperty(vSelf, "direction");  //Get current facing direction
    int MP = getentityproperty(vSelf,"mp"); //Get current MP

    void iUp = playerkeys(iPlIndex, 1, "moveup"); // New key status of "Up"
    void iDown = playerkeys(iPlIndex, 1, "movedown"); // New key status of "Down"
    void iLeft = playerkeys(iPlIndex, 1, "moveleft"); // New key status of "Left"
    void iRight = playerkeys(iPlIndex, 1, "moveright"); // New key status of "Right"
    void iJump = playerkeys(iPlIndex, 1, "jump"); //New key status of "Jump"
    void iSpecial = playerkeys(iPlIndex, 1, "Special"); //New key status of "Special"
    void iAttack = playerkeys(iPlIndex, 1, "attack"); //New key status of "Attack"
    void iAttack2 = playerkeys(iPlIndex, 1, "attack2"); // New key of "Attack 2"
    void iAttack3 = playerkeys(iPlIndex, 1, "attack3"); // New key of "Attack 3"
    void iAttack4 = playerkeys(iPlIndex, 1, "attack4"); // New key of "Attack 4"

    void iLeftR = playerkeys(iPlIndex, 2, "moveleft"); // Release status of "Left"
    void iRightR = playerkeys(iPlIndex, 2, "moveright"); // Release status of "Right"
    void iDownR = playerkeys(iPlIndex, 2, "movedown"); //Release status of "Down"
    void iAttackR = playerkeys(iPlIndex, 2, "attack"); //Release status of "Attack"

    void iUpH = playerkeys(iPlIndex, 0, "moveup");
    void iDownH = playerkeys(iPlIndex, 0, "movedown");
    void iLeftH = playerkeys(iPlIndex, 0, "moveleft");
    void iRightH = playerkeys(iPlIndex, 0, "moveright");

//Double jump
    if(vAniID == openborconstant("ANI_JUMP") || vAniID == openborconstant("ANI_FOLLOW1")){ //Jumping?
      if(iJump){ //Left pressed?
        changeentityproperty(vSelf, "animation", openborconstant("ANI_FREESPECIAL12"));
        if(iLeftH){ //Left held?
          changeentityproperty(vSelf, "direction", 0);
          tossentity(vSelf, 3, -1, 0);
        } else if(iRightH){ //Right held?
          changeentityproperty(vSelf, "direction", 1);
          tossentity(vSelf, 3, 1, 0);
        } else { //Nothing
          tossentity(vSelf, 3, 0, 0);
        }
      }
    }

    if(vAniID == openborconstant("ANI_RUNJUMP") || vAniID == openborconstant("ANI_FOLLOW1")){ //Jumping?
      if(iJump){ //Left pressed?
        changeentityproperty(vSelf, "animation", openborconstant("ANI_FREESPECIAL12"));
        if(iLeftH){ //Left held?
          changeentityproperty(vSelf, "direction", 0);
          tossentity(vSelf, 3, -2, 0);
        } else if(iRightH){ //Right held?
          changeentityproperty(vSelf, "direction", 1);
          tossentity(vSelf, 3, 2, 0);
        } else { //Nothing
          tossentity(vSelf, 3, 0, 0);
        }
      }
    }

}



void spawn01(void vName, float fX, float fY, float fZ)
{
	//vName: Model name of entity to be spawned in.
	//fX: X location adjustment.
	//fY: Y location adjustment.
        //fZ: Z location adjustment.

	int player = getlocalvar("player");
	void self = getplayerproperty(player, "entity");
	void vSpawn; //Spawn object.
	int  iDirection = getentityproperty(self, "direction");

	clearspawnentry(); //Clear current spawn entry.
        setspawnentry("name", vName); //Acquire spawn entity by name.

	if (iDirection == 0){ //Is entity facing left?                  
          fX = -fX; //Reverse X direction to match facing.
	}

      fX = fX + getentityproperty(self, "x"); //Get X location and add adjustment.
      fY = fY + getentityproperty(self, "a"); //Get Y location and add adjustment.
      fZ = fZ + getentityproperty(self, "z"); //Get Z location and add adjustment.
	
	vSpawn = spawn(); //Spawn in entity.

	changeentityproperty(vSpawn, "position", fX, fZ, fY); //Set spawn location.
	changeentityproperty(vSpawn, "direction", iDirection); //Set direction.

	return vSpawn; //Return spawn
}

void spawner(void vName, float fX, float fY, float fZ)
{	//Spawns entity next to caller and set them as child.
	//
	//vName: Model name of entity to be spawned in.
	//fX: X location adjustment.
	//fY: Y location adjustment
      //fZ: Z location adjustment

	int player = getlocalvar("player");
	void self = getplayerproperty(player, "entity");
	void vSpawn; //Spawn object.
	
	vSpawn = spawn01(vName, fX, fY, fZ); //Spawn in entity.

	changeentityproperty(vSpawn, "parent", self); //Set caller as parent.
        setentityvar(self, 1, vSpawn);
	changeentityproperty(vSpawn, "owner", self);   
	return vSpawn; //Return spawn
}

void spawnBind(void vName, float fX, float fY, float fZ, int Num)
{ //Spawns entity next to caller and set them as child.
  //
  //vName: Model name of entity to be spawned in.
  //fX: X location adjustment.
  //fY: Y location adjustment
      //fZ: Z location adjustment

  int player = getlocalvar("player");
  void self = getplayerproperty(player, "entity");
  void vSpawn; //Spawn object.
  
  vSpawn = spawn01(vName, fX, fY, fZ); //Spawn in entity.

  changeentityproperty(vSpawn, "parent", self); //Set caller as parent.
    bindentity(vSpawn, self, fX, fZ, fY);
        setentityvar(self, Num, vSpawn);  
  return vSpawn; //Return spawn
}