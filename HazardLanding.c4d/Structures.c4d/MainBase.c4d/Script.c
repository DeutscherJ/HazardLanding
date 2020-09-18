/*-- Hauptbasis --*/

#strict
#include SDWU     // Script basiert auf Wohneinheit

local weapon;


/* Initialisierung */

protected func Initialize()
{
  manager = CreateObject(BMAN,0,0,GetOwner());
  manager->Init(this());
  manager->InitLight(-2,-9);
  SetR(180,CreateObject(SAG4,15,-18,GetOwner()));
}

protected func Construction()
{
  basement = CreateObject(BS20,0,+8,GetOwner());
}
  
public func PreDestruction()
{
  if (weapon) RemoveObject(weapon);
  return(inherited());     // erledigt auch den "manager"
}

/* Steuerung 

protected func ContainedDig(caller)
{
  [Waffenwechsel]
  // nichts tun, wenn hier ein Uplink drauf ist
  if (GetUplink())
    return(inherited(caller));
  SelectWeapons(caller);
}

public func SelectWeapons(caller)
{
  [Waffenwechsel]
  // Menü zum Waffenwechsel
  CreateMenu(GetID(), caller, 0,2, "Waffenwechsel");
  AddMenuItem("keine Waffe", "ChangeWeapon", SYNW,caller, 0,0,0, 128,0, GetCost());
  if (GetPlrKnowledge(GetOwner(),SLSW))
    AddMenuItem("Laser",          "ChangeWeapon", SLSW,caller, 0,0,0, 128,0, GetCost(SLSW));
  if (GetPlrKnowledge(GetOwner(),STW1))
    AddMenuItem("Maschinengewehr","ChangeWeapon", STW1,caller, 0,0,0, 128,0, GetCost(STW1));
  if (GetPlrKnowledge(GetOwner(),STW4))
    AddMenuItem("Vulcan-Waffe",   "ChangeWeapon", STW4,caller, 0,0,0, 128,0, GetCost(STW4));
  if (GetPlrKnowledge(GetOwner(),STW3))
    AddMenuItem("Elektrowaffe",   "ChangeWeapon", STW3,caller, 0,0,0, 128,0, GetCost(STW3));
}

public HasWeaponSelection: return(1);   // sagt dem Uplink, dass hier Waffenwechsel möglich ist

protected func ChangeWeapon(ID)
{
  // nochmal das gleiche gewählt?
  if (ID == SYNW) ID = 0;
  if (ID == GetID(weapon)) return(0);
  if (!ID && !weapon)      return(0);
  // genug Geld da?
  var cost = GetCost(ID);
  if (GetWealth(GetOwner()) < cost)
  {
    PlayerMessage(GetOwner(), "Nicht genug Geld!", this());
    Sound("Error");
    return(0);
  }
  // bezahlen
  DoWealth(GetOwner(), -cost);
  if (cost > 0) Sound("UnCash");
           else Sound("Cash");
  // alte Waffe weg
  if (weapon)
    RemoveObject(weapon);
  // keine draufsetzen?
  if (!ID) return(1);
  // neue Waffe erzeugen
  weapon = CreateObject(ID, 0,-100,GetOwner());
  weapon->Init(this(),1,-41,-19);
  return(1);
}

private func GetCost(ID)
{
  // Waffe bereits verwendet?
  if (!ID && !weapon)      return(0);
  if (ID == GetID(weapon)) return(0);
  // Kostenberechnung
  var cost = 0;
  if (ID)     cost += GetValue(0,ID);         // neue Waffe kostet was
  if (weapon) cost -= GetValue(weapon)*4/5;   // alte wird für 80% des Wertes verkauft
  return(cost);
}


/* Eigenschaften */

public IsEnergyConsumer: return(weapon != 0);
public InfoBarSize: return(4);
public InfoBarPos:  return(6);
public GetMaxDamage: return(160);

