/*-- Datendisk --*/

#strict

local plan1, plan2, plan3;


/* Initialisierung */

protected func Initialize()
{
  SetAction("Spin");
}

global func CreateDataDisc(pContainer,ID1, ID2, ID3)
{
	var pDisc = CreateContents(_DIS,pContainer);
	pDisc->~SetPlans(ID1, ID2, ID3);
	return(pDisc);
}

public func SetPlans(ID1, ID2, ID3)
{
  if (ID1)  plan1 = ID1;
  if (ID2)  plan2 = ID2;
  if (ID3)  plan3 = ID3;
}

protected func Activate(caller)
{
  if (plan1)  SetPlrKnowledge(GetOwner(caller), plan1);
  if (plan2)  SetPlrKnowledge(GetOwner(caller), plan2);
  if (plan3)  SetPlrKnowledge(GetOwner(caller), plan3);
  // drei Pläne
  if (plan3)
    Message("Baupläne erhalten:|%s|%s|%s",caller, GetName(0,plan1), GetName(0,plan2), GetName(0,plan3));
  // zwei Pläne
  else if (plan2)
    Message("Baupläne erhalten:|%s|%s",caller, GetName(0,plan1), GetName(0,plan2));
  // nur ein Plan
  else
    Message("Bauplan erhalten:|%s",caller, GetName(0,plan1));
  RemoveObject();
  return(1);
}

