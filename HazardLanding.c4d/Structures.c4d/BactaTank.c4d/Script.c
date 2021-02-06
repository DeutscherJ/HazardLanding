/*-- Bacta-Tank --*/

#strict

local pLight, pScreen;

func IsBactatank(){return(1);}

func IsBulletTarget()
{
	if(Random(60)) return(0);
	return(1);
}

func CheckEnergy()
{
	if(!pLight)
	{
		pLight = AddLightAmbience(40);
		pLight->~ChangeColor(RGBa(120,120,255,40));
		pLight->~TurnOn();
	}
	if(!GameCall("MainEnergySupply")) pLight->~TurnOff();
	else
	{
		for(var i=0; Contents(i); i++)
		{
			if(GetAlive(Contents(i)))
			{
				DoEnergy(1,Contents(i));
			}
		}
		pLight->~TurnOn();
	}
	return(1);
}

func Initialize()
{
  SetAction("beweg");
  SetPhase(Random(50));
  SetSolidMask (GetDefCoreVal("SolidMask","DefCore",GetID(),0),GetDefCoreVal("SolidMask","DefCore",GetID(),1),GetDefCoreVal("SolidMask","DefCore",GetID(),2),GetDefCoreVal("SolidMask","DefCore",GetID(),3),GetDefCoreVal("SolidMask","DefCore",GetID(),4),GetDefCoreVal("SolidMask","DefCore",GetID(),5));
  if(!TankContent()) SetEntrance(1);
  if(!pLight)
  {
	pLight = AddLightAmbience(40);
	pLight->~ChangeColor(RGBa(120,120,255,60));
	pLight->~TurnOn();
  }
  /*if(!pScreen)
  {
	pScreen = CreateObject(SCR4,13,5+28,GetOwner());
	RemoveObject(pScreen->FindObject2(Find_ID(FRME),Find_Distance(20)));
	SetCategory(1+8,pScreen);
	SetObjDrawTransform(400,200,0,0,300,0,pScreen);
  }*/
  return(1);
}

func ActivateEntrance(pByObj)
{
	if(!TankContent())
		return(SetEntrance(1));
	if(Contained(pByObj)==this())
		return(SetEntrance(1));
	return(1);
}

func Collection2(pObj)
{
	if(GetAlive(pObj))
		Set(pObj);
	return(1);
}

func Ejection(pObj)
{
	if(GetAlive(pObj))
	{
		if(LocalN("contentID",TankContent())==pObj) Unset();
		SetEntrance(1);
	}
	return(1);
}

func Damage()
{
	if(GetDamage()>10)
	Incinerate();
	return(1);
}

func Set(a,b,c)
{
	var pContent = TankContent();
	if(!pContent) pContent = CreateObject(BCCN,0,30,GetOwner());
	pContent->~Set(a,this());
	//LocalN("pTank",pContent)=this();
	SetEntrance(0);
	return(1);
}
func Unset()
{
	RemoveObject(TankContent());
	return(1);
}

func TankContent(){return(FindObject2(Find_ID(BCCN),Find_Func("IsTarget",this())));}

func ContentOffsetX(contentID)
{
	if(contentID==ST5B) return(-1);
	return(0);
}
func ContentOffsetX(contentID){return(0);}

func Destroy()
{
	Sound("Blast2");
	Sound("GlassBreak");
	for(var i=0; i<=9; i++)
	{
		CreateObject(TNF1,0,0,-1)->Set(i);
	}
	if(TankContent()) TankContent()->~Free();
	RemoveObject();
	return(1);
}

func Incineration()
{
	Destroy();
	return(1);
}
public func HazardBuilding(){return(2);}