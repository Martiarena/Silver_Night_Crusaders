void main()
{// Death script for Stone Circle
    void self = getlocalvar("self");
    void Parent = getentityproperty(self, "parent");
    void Stone1 = getentityvar(self, 1);
    void Stone2 = getentityvar(self, 2);
    void Stone3 = getentityvar(self, 3);
    void Stone4 = getentityvar(self, 4);

    if(Parent){
      setentityvar(Parent, 1, NULL());
    }
    if(Stone1){
      killentity(Stone1);
      setentityvar(self, 1, NULL());
    }    
    if(Stone2){
      killentity(Stone2);
      setentityvar(self, 2, NULL());
    }
    if(Stone3){
      killentity(Stone3);
      setentityvar(self, 3, NULL());
    }
    if(Stone4){
      killentity(Stone4);
      setentityvar(self, 4, NULL());
    }
}