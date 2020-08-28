/*-- Maschinenfabrik --*/

#strict
#include BOB1

local basement, manager;
local factory;


/* Initialisierung */

protected func Initialize()
{
  manager = CreateObject(BMAN,0,0,GetOwner());
  manager->Init(this(), 1);
  manager->InitLight(-35,-17);
  // Fabrikobjekt
  factory = CreateObject(SOF3,0,0,GetOwner());
  factory->Init(this());
}

protected func Construction()
{
  basement = CreateObject(BS24,0,+8,GetOwner());
}
  
protected func Destruction()
{
  PreDestruction();
  if (basement) RemoveObject(basement);
}

public func PreDestruction()
{
  if (factory)
  {
    factory->StopProduction();
    RemoveObject(factory);
  }
  if (manager) RemoveObject(manager);
  return(inherited());
}


/* Steuerung */

protected func ContainedUp(caller)
{
  [Produktion]
  factory->KeyUp(caller);
}

protected func ContainedDig(caller)
{
  [Auftragsmen�]
  factory->KeyDig(caller);
}


/* Inhalt von Loren �bernehmen */

private func DoorClosed()
{
  var num = -1;
  var obj;
  while (obj = Contents(++num))
    if (obj->~IsLorry())
    {
      GrabContents(obj);
      SetCommand(obj,"Exit");
    }
}


/* Energie */

public EnoughEnergy: return(GetEnergy() >= 25);
public IsEnergyConsumer: return(1);


/* Eigenschaften */

public InfoBarSize: return(5);
public GetMaxDamage: return(140);

