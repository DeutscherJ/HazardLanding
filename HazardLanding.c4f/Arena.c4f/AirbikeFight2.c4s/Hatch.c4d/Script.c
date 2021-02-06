/*Luke*/

#strict

func Initialize()
{
  SetAction("HatchClosed");
  return(1);
}

CheckArea:
  // Clonk unter der Klappe suchen
  var pClonk;
  pClonk= FindObject(0, -10,10,24,20, OCF_CrewMember());
  // Automatisch �ffnen
  if (pClonk) return(ControlUp());
  ControlDownSingle();
  return(1);
  
// Schlie�t die Luke
ControlDownSingle:
  // Wenn Luke bereits zu, keine Aktion
  if (GetAction() eq "HatchClosed") return(0);
  // Sonst Luke schlie�en
  SetAction("CloseHatch");
  Sound("Airlock2");
  return(1);

// �ffnet die Luke
ControlUp:
  // Wenn Luke bereits offen, keine Aktion
  if (GetAction() eq "HatchOpen") return(0);
  // Sonst Luke �ffnen
  SetAction("OpenHatch");
  Sound("Airlock1");
  return(1);

// Entfernt die SolidMask    
RemoveSolidMask:
  SetSolidMask();
  return(1);

// Stellt SolidMask wieder her
PutSolidMask:
  SetSolidMask(0,12,19,2,0,12);
  return(1);