#strict

Initialize:
  SetAction("Drehen");
  SetPhase(Random(20));
  SetPhysical("Float",Random(100)+100,2);
  SetComDir(COMD_Down());
  return(1);

Drehen:
  if(!GBackSemiSolid(0,1)) return(0);
  return(DoCon(-10));