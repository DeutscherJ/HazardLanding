/*-- Wachturm --*/

#strict
#include BOB1

local basement, manager;
local gun;


/* Initialisierung */

protected func Initialize()
{
  manager = CreateObject(BMAN,0,0,GetOwner());
  manager->Init(this(), 1);
  manager->InitLight(-3,-19);
  gun = CreateObject(AGG4,0,-23+15,GetOwner());
}

protected func Construction()
{
  basement = CreateObject(BS13,0,+8,GetOwner());
}

protected func Destruction()
{
  PreDestruction();
  if (basement) RemoveObject(basement);
}

public func PreDestruction()
{
  if (manager) RemoveObject(manager);
  if(gun) RemoveObject(gun);
  inherited();
}


/* Steuerung */

protected func ContainedDig(caller)
{
  [Waffenwechsel]
  CreateMenu(GetID(), caller, 0,2, "Waffenwechsel");
  if(Contents(0,gun)) AddMenuItem("Waffe abnehmen", "RemoveWeapon", SYNW,caller, 0,0,"keine Bewaffnung");
  
  var weaponArray = FindObjects(Find_Func("IsWeapon"),Find_Or(Find_Container(caller),Find_Container(this())));
  for(var weapon in weaponArray)
  {
		AddMenuItem(Format("%s von %s",GetName(weapon),GetName(Contained(weapon))), Format("ChangeWeapon(Object(%d))",ObjectNumber(weapon)), GetID(weapon),caller, 0,0,"keine Bewaffnung", 3,weapon);
  }
  return(1);
}

func RemoveWeapon()
{
	if(Contents(0,gun))
	{
		Enter(this(),Contents(0,gun));
		gun->~TurnOff();
	}
	Sound("Connect");
	return(1);
}

func ChangeWeapon(obj)
{
	RemoveWeapon();
	Enter(gun,obj);
	gun->~Arm(GetID(obj));
	gun->~TurnOn();
	return(1);
}
/* Clonks im Wachturm */

protected func Collection2(clonk)
{
  // neuen Clonkschatten erzeugen
  if (!(GetOCF(clonk) & OCF_CrewMember()))
    return(0);
  CreateObject(STOF,0,0,GetOwner())->Init(this(), clonk);
  return(1);
}

protected func Ejection(clonk)
{
  // Clonkschatten löschen
  var figure;
  while (figure = FindObject(STOF, 0,0,0,0, 0,0,this(), 0,figure))
    if (figure->GetClonk() == clonk)
      return(RemoveObject(figure));
  return(1);
}


/* Energie */

public func EnoughEnergy()
{
  if(!gun) return(1);
  if (gun->~IsThreat())
    return(GetEnergy() > 2);
  return(GetEnergy());
}


/* Eigenschaften */

public func IsEnergyConsumer()
{
	if(!gun)
		return(0);
	return(gun->~IsThreat());
}
public InfoBarSize: return(2);
public GetMaxDamage: return(75);

