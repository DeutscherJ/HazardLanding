/*-- Flaggen können von innen (mindestens vom Besitzer) abgenommen werden --*/

#strict
#appendto DOOR
#appendto BOB1

func Context(pCaller)
{
  [$RemoveFlag$|Image=FLAG|Condition=HasFlag]
  HasFlag(pCaller)->SetAction("Idle");
  SetActionTargets(0,0,HasFlag(pCaller));
  return(1);
}

func HasFlag(pCaller)
{
	var pFlag = FindObject2(Find_ID(FLAG),Find_ActionTarget(this()));
	if(!pFlag) return(0);
	if(!FindObject(FGRV) && GetOwner(pFlag)!=GetOwner(pCaller) && GetOwner(pFlag)!=-1) return(0);//Ist die Flagge abnehmbar Regel nicht angestellt? Dann darf nur der Besitzer abnehmen
	return(pFlag);
}