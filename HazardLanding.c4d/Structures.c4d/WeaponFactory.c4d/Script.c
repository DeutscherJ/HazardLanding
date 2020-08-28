/*-- Waffenfabrik --*/

#strict
#include BOB1

local basement, manager;
local factory;


/* Initialisierung */

protected Initialize:
  manager = CreateObject(BMAN,0,0,GetOwner());
  manager->Init(this(), 1);
  manager->InitLight(29,-3);
  // Fabrikobjekt
  factory = CreateObject(SOF2,0,0,GetOwner());
  factory->Init(this());
  return(1);

protected Construction:
  basement = CreateObject(BS17,0,+8,GetOwner());
  return(1);
  
protected Destruction:
  PreDestruction();
  if (basement) RemoveObject(basement);
  return(1);

public PreDestruction:
  if (factory)
  {
    factory->StopProduction();
    RemoveObject(factory);
  }
  if (manager) RemoveObject(manager);
  return(inherited());

/* Steuerung */

protected ContainedUp:
  [Produktion]
  factory->KeyUp(Par(0));
  return(1);

protected ContainedDig:
  [Auftragsmen�]
  factory->KeyDig(Par(0));
  return(1);


/* Inhalt von Loren �bernehmen */

private DoorClosed:
  var num = -1;
  var obj;
  while (obj = Contents(++num))
    if (obj->~IsLorry())
    {
      GrabContents(obj);
      SetCommand(obj,"Exit");
    }
  return(1);


/* Energie */

public EnoughEnergy: return(GetEnergy() >= 25);
public IsEnergyConsumer: return(1);


/* Eigenschaften */

public InfoBarSize: return(3);
public GetMaxDamage: return(90);

