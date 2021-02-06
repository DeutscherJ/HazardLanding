/*Schalter*/

#strict

// Locals
// 0 Erstes Zielobjekt

static fLight;

protected func Initialize()
{
  SetAction("On");
  fLight=1;
  return(1);
}
  
//Parameter 0 - Typ des zu kontrollierenden Objekts
public func SearchTarget(idTarget)
{
  if(ObjectDistance(FindObject(idTarget,0,0,-1,-1))<500) return(0);
  return(FindObject(idTarget,0,0,-1,-1));
}

//Parameter 0 - Typ des zu kontrollierenden Objekts
public SetTarget:
  if(SearchTarget(Par(0))==0) return(Message("Kein Ziel in Reichweite",this()));
  SetLocal(0,SearchTarget(Par(0)));
  Sound("Click");
  Message("Ziel ist jetzt|%i",this(),GetID(Local(0)));
  return(Local(0));
  
public ControlUp:
  return(On());  
public ControlDownSingle:
  return(Off());
  
private On:
  Sound("Click");
  if (!GameCall("MainEnergySupply")) return(And( Sound("Error"), Message("Nicht genug Energie.",this()) ));
  SetAction("On");
  fLight=1;
  return(1);
  
private Off:
  Sound("Click");
  if (!GameCall("MainEnergySupply")) return(And( Sound("Error"), Message("Nicht genug Energie.",this()) ));
  SetAction("Off");
  fLight=0;
  return(1);

private OnOff:
  if(GetAction() eq "Countdown") return(0);
  if(GetComDir(Local(0)) == COMD_Down()) SetAction("Off");
  if(GetComDir(Local(0)) == COMD_Up()) SetAction("On");
  
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

ControlDigDouble:
  if (Not(GameCall("MainEnergySupply"))) return(And( Sound("Error"), Message("Nicht genug Energie.",this()) ));
  return(SetAction("Countdown"));

Incineration:
  return(Extinguish());

Destroy:
  DoDamage(30);
  return(1);