/*-- Neues Script --*/

#strict

global func FindStippelTargetDistance(iDistance,pStippel)
{
	var pTarget;
	if(GetOwner(pStippel)>=0) //Kein Besitzer?
		pTarget = FindObject2(Find_Distance(iDistance),
		Find_Or(Find_OCF(OCF_Alive()),Find_And(Find_Func("IsThreat"),Find_Func("IsMachine")),Find_Func("CheckEnemyObject",GetOwner(pStippel))),
		Find_NoContainer(),
		Find_Or(Find_Owner(-1),Find_Hostile(GetOwner(pStippel))),
		Find_Not(Find_Func("IsDying")));
	else
		pTarget = FindObject2(Find_Distance(iDistance), Find_Or(Find_OCF(OCF_CrewMember()),Find_And(Find_Func("IsThreat"),Find_Func("IsMachine")),Find_Func("CheckEnemyObject",GetOwner(pStippel))),Find_NoContainer(),Find_Not(Find_Func("IsDying")));
	return(pTarget);
}