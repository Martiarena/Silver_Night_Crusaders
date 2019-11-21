void main()
{// Update script for displaying checkplatform
    void P1 = getplayerproperty(0, "entity"); 
    int x = getentityproperty(P1,"x"); //Get entity's x
    int y = getentityproperty(P1,"a"); //Get entity's altitude
    int z = getentityproperty(P1,"z"); //Get entity's z
//    void e = checkplatformbelow(x+10, z, y+10);
    void f = checkplatformbelow(x, z, y+2);
    char FName = getentityproperty(f,"name");
    
//    drawstring(50,110,0, "Right & above "+e);
    drawstring(50,130,0, "Below "+FName);

//    void Familiar = getentityvar(P1, 1);
//    char FamName = getentityproperty(Familiar,"name");
//    int FamEx = getentityproperty(Familiar,"exists");

//    drawstring(150,130,3, FamName);
//    drawstring(150,150,3, FamEx);
}
