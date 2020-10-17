void main()
{
	void self = getlocalvar("self");
	void Stone1 = getentityvar(self, 1);
    void Stone2 = getentityvar(self, 2);
    void Stone3 = getentityvar(self, 3);
    void Stone4 = getentityvar(self, 4);

    killentity(Stone1);
    killentity(Stone2);
    killentity(Stone3);
    killentity(Stone4);
}