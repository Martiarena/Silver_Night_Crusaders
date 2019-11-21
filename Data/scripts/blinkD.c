void main()
{// Special Blink effect script
// Only blink if certain entity variable is set
    void self = getlocalvar("self"); //Get calling entity.
    int Health = getentityproperty(self,"health");
    int iTyp = openborconstant("ATK_NORMAL");  
    int Def = getentityproperty(self, "defense", iTyp, "factor");
    int SFX = loadsample("data/sounds/clang.wav");

    if(Health > 0 && Def != 0){
	changeentityproperty(self, "colourmap", 1);
	changeentityproperty(self, "maptime", 14 + openborvariant("elapsed_time"));
    } else if( Def == 0 ){
      playsample(SFX, 0, 120, 120, 100, 0);
    }
}