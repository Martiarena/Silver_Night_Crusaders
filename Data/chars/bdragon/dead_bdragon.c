void main()
{
	void self = getlocalvar("self");
    void Parent = getentityproperty(self, "parent");

    damageentity(Parent, self, 1000, 1, openborconstant("ATK_NORMAL"));
}