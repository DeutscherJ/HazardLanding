/*-- Alarmleuchte --*/

#strict

protected Initialize:
  SetAction("leucht");
  return(1);

Energy:
  if (!fLight) return(SetAction("Idle"));
  SetAction("leucht");
  return();