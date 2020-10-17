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


}