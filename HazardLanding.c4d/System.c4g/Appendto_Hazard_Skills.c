/*-- Neues Script --*/

#strict
#appendto CLNK
#appendto HZCK
func Initialize(a,b,c,d,e,f)
{
	SetPlrExtraData(GetOwner(),"FSE_Skill",1);
	return(_inherited(a,b,c,d,e,f));
}
/*
func ContextRivive()
{
	[Skills]
	SetPlrExtraData(GetOwner(pClonk),"FSE_Skill",1);
//CreateMenu();
	return(1);
}
