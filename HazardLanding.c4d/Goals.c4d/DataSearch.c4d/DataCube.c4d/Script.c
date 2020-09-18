#strict

func Initialize()
{
  SetAction("Spin");
  return(1);
}

func ObjectColor(){return(RGB(255,255,255));}
func DataCube(){return(1);}

func Entrance(pContainer)
{
	if(GetID(pContainer)==SHTL)
		Saved(pContainer);
	return(1);
}


func Saved(pClonk)
{
	Log("%s%d geborgen",GetName(),ObjectNumber());
	CastParticles("PxSpark",10,50,0,0,100,100,ObjectColor());
	Sound("SpellSysCombo1");
	RemoveObject();
	return(1);
}

func RejectEntrance(pClonk)
{
	if(GetAlive(pClonk) && iDataCubeCollectionType)
		Saved(pClonk);
	return(0);//Hineinversetzen verhinden
}