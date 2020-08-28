#strict
#include _SWT

// Locals
// 0 Erstes Zielobjekt
// 1 Zweites Zielobjekt (invertiert)

func ControlsObject(pObj){return(Local(1)==pObj||Local(1)==pObj);}
func IsHangarSwitch(){return(1);}

func Set(iDistance)
{
	if(!iDistance) iDistance = 200;
	var i=0;
	for(var target in FindObjects(Find_Func("IsHangarGate"),Find_Distance(iDistance)))
	{
		Local(i)=target;
		Message(Format("Ziel %d",i+1),target);
		Message("!",this());
		
		for(var otherSwitches in FindObjects(Find_Func("IsHangarSwitch"),Find_Distance(iDistance)))
		{
			Local(i,otherSwitches)=target;
			Message("!",otherSwitches);
		}
	
		i++;
	}
	
	return(1);
}

protected Initialize:
  SetAction("Off");
  return(1);
  
public SetTargets:
  SetLocal(0,Par(0));
  SetLocal(1,Par(1));
  return(1); 
  
/*public ControlUp:
  return(On());  
public ControlDownSingle:
  return(Off());*/
public ControlLeft:
  [÷ffnen]
  return(On());  
public ControlRight:
  [Schlieﬂen]
  return(Off());
  
private On:
  Sound("Click");
  if (Not(GameCall("MainEnergySupply"))) return(And( Sound("Error"), Message("Nicht genug Energie.",this()) ));
  SetAction("On");
  ObjectCall(Local(0),"ControlLeft");
  ObjectCall(Local(1),"ControlRight");
  return(1);
private Off:
  Sound("Click");
  if (Not(GameCall("MainEnergySupply"))) return(And( Sound("Error"), Message("Nicht genug Energie.",this()) ));
  SetAction("Off");
  ObjectCall(Local(0),"ControlRight");
  ObjectCall(Local(1),"ControlLeft");
  return(1);

private OnOff:
  if(GetComDir(Local(0)) == COMD_Right()) SetAction("Off");
  if(GetComDir(Local(0)) == COMD_Left()) SetAction("On");
  if(GetComDir(Local(1)) == COMD_Left()) SetAction("Off");
  if(GetComDir(Local(1)) == COMD_Right()) SetAction("On");
  PowerUpdate();
  return(1);

protected Damage:
  if ( LessThan( GetDamage(), 20 ) ) return(0);
  CastObjects(DFLM,3,50,0,-5);
  CastObjects(SHRP,10,30,0,0);
  Sound("Discharge");
  Sound("Blast2");
  CreateObject(HSWD,0,8);
  Explode(15);  
  return(1);

ControlDigDouble:
  if (Not(GameCall("MainEnergySupply"))) return(And( Sound("Error"), Message("Nicht genug Energie.",this()) ));
  return(SetAction("Countdown"));

Incineration:
  return(Extinguish());

Destroy:
  DoDamage(30);
  return();
  
func PowerUpdate()
{
	LightControl();
	if(GetAction()ne"NoPower")
		lastState = GetAction();
	if(!GameCall("MainEnergySupply"))
	{
		SetAction("NoPower");
	}
	else
	{
		if(GetAction()eq"NoPower") SetAction(lastState);
	}
	return(1);
}