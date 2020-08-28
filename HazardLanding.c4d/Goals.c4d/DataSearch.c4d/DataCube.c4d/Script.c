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
	{
		Saved(pContainer);
	}
	return(1);
}


func Saved(pClonk)
{
	Log("%s%d geborgen",GetName(),ObjectNumber());
	RemoveObject();
	return(1);
}

func RejectEntrance(pClonk)
{
	RemoveObject();
	return(0);//Hineinversetzen verhinden
}

func Destruction()
{
	Log("%s wurde eingesammelt",GetName());
	CastParticles("PxSpark",10,50,0,0,100,100,ObjectColor());
	Sound("SpellSysCombo1");
	return(1);
}