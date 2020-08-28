/*-- Automatischer Schalter --*/

#strict
#include STND

func Initialize()
{
	SetVisibility(VIS_God);
	return(1);
}

func Timer()
{
	CreateParticle("NoGravSpark", RandomX(-5,5), RandomX(5,10), 0, -5, 35, RGBa(150, 255, 150, 100));
	var pClonk = FindObject2(Find_OCF(OCF_Alive),Find_Distance(15), Find_Func("OwnerIsRealPlayer"));
	if(pClonk)
	{
		Light(pClonk);
		RemoveObject();
		Sound("OOT_Get_SmallItem1");
	}
	return(0);
}

func IsLighter(){return(0);}