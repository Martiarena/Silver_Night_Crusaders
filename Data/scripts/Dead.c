void main()
{// Death script for players with familiar
    void self = getlocalvar("self");
    void Familiar = getentityvar(self, 1);
    void StoneCircle = getentityvar(self, 2);


    if(Familiar){
      bindentity(Familiar, NULL());
      damageentity(Familiar, self, 1000, 1, openborconstant("ATK_NORMAL"));
      setentityvar(self, 1, NULL());
    }

    if(StoneCircle){
      bindentity(StoneCircle, NULL());
      damageentity(StoneCircle, self, 1000, 1, openborconstant("ATK_NORMAL"));

      setentityvar(self, 2, NULL());
    }
}