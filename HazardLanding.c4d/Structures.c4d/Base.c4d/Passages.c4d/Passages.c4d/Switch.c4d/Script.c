#strict

// Locals
// 0 Erstes Zielobjekt
local lastState, pLight;
 
protected Initialize:
	SetAction("On");
	UpdateTransferZone();
	return(1);

func ControlTransfer(object pObj, int iTx, int iTy)
{
	if(Local()->~IsClosed())
	{
		//var control = FindObject2(Find_Func("ControlsObject",this()),Find_Func("PathFree",pObj));
		AddCommand(pObj,"Call",this(),pObj,0,0,0,"ControlUp");
		AddCommand(pObj,"Grab",this());
		return(1);
	}
}

public func UpdateTransferZone()
{
  SetTransferZone(-10,-10,20,20);
}

func IsSwitch(){return(1);}

func LightControl()
{
	if(!pLight) pLight = AddLightAmbience(20);
	if(GetAction()eq"NoPower")
		return(pLight->~TurnOff());
	pLight->~TurnOn();
	if(GetAction()eq"On")
		pLight->~ChangeColor(RGBa(0,255,0,80));
	if(GetAction()eq"Off")
		pLight->~ChangeColor(RGBa(255,0,0,80));
	return(1);
}

func Set(iDistance)
{
	if(!iDistance) iDistance = 80;
	var target = FindObject2(Find_Func("IsGate"),Find_Distance(iDistance));
	if(!target) return(Message("Kein Ziel gefunden",this()));
	Local(0)=target;
	Message("Ziel",target);
	Message("!",this());
	
	for(var otherSwitches in FindObjects(Find_Func("IsSwitch"),Find_Distance(iDistance)))
	{
		Local(0,otherSwitches)=target;
		Message("!",otherSwitches);
	}
	return(1);
}

//Parameter 0 - Typ des zu kontrollierenden Objekts
public SearchTarget:
  if(GreaterThan(ObjectDistance(FindObject(Par(0),0,0,-1,-1)),500)) return(0);
  return(FindObject(Par(0),0,0,-1,-1));

//Parameter 0 - Typ des zu kontrollierenden Objekts
public SetTarget:
  if(Equal(SearchTarget(Par(0)),0)) return(Message("Kein Ziel in Reichweite",this()));
  SetLocal(0,SearchTarget(Par(0)));
  Sound("Click");
  Message("Ziel ist jetzt|%i",this(),GetID(Local(0)));
  return(Local(0));
  
public ControlUp:
  return(On());  
public ControlDownSingle:
  return(Off());  
//public ControlLeft:
//  return(On());  
//public ControlRight:
//  return(Off());
  
private On:
  Sound("Click");
  if (Not(GameCall("MainEnergySupply"))) return(And( Sound("Error"), Message("Nicht genug Energie.",this()) ));
  SetAction("On");
  ObjectCall(Local(0),"ControlLeft");
  return(1);
private Off:
  Sound("Click");
  if (Not(GameCall("MainEnergySupply"))) return(And( Sound("Error"), Message("Nicht genug Energie.",this()) ));
  SetAction("Off");
  ObjectCall(Local(0),"ControlRight");
  return(1);

private OnOff:
  if(GetAction() eq "Countdown") return(0);
  if(GetComDir(Local(0)) == COMD_Down()) SetAction("Off");
  if(GetComDir(Local(0)) == COMD_Up()) SetAction("On");
  PowerUpdate();
  return(1);

protected Damage:
  if (GetDamage()<20) return(0);
  CastObjects(DFLM,3,50,0,-5);
  CastObjects(SHRP,10,30,0,0);
  Sound("Discharge");
  Sound("Blast2");
  CreateObject(SWTD,0,8);
  Explode(15);  
  return(1);

ControlDigDouble:
  if (Not(GameCall("MainEnergySupply"))) return(And( Sound("Error"), Message("Nicht genug Energie.",this()) ));
  return(SetAction("Countdown"));

Incineration:
  return(Extinguish());

Destroy:
  DoDamage(30);
  return(1);
  
func PowerUpdate()
{
	if(GetAction()ne"NoPower")
		lastState = GetAction();
	if(!GameCall("MainEnergySupply"))
		SetAction("NoPower");
	else
		if(GetAction()eq"NoPower")
			SetAction(lastState);
	LightControl();
	return(1);
}