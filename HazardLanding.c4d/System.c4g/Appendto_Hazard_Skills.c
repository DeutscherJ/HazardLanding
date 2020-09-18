/*-- Neues Script --*/

#strict
#appendto CLNK
#appendto HZCK
func Initialize(a,b,c,d,e,f)
{
	SetPlrExtraData(GetOwner(),"FSE_Skill",1);
	return(_inherited(a,b,c,d,e,f));
}

func ContextSkill(blar,j)
{
	[Fähigkeiten]
	
	CreateMenu(HZCK, this(), this());
	
	var def = CreateObject(SK5B, 0,0, -1);
	if(GetPlrExtraData(GetOwner(),"FSE_Skill")==1)
		{
		SetGraphics("Chosen", def, WPCH, 1, GFXOV_MODE_Picture);
		SetObjDrawTransform(650,0,5000,0,650,5000, def, 1);
		}
	var i=0;
	if(GetPlrExtraData(GetOwner(),"FSE_Skill")==1)
		AddMenuItem("Deaktiviere: Kokons zerbrechen", "SetSkill",SK5B, this(), 0, i, "Wenn diese Fähigkeit aktiviert wird, zerbricht der Clonk bei Kontakt mit Kokons diese automatisch.", 4, def);
	else
		AddMenuItem("Aktiviere: Kokons zerbrechen", "SetSkill",SK5B, this(), 0, i, "Wenn diese Fähigkeit aktiviert wird, zerbricht der Clonk bei Kontakt mit Kokons diese automatisch.", 4, def);
	RemoveObject(def);
	SelectMenuItem(j);
	return(1);
}

func SetSkill(skillID,iVal)
{
	var szSkill = "";
	if(skillID==SK5B)
		szSkill="FSE_Skill";
	if(GetPlrExtraData(GetOwner(),"FSE_Skill")==1) SetPlrExtraData(GetOwner(),szSkill,2);
	else SetPlrExtraData(GetOwner(),szSkill,1);
	ContextSkill(0,iVal);
	return(1);
}

/*
func ContextRivive()
{
	[Skills]
	SetPlrExtraData(GetOwner(pClonk),"FSE_Skill",1);
//CreateMenu();
	return(1);
}
