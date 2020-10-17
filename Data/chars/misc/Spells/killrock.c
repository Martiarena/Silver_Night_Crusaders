void main()
{
	void self = getlocalvar("self");
	void StoneC = getentityproperty(self, "parent");

    damageentity(StoneC, self, 25, 1, openborconstant("ATK_NORMAL"));

}