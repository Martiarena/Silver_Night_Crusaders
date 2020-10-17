void main()
{// Temporary invincibility script
    void self = getlocalvar("self"); //Get calling entity.
    int Health = getentityproperty(self,"health");
    int Type = getlocalvar("attacktype");
    int eTime = openborvariant("elapsed_time");
    int damage = getlocalvar("damage");
    int result_damage = 0;
    int Current_health = 0;
    int Hardmode_active = openborvariant("current_stage");


    if (Hardmode_active > 10){
      if(Health > 0 && Type != openborconstant("ATK_NORMAL20")) {
        if(Health > 0 && Type != openborconstant("ATK_NORMAL21")) {
          if (damage < 25){
            result_damage = 25 - damage;
            changeentityproperty(self, "health", Health - result_damage);
          }
          Current_health = getentityproperty(self,"health");
          if(Current_health > 0 && Type != openborconstant("ATK_NORMAL20")) {
            if(Current_health > 0 && Type != openborconstant("ATK_NORMAL21")) {
              if (Current_health > 0 && Type != openborconstant("ATK_NORMAL17")){
                changeentityproperty(self, "invincible", 1);
                changeentityproperty(self, "invinctime", eTime + 300);
                changeentityproperty(self, "blink", 1);
              }
            }
          }
        }
      }
    } else {
      if(Health > 0 && Type != openborconstant("ATK_NORMAL20")) {
        if(Health > 0 && Type != openborconstant("ATK_NORMAL21")) {
          if (Health > 0 && Type != openborconstant("ATK_NORMAL17")) {
              changeentityproperty(self, "invincible", 1);
              changeentityproperty(self, "invinctime", eTime + 300);
              changeentityproperty(self, "blink", 1);
          }
  		  }
      }
    }
}