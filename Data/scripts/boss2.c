void main()
{
   void self = getlocalvar("gevaudan");
      void plr = getentityproperty(self, "opponent");


   if (plr != NULL())
   {
   performattack(plr, openborconstant("ANI_FOLLOW1"));
   }
}