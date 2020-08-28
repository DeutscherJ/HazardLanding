/*-- Eingang für gedrehte Objekte --*/

#strict

public func ActivateEntrance(pClonk)
{
  SetCommand(pClonk,"None");
  if(GetActionTarget()->~ Entering()) Enter(GetActionTarget(),pClonk);
  return(0);
}
