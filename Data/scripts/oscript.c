void offscreenkill( float dx, int E )
{// Check position relative to screen. If enemy is offscreen, suicide!
//  dx : Distance to screen edge
//  E  : Edge selection, 0 = left, 1 = right

    void self = getlocalvar("self");
    int x = getentityproperty(self,"x"); //Get character's x coordinate
    int XPos = openborvariant("xpos"); //Get screen edge's position

    if( (x > XPos + 320 + dx) && (E == 1) ){ // Offscreen to the right?
      killentity(self); //Suicide!
    } else if( (x < XPos - dx) && (E == 0) ){ // Offscreen to the left?
      killentity(self); //Suicide!
    }
}

void groundkill()
{// Check altitude. If bomb is on ground, suicide!

    void self = getlocalvar("self");
    int y = getentityproperty(self,"a"); //Get bomb's altitude

    if( y <= 5 ){ // On ground?
      killentity(self); //Suicide!
    }
}

void suicide()
{ // Suicide!!
    void self = getlocalvar("self");

    killentity(self); //Suicide!
}

void degravity(int Ratio)
{// Changes antigravity effect
    void self = getlocalvar("self");
    changeentityproperty(self, "antigravity", Ratio);
}

void givescore(int Num, int Add)
{// Gives player score
    int PScore = getplayerproperty(Num, "score"); // Get player's score
    changeplayerproperty(Num, "score", PScore+Add);
}

void clearL()
{ // Clears all local variables
     clearlocalvar();
}

void dasher( float Vx, float Vy)
{// Dash with desired speed!
    void self = getlocalvar("self");
    int dir = getentityproperty(self,"direction");

    if(dir==0){ // Facing left?
      Vx = -Vx ;
    }

    changeentityproperty(self, "velocity", Vx, 0, Vy); //Move!
}

void clearE(int Num)
{ // Clears entity variable
    void self = getlocalvar("self");
    setentityvar(self, Num, NULL());
}

void spawn01(void vName, float fX, float fY, float fZ)
{
	//spawn01 (Generic spawner)
	//Damon Vaughn Caskey
	//07/06/2007
	//
	//Spawns entity next to caller.
	//
	//vName: Model name of entity to be spawned in.
	//fX: X location adjustment.
	//fY: Y location adjustment.
      //fZ: Z location adjustment.

	void self = getlocalvar("self"); //Get calling entity.
	void vSpawn; //Spawn object.
	int  iDirection = getentityproperty(self, "direction");

	clearspawnentry(); //Clear current spawn entry.
      setspawnentry("name", vName); //Acquire spawn entity by name.

	if (iDirection == 0){ //Is entity facing left?                  
          fX = -fX; //Reverse X direction to match facing.
	}

      fX = fX + getentityproperty(self, "x"); //Get X location and add adjustment.
      fY = fY + getentityproperty(self, "a"); //Get Y location and add adjustment.
      fZ = fZ + getentityproperty(self, "z"); //Get Z location and add adjustment.
	
	vSpawn = spawn(); //Spawn in entity.

	changeentityproperty(vSpawn, "position", fX, fZ, fY); //Set spawn location.
	changeentityproperty(vSpawn, "direction", iDirection); //Set direction.
    
	return vSpawn; //Return spawn.
}

void spawn02(void vName, float fX, float fY, float fZ)
{
	//Spawns entity based on left screen edge
	//
	//vName: Model name of entity to be spawned in.
	//fX: X distance relative to left edge
	//fY: Y location adjustment
      //fZ: Z location adjustment

	void self = getlocalvar("self"); //Get calling entity.
	void vSpawn; //Spawn object.
        int XPos = openborvariant("xpos"); //Get screen edge's position

	clearspawnentry(); //Clear current spawn entry.
      setspawnentry("name", vName); //Acquire spawn entity by name.

      fZ = fZ + getentityproperty(self, "z"); //Get Z location and add adjustment.

	vSpawn = spawn(); //Spawn in entity.

	changeentityproperty(vSpawn, "position", fX + XPos, fZ, fY); //Set spawn location.

	return vSpawn; //Return spawn.
}

void Mspawn(void Name, float dx, float dy)
{ // Spawn certain entity and respawns if it dies
   void self = getlocalvar("self");
   int map = getentityproperty(self,"map");
   void Entity = getentityvar(self, 0);
   void Spawn;

   if(Entity==NULL()){ // Entity is absent?
     Spawn = spawn02(Name, dx, dy, 0);
     changeentityproperty(Spawn, "map", map);
     setentityvar(self, 0, Spawn);
   } else { // Entity is present
     int Health = getentityproperty(Entity, "health");

     if(Health<=0){ // Entity is dead?
       setentityvar(self, 0, NULL());
     }
   }
}

void MspawnR(void Name, float dx, float dy, int DevX, int DevY)
{ // Spawn certain entity and respawns if it dies
//Random effect is added
   void self = getlocalvar("self");
   int map = getentityproperty(self,"map");
   int iHealth = getentityproperty(self,"health");
   void Entity = getentityvar(self, 0);

   if(Entity==NULL()){ // Entity is absent?
     void Spawn;
     int iR = rand()%30;
     int iDX;
     int iDY;

     if(DevX!=0){
       iDX = rand()%DevX;
     } else {
       iDX = 0;
     }

     if(DevY!=0){
       iDY = rand()%DevY;
     } else {
       iDY = 0;
     }

     if (iR > 0){ 
       Spawn = spawn02(Name, 320-dx+iDX, dy+iDY, 0);
       changeentityproperty(Spawn, "direction", 1);
     } else {
       Spawn = spawn02(Name, dx+iDX, dy+iDY, 0);
       changeentityproperty(Spawn, "direction", 0);
     }
     changeentityproperty(Spawn, "map", map);
     changeentityproperty(Spawn, "health", iHealth);
     setentityvar(self, 0, Spawn);

   } else { // Entity is present
     int Health = getentityproperty(Entity, "health");

     if(Health<=0){ // Entity is dead?
       setentityvar(self, 0, NULL());
     }
   }
}

void MspawnT(void Name, float dx, float dy, int DevX, int DevY)
{ // Spawn certain entity and respawns if it dies
//Entity is directed toward player
   void self = getlocalvar("self");
   int map = getentityproperty(self,"map");
   int iHealth = getentityproperty(self,"health");
   void Entity = getentityvar(self, 5);
   void Player = getplayerproperty(0, "entity");

   if(Entity==NULL()){ // Entity is absent?
     void Spawn;
     int iR = rand()%30;
     int iDX;
     int iDY;

     if(DevX!=0){
       iDX = rand()%DevX;
     } else {
       iDX = 0;
     }

     if(DevY!=0){
       iDY = rand()%DevY;
     } else {
       iDY = 0;
     }

     if (iR > 0){ 
       Spawn = spawn02(Name, 320-dx+iDX, dy+iDY, 0);
       changeentityproperty(Spawn, "direction", 1);
     } else {
       Spawn = spawn02(Name, dx+iDX, dy+iDY, 0);
       changeentityproperty(Spawn, "direction", 0);
     }

     if(Player!=NULL()){
       int x = getentityproperty(Spawn,"x");
       int Py = getentityproperty(Player,"a");
       int z = getentityproperty(Spawn,"z");

       changeentityproperty(Spawn, "position", x, z, Py+dy+iDY);
     }
     changeentityproperty(Spawn, "map", map);
     changeentityproperty(Spawn, "health", iHealth);
     setentityvar(self, 5, Spawn);

   } else { // Entity is present
     int Health = getentityproperty(Entity, "health");

     if(Health<=0){ // Entity is dead?
       setentityvar(self, 5, NULL());
     }
   }
}

void beidle()
{// Go to IDLE animation!
    void self = getlocalvar("self");

    setidle(self, openborconstant("ANI_IDLE"));
}

void suicide()
{ // Suicide!!
    void self = getlocalvar("self");

    killentity(self); //Suicide!
}