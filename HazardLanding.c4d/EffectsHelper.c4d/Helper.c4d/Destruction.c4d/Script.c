/*-- Gebäudeabriss --*/

#strict

local dest_speed;   // Abbaugeschwindigkeit (abhängig von Gebäudegröße)


public func DoDestruction(target)
{
  // Abbau einschalten
  SetAction("Destruct",target);
  // Aufruf im Gebäudescript
  if (GetOCF(target) & OCF_Fullcon())
  {
    target->~PreDestruction();
    ObjectSetAction(target,"Idle");
  }
  // alles aus dem Gebäude raus
  if (GetOCF(target) & OCF_Container())
  {
    var obj;
    while (obj = Contents(0,target))
      Exit(obj);
  }
  // einen Bausatz hier rein
  CreateContents(CNKT);
  // Leitungen trennen
  var linekits;
  linekits += Disconnect(PWRL);
  linekits += Disconnect(DPIP);
  linekits += Disconnect(SPIP);
  if (linekits)
    if (linekits > 1) Message("%d Leitungen abgenommen", target, linekits);
                 else Message("Eine Leitung abgenommen", target);
  while (--linekits >= 0)
    CreateContents(LNKT);
  // Baumaterial
  if (FindObject(CNMT))   // Regel Baumaterial
  {
    var i = -1;
    var objID, count;
    while (objID = GetComponent(0,++i,target))
      for (count = GetComponent(objID,0,target); count > 0; --count)
        CreateContents(objID); 
  }
  // Abbaugeschwindigkeit festlegen
  if (GetMass(target) >= 5000)  return(dest_speed = 1);
  if (GetMass(target) >= 3000)  return(dest_speed = 2);
  if (GetMass(target) >= 1500)  return(dest_speed = 3);
  dest_speed = 4;
  return(DestructionStep());
}

private func DestructionStep()
{
  // schrittweiser Abbau
  var target = GetActionTarget();
  DoCon(-dest_speed, target);
  // Abriss abgeschlossen
  if (!target)
  {
    // Inhalt rausrücken
    while (Contents())
      Exit(Contents(),Random(11)-5,5);
    // Hilfsobjekt wird nicht mehr benötigt
    return(RemoveObject());
  }
  // Clonks daran hindern, hier zu bauen
  var obj = FindObject(0,0,0,0,0, OCF_CrewMember(),"Build",GetActionTarget(),NoContainer());
  if (obj)
  {
    ObjectSetAction(obj,"Walk");
    SetCommand(obj,"None");
  }
  // Sound ausgeben
  if (!Random(3)) Sound("Build*");
  return(1);
}

private func Disconnect(lineID)
{
  var obj, linekits;
  while (obj = FindObject(lineID, 0,0,0,0, 0,"Connect",0,0, obj))
    // ist das Zielgebäude angeschlossen?
    if ((GetActionTarget(0,obj) == GetActionTarget()) ||
        (GetActionTarget(1,obj) == GetActionTarget()))
    {
      // Leitung löschen
      RemoveObject(obj);
      // beide Enden angeschlossen?
      if (GetID(GetActionTarget(0,obj)) == LNKT)  continue;
      if (GetID(GetActionTarget(1,obj)) == LNKT)  continue;
      ++linekits;   // als Ersatz ein Leitungsbausatz
    }
  return(linekits);
}

