void main()
{// Temporary invincibility script
    void self = getlocalvar("self"); //Get calling entity.
    int Health = getentityproperty(self,"health");
    int Type = getlocalvar("attacktype");
    int eTime = openborvariant("elapsed_time");

    if(Health > 0 && Type != openborconstant("ATK_NORMAL20")) {
    	if (Health > 0 && Type != openborconstant("ATK_NORMAL17")){
      		changeentityproperty(self, "invincible", 1);
      		changeentityproperty(self, "invinctime", eTime + 300);
      		changeentityproperty(self, "blink", 1);
  		}
    }
}