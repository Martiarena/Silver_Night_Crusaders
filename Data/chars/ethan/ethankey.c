void main()
{
    int iPlIndex = getlocalvar("player");
    void vSelf = getplayerproperty(iPlIndex , "entity");
    void vAniID = getentityproperty(vSelf,"animationID");
    void vAniPos = getentityproperty(vSelf, "animpos");
    int iDir = getentityproperty(vSelf, "direction");

    void iUp = playerkeys(iPlIndex, 1, "moveup");
    void iDown = playerkeys(iPlIndex, 1, "movedown");
    void iLeft = playerkeys(iPlIndex, 1, "moveleft");
    void iRight = playerkeys(iPlIndex, 1, "moveright");
    void iJump = playerkeys(iPlIndex, 1, "jump");
    void iSpecial = playerkeys(iPlIndex, 1, "Special");
    void iAttack = playerkeys(iPlIndex, 1, "attack");
    void iAttack2 = playerkeys(iPlIndex, 1, "attack2");
    void iAttack3 = playerkeys(iPlIndex, 1, "attack3");
    void iAttack4 = playerkeys(iPlIndex, 1, "attack4");

    void iLeftR = playerkeys(iPlIndex, 2, "moveleft");
    void iRightR = playerkeys(iPlIndex, 2, "moveright");
    void iDownR = playerkeys(iPlIndex, 2, "movedown");
    void iAttackR = playerkeys(iPlIndex, 2, "attack");

    void iUpH = playerkeys(iPlIndex, 0, "moveup");
    void iDownH = playerkeys(iPlIndex, 0, "movedown");
    void iLeftH = playerkeys(iPlIndex, 0, "moveleft");
    void iRightH = playerkeys(iPlIndex, 0, "moveright");

     void iUpH = playerkeys(iPlIndex, 0, "moveup"); //       Held status of "Up"
    void iDownH = playerkeys(iPlIndex, 0, "movedown"); //   Held status of "Down"
    void iLeftH = playerkeys(iPlIndex, 0, "moveleft"); //   Held status of "Left"
    void iRightH = playerkeys(iPlIndex, 0, "moveright"); // Held status of "Right"
    void iJumpH = playerkeys(iPlIndex, 0, "jump"); //       Held status of "Jump"
    void iSpecialH = playerkeys(iPlIndex, 0, "Special"); // Held status of "Special"
    void iAttackH = playerkeys(iPlIndex, 0, "attack"); //   Held status of "Attack"
    void iAttack2H = playerkeys(iPlIndex, 0, "attack2"); // Held status of "Attack 2"
    void iAttack3H = playerkeys(iPlIndex, 0, "attack3"); // Held status of "Attack 3"
    void iAttack4H = playerkeys(iPlIndex, 0, "attack4"); // Held status of "Attack 4"

    void iUpR = playerkeys(iPlIndex, 2, "moveup"); //       Release status of "Up"
    void iDownR = playerkeys(iPlIndex, 2, "movedown"); //   Release status of "Down"
    void iLeftR = playerkeys(iPlIndex, 2, "moveleft"); //   Release status of "Left"
    void iRightR = playerkeys(iPlIndex, 2, "moveright"); // Release status of "Right"
    void iJumpR = playerkeys(iPlIndex, 2, "jump"); //       Release status of "Jump"
    void iSpecialR = playerkeys(iPlIndex, 2, "Special"); // Release status of "Special"
    void iAttackR = playerkeys(iPlIndex, 2, "attack"); //   Release status of "Attack"
    void iAttack2R = playerkeys(iPlIndex, 2, "attack2"); // Release status of "Attack 2"
    void iAttack3R = playerkeys(iPlIndex, 2, "attack3"); // Release status of "Attack 3"
    void iAttack4R = playerkeys(iPlIndex, 2, "attack4"); // Release status of "Attack 4"


    //Whip Spiral
    if(iAttackR) {
      if(vAniID == openborconstant("ANI_ATTACK3")){ //Idle?
        performattack(vSelf, openborconstant("ANI_ATTACK4"));
      } else if(vAniID == openborconstant("ANI_FOLLOW3")){
        performattack(vSelf, openborconstant("ANI_ATTACK5"));
      }
      if(vAniID == openborconstant("ANI_ATTACK6")){ //Idle?
        performattack(vSelf, openborconstant("ANI_ATTACK8"));
      } else if(vAniID == openborconstant("ANI_FOLLOW6")){
        performattack(vSelf, openborconstant("ANI_ATTACK7"));
      }
    }

    //Double jump
    if(vAniID == openborconstant("ANI_JUMP") || vAniID == openborconstant("ANI_FOLLOW1")){ 
      if(iJump){ 
        changeentityproperty(vSelf, "animation", openborconstant("ANI_FREESPECIAL12"));
        if(iLeftH){ 
          changeentityproperty(vSelf, "direction", 0);
          tossentity(vSelf, 3, -1, 0);
        } else if(iRightH){
          changeentityproperty(vSelf, "direction", 1);
          tossentity(vSelf, 3, 1, 0);
        } else { 
          tossentity(vSelf, 3, 0, 0);
        }
      }
    }


}