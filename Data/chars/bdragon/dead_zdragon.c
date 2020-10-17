void main()
{// Death script for players with familiar
	void vEntity;
	int  iEntity;
	char iType;
	char iName;
	int  iMax = openborvariant("count_entities");
	void self = getlocalvar("self");

	for(iEntity=0; iEntity<iMax; iEntity++){
        vEntity = getentity(iEntity);
        iType   = getentityproperty(vEntity, "type");
		iName   = getentityproperty(vEntity, "name");

        if(iType == openborconstant("TYPE_ENEMY")){
	  		if (iName == "D._Zombi_" || iName == "Rib7" || iName == "Rib6" || iName == "Rib5" || iName == "Rib4" || iName == "Rib3" || iName == "Rib2" || iName == "Rib1") {

          	} else {
				damageentity(vEntity, self, 1000, 1, openborconstant("ATK_NORMAL30"));
	  		}
		}
	}
}