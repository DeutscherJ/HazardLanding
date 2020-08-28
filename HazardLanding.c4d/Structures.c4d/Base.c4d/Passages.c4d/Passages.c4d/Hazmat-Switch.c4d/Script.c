#strict

// Locals
// 0 Tür 1
// 1 Tür 2
// 2 Wassereinlauf
// 3 Wasserablauf

protected Initialize:
  SetAction("OffEnd");
  return(1);
  
//Parameter 0 - Typ des zu kontrollierenden Objekts
public SearchTarget:
  if(GreaterThan(ObjectDistance(FindObject(Par(0),0,0,-1,-1)),500)) return(0);
  return(FindObject(Par(0),0,0,-1,-1));

//Parameter 1 - Typ des zu kontrollierenden Objekts
//Parameter 0 - Variable
public SetTarget:
  if(Equal(SearchTarget(Par(1)),0)) return(Message("Kein Ziel in Reichweite",this()));
  SetLocal(Par(0),SearchTarget(Par(1)));
  Sound("Click");
  Message("Ziel ist jetzt|%i",this(),GetID(Local(0)));
  return(Local(0));
  
public ControlUp:
  return(Off());  
public ControlDownSingle:
  return(On());  

  
private On:
  if(Not(SEqual(GetAction(),"OffEnd"))) return(0);
  Sound("Click");
  if (Not(GameCall("MainEnergySupply"))) return(And( Sound("Error"), Message("Nicht genug Energie.",this()) ));
  SetAction("On");
  return(1);

private Off:
  if(Not(SEqual(GetAction(),"OnEnd"))) return(0);
  Sound("Click");
  if (Not(GameCall("MainEnergySupply"))) return(And( Sound("Error"), Message("Nicht genug Energie.",this()) ));
  SetAction("Off");
  return(1);

EventOn2:
  ObjectCall(Local(0),"ControlRight");
  return(1);

EventOn3:
  ObjectCall(Local(1),"ControlRight");
  return(1);

EventOn4:
  ObjectSetAction(Local(3),"NoWater");
  ObjectSetAction(Local(2),"Water");
  return(1);


EventOff2:
  ObjectSetAction(Local(2),"NoWater");
  ObjectSetAction(Local(3),"Water");
  return(1);

EventOff3:
  ObjectCall(Local(0),"ControlLeft");
  return(1);
  
EventOff4:
  ObjectCall(Local(1),"ControlLeft");
  return(1);

protected Damage:
  if ( LessThan( GetDamage(), 20 ) ) return(0);
  CastObjects(DFLM,3,50,0,-5);
  CastObjects(SHRP,10,30,0,0);
  Sound("Discharge");
  Sound("Blast2");
  CreateObject(SWTD,0,8);
  Explode(15);  
  return(1);


Incineration:
  return(Extinguish());

Destroy:
  DoDamage(30);
  return(1);