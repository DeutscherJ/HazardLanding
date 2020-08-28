/*-- Kokon --*/
#strict

func IsStippel(){return(true);}
func Initialize(){return(SetOwner(-1));}

func Activate(pClonk)
{
	return(Aufplatzen(pClonk));
}

//Timerfunktion
func Zyklus()
{  
  if(InLiquid()||(GBackSolid(0,-4)&&GBackSolid(0,4))||!Frei())
  {
	  DoDamage(5);
	  return(1);
  }
  Local(0)++;
  if (Local(0)>100) return(Stippel());//Schlüpfen
  return(1);
}

func Stippel()
{
  if(!Frei())									return(0);
  if(Contained())                          		return(0);
  if(FindObject(0,-10,-10,20,20,OCF_OnFire())) 	return(0);
  
  if(!FindObject(KG5B))
	  if(FindObject(ST5_))
		if(Local(0,FindObject(ST5_))<=5) return(Koenigin());
  
  if(ObjectCount(ST5B,-200,-200,400,400)<=5)
    if(ObjectCount(SK5B,-200,-200,400,400)<=5)
      if(!FindObject(KG5B))
        if(!Random(15)) return(Koenigin());
  
  if(ActiveMiffel())
    if(!Random(16)) return(Miffelbaum());

  if(ActiveMoff())
    if(!Random(8)) return(Moff());

  if(ActiveAlphaStippel())
    if(!Random(10)&&ObjectCount(AS5B)<5) return(AlphaStippel());
	
  CreateObject(ST5B,0,0,-1)->~Frisch();

  Sound("STKokon");
  return(RemoveObject());
}

func DoppelStippel()
{
  if(!Frei())                              return(0);
  if(Contained())                              return(0);
  if(FindObject(0,-10,-10,20,20,OCF_OnFire())) return(0);
  
  ObjectCall(CreateObject(ST5B),"Frisch");
  Stippel();
  return(1);
}

func Koenigin()
{
  if(!PathFree(GetX(),GetY(),(GetX()-50),GetY())) return(0);
  if(!PathFree(GetX(),GetY(),(GetX()+50),GetY())) return(0);
  if(ObjectCount(KG5B)>=Global(3))      		  return(0);
  CreateConstruction(KG5B,0,0,-1,50);
  Sound("STKokon");
  return(RemoveObject());
}

func Miffelbaum()
{
  if(!PathFree(GetX(),GetY(),(GetX()-50),GetY())) 	return(0);
  if(!PathFree(GetX(),GetY(),(GetX()+50),GetY())) 	return(0);
  if(!ActiveMiffel())                   			return(0);
  if(!ObjectCount(KG5B))           					return(0);
  if(FindObject(MB5B,-50,-50,100,100)) 				return(0);//steht hier shcon ein Miffelbaum?
  if(!GBackSolid(0,4))             					return(0);
  CreateConstruction(MB5B,0,5,-1,10);
  Sound("STKokon");
  return(RemoveObject());
}

func Moff()
{
  if(!ActiveMoff()) return(0);
  CreateObject(MF5B);
  Sound("STKokon");
  return(RemoveObject());
}

func AlphaStippel()
{
  if(!ActiveAlphaStippel()) return(0);
  CreateObject(AS5B)->~Frisch();
  return(RemoveObject());
}

func Frei(){return(!GBackSemiSolid());}

func Hit()
{
  if(Abs(GetXDir())+Abs(GetYDir())>60) return(Aufplatzen());//Bei einem tiefen Fall aufplatzen
  return(Sound("RockHit*"));
}

func Damage()
{
	if(GetDamage()>50) return(Aufplatzen());
}

func Aufplatzen(pClonk)
{
	Sound("MFSchaden*");
	if(GBackTunnel()&&GBackTunnel(-15,0)&&GBackTunnel(-15,0)&&GBackTunnel(15,0)&&GBackTunnel(0,-15))
	{
		var fleck=CreateObject(FLCK,0,20,-1);
		SetClrModulation(RGB(134,200,100),fleck);
		fleck->SetSize(20);
	}
	else
	{
		var fleck = CreateObject(FLCK,0,0,-1);
		SetClrModulation(RGB(134,200,100),fleck);
		fleck->SetSize(20);
	}
	CastObjects(FZ5B,10,50);
	RemoveObject();
	return(1);
}

func Entrance(pClonk)
{
	if(GetPlrExtraData(GetOwner(pClonk),"FSE_Skill")==1) return(Aufplatzen(pClonk));
}
func RejectEntrance(pClonk)
{
	if(GetPlrExtraData(GetOwner(pClonk),"FSE_Skill")==1) return(Aufplatzen(pClonk));
}