void main()
{// Death script for players with familiar
    void self = getlocalvar("self");
    void Familiar = getentityvar(self, 1);

    if(Familiar){
      bindentity(Familiar, NULL());
//      killentity(Familiar);
      damageentity(Familiar, self, 1000, 1, openborconstant("ATK_NORMAL"));
      damageentity(Familiar, self, 1000, 1, openborconstant("ANI_FREESPECIAL24"));
      setentityvar(self, 1, NULL());
    }
}