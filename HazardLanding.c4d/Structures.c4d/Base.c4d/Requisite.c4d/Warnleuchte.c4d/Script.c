/*-- Neues Objekt --*/

#strict

protected Initialize:
  SetAction("leucht");
  return(1);

Energy:
  if (Not(GameCall("MainEnergySupply"))) return(SetAction("Idle"));
  SetAction("leucht");
  return();