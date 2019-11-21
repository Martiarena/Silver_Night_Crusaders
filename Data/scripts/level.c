void main()
{
  void player = getplayerproperty(0, "entity");
  if(player==NULL()){
  	void player = getplayerproperty(1, "entity");
  	setentityvar(player, 2, NULL());
  }else{
  	setentityvar(player, 1, NULL());
  }
}