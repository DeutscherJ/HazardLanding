/*-- Hauptbasis --*/

#strict
#include SDWU     // Script basiert auf Wohneinheit

local gun;


/* Initialisierung */

protected func Initialize()
{
  manager = CreateObject(BMAN,0,0,GetOwner());
  manager->Init(this());
  manager->InitLight(-2,-9);
  gun = CreateObject(AGG4,26,-4,GetOwner());
}

protected func Construction()
{
  basement = CreateObject(BS20,0,+8,GetOwner());
}
  
public func PreDestruction()
{
  if(gun) RemoveObject(gun);
  return(inherited());     // erledigt auch den "manager"
}


/* Steuerung */

protected func ContextWeaponChange(caller)
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

/* Eigenschaften */
public func IsEnergyConsumer()
{
	if(!gun)
		return(0);
	return(gun->~IsThreat());
}
public InfoBarSize: return(4);
public InfoBarPos:  return(6);
public GetMaxDamage: return(160);

