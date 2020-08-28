/*-- Bohrturm --*/

#strict
#include BOB2

local basement, manager;
local drillhead;


/* Initialisierung */

protected func Initialize()
{
  manager = CreateObject(BMAN,0,0,GetOwner());
  manager->Init(this(),1);
  // internes Fass als Zwischenlager
  CreateContents(BARL);
  PipeHeadCheck();
}

protected func Construction()
{
  basement = CreateObject(BSA1,0,+8,GetOwner());
}

protected func Destruction()
{
  PreDestruction();
  if (basement) RemoveObject(basement);
}

public func PreDestruction()
{
  if (manager)   RemoveObject(manager);
  if (drillhead) RemoveObject(drillhead);
  // Inhalt löschen
  var obj;
  while (obj = Contents())
    RemoveObject(obj);
  inherited();
}


/* Steuerung */

protected func ControlDig(caller)
{
  [Statusanzeige]
  if (Hostile(GetController(caller),GetOwner())) return(0);
  // Status anzeigen
  var max = GetMaxDamage();
  ShowInfoBar(IBRS, this(), max-GetDamage(), max, 5);
}

protected func ControlDownSingle(caller)
{
  [Bohren|Image=SPIH]
  if (Hostile(GetController(caller),GetOwner())) return(0);
  PipeHeadCheck();
  Sound("Click");
  if (GetEnergy() < 50) return(0);
  SetComDir(COMD_Down(), drillhead);
  ObjectSetAction(drillhead, "Drilling");
  SetPlrView(GetOwner(caller), drillhead);
}

protected func ControlDown(caller)
{
  [Bohren|Image=SPIH]
  if (Hostile(GetController(caller),GetOwner())) return(0);
  SetPlrView(GetOwner(caller), drillhead);
}

protected func ControlUp(caller)
{
  [Zurückziehen|Image=SPIH]
  if (Hostile(GetController(caller),GetOwner())) return(0);
  PipeHeadCheck();
  Sound("Click");
  if (GetEnergy() < 50) return(0);
  SetComDir(COMD_Up(), drillhead);
  ObjectSetAction(drillhead, "Level");
  SetPlrView(GetOwner(caller), drillhead);
}

protected func ControlLeft(caller)
{
  [Stop|Image=SPIH]
  if (Hostile(GetController(caller),GetOwner())) return(0);
  return(StopDrillHead(caller));
}

protected func ControlRight(caller)
{
  [Stop|Image=SPIH]
  if (Hostile(GetController(caller),GetOwner())) return(0);
  return(StopDrillHead(caller));
}

private func StopDrillHead(caller)
{
  Sound("Click");
  ObjectSetAction(drillhead, "Level");
  SetComDir(COMD_Stop(), drillhead);
  SetYDir(0, drillhead);
  SetPlrView(GetOwner(caller), drillhead);
}


/* Bohrkopf */

private func PipeHeadCheck()
{
  // bei Bedarf Bohrkopf und Leitung erzeugen
  if (!drillhead)
  {
    drillhead = CreateObject(SPIH,0,10,GetOwner());
    drillhead->Init(this());
    var pipe = CreateObject(SPIP,0,0,GetOwner());
    ObjectSetAction(pipe, "Connect", this(), drillhead);
  }
  // Pumpen
  if (GetAction() ne "Pumping")
    SetAction("Pumping", drillhead);
  return(drillhead);
}


/* Pumpkontrolle */

public func AcceptTransfer()
{
  return(EnoughEnergy());
}


/* Timer-Call */

private func CheckEnergy()
{
  // bei EMP ausschalten
  if (HasEMP()) SetAction("Idle");
  // Pump-Aktion nach EMP reeaktivieren
  if (ActIdle())
    if (EnoughEnergy()) SetAction("Pumping");
                   else return(0);
  // Energieverbrauch
  DoEnergy(-10);
  // keine Energie mehr?
  if (!GetEnergy()) SetAction("Idle");
}


/* Energie */

public EnoughEnergy: return(GetEnergy() >= 10);
public IsEnergyConsumer: return(1);


/* Eigenschaften */

public InfoBarSize:  return(1);
public GetMaxDamage: return(60);

