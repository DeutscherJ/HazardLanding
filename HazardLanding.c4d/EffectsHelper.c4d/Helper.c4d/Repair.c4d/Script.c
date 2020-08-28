/*-- Reparatur --*/

#strict


/* Initialisierung */

public func Init(target)
{
  // schon ein Reparaturobjekt da?
  if (FindObject(GetID(), 0,0,0,0, 0,0,target))
    return(RemoveObject());
  // Ziel auch komplett?
  if (GetCon(target) < 100)
    return(RemoveObject());
  // Initialisieren
  SetPosition(GetX(target), GetY(target));
  SetVertex(0,0, GetVertex(0,0,target));
  SetVertex(0,1, GetVertex(0,1,target));
  SetAction("Repair", target);
}


/* Action-Call */

protected func DoRepair()
{
  // Gebäude reparieren
  var target = GetActionTarget();
  // fertig mit Reparatur
  if (!GetDamage(target))
    return(RemoveObject());
  // kein Geld oder ein EMP?
  if (!GetWealth(GetOwner(target)) || HasEMP(target))
    return(0);
  // Geld abziehen & reparieren
  DoWealth(GetOwner(target), -1);
  DoDamage(-5, target);
}


/* Ziel zerstört */

protected AttachTargetLost:
  return(RemoveObject());

