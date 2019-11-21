void main(){


    int iPlIndex = getlocalvar("player"); //Get calling player
    void vSelf = getplayerproperty(iPlIndex, "entity"); //Get calling entity
    void vAniID = getentityproperty(vSelf,"animationID"); //Get current animation ID
    void vAniPos = getentityproperty(vSelf, "animpos"); //Get current animation frame
    int  iDir = getentityproperty(vSelf, "direction");  //Get current facing direction

    void iUp = playerkeys(iPlIndex, 1, "moveup"); // New key status of "Up"
    void iDown = playerkeys(iPlIndex, 1, "movedown"); // New key status of "Down"
    void iLeft = playerkeys(iPlIndex, 1, "moveleft"); // New key status of "Left"
    void iRight = playerkeys(iPlIndex, 1, "moveright"); // New key status of "Right"
    void iJump = playerkeys(iPlIndex, 1, "jump"); //New key status of "Jump"
    void iSpecial = playerkeys(iPlIndex, 1, "Special"); //New key status of "Special"
    void iAttack = playerkeys(iPlIndex, 1, "attack"); //New key status of "Attack"
    void iAttack2 = playerkeys(iPlIndex, 1, "attack2"); // New key status of "Attack 2"
    void iAttack3 = playerkeys(iPlIndex, 1, "attack3"); // New key status of "Attack 3"
    void iAttack4 = playerkeys(iPlIndex, 1, "attack4"); // New key status of "Attack 4"

    void iLeftR = playerkeys(iPlIndex, 2, "moveleft"); // Release status of "Left"
    void iRightR = playerkeys(iPlIndex, 2, "moveright"); // Release status of "Right"
    void iAttackR = playerkeys(iPlIndex, 2, "attack"); //Release status of "Attack"

    void iLeftH = playerkeys(iPlIndex, 0, "moveleft");
    void iRightH = playerkeys(iPlIndex, 0, "moveright");

    void iForwardH; // New key status of "Forward"
    if (iDir == 0){ // Facing Left?
      iForwardH = playerkeys(iPlIndex, 0, "moveleft"); // "Left"
    } else { // Facing Right
      iForwardH = playerkeys(iPlIndex, 0, "moveright"); // "Right"
    }

//Jump Special
    if (vAniID == openborconstant("ANI_JUMP") || vAniID == openborconstant("ANI_FORWARDJUMP") || vAniID == openborconstant("ANI_FREESPECIAL")){ //Jumping?
      if (iSpecial){ //Special pressed?
        if (vAniPos >= 1){ //Not on 1st frame?
	  changeentityproperty(vSelf, "animation", openborconstant("ANI_JUMPSPECIAL"));
          updateframe(vSelf, 0);
        }
      }
    }

//Double jump
    if(vAniID == openborconstant("ANI_JUMP") || vAniID == openborconstant("ANI_FORWARDJUMP")){ //Jumping?
      if(iJump){ //Left pressed?
        changeentityproperty(vSelf, "animation", openborconstant("ANI_FREESPECIAL"));
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

}