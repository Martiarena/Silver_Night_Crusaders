void main()
{
   void self = getlocalvar("self");
      void plr = getentityproperty(self, "opponent");


   if (plr != NULL())
   {
   performattack(plr, openborconstant("ANI_FREESPECIAL9"));
   }
}