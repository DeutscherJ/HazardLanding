/*-- Chemiefabrik --*/

#strict
#include BOB1

local basement, manager;
local factory;


/* Factory-Objekt und Fundament erzeugen bzw. löschen */

protected Initialize:
  manager = CreateObject(BMAN,0,0,GetOwner());
  manager->Init(this());
  factory = CreateObject(SOF1,0,0,GetOwner());
  factory->Init(this(),15,0);
  return(1);

protected Construction:
  basement = CreateObject(BS14,0,+8,GetOwner());
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
  [Auftragsmenü]
  factory->KeyDig(Par(0));
  return(1);


/* Inhalt von Loren übernehmen */

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


/* Eigenschaften */

public InfoBarSize: return(2);
public GetMaxDamage: return(75);

