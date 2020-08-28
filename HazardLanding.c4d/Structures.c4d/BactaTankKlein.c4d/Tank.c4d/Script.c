/*-- Separater Tank --*/

#strict
#include BCTG

public func IsCraneGrabable() { return(1); }

func IsReleased()
{
	var holder = FindObject2(Find_ID(BCTK),Find_Action("Kaputt"),Find_AtPoint());
	if(holder)
	{
		holder->~Initialize();
		LocalN("pTank",TankContent())=holder;
		RemoveObject();
	}
	return(1);
}
func Destroy()
{
	for(var i=0; i<=5; i++)
	{
		CreateObject(TNF2,0,30,-1)->Set(i);
	}
	if(TankContent()) TankContent()->~Free();
	RemoveObject();
	return(1);
}
func ContentAngle(contentID)
{
	if(contentID==MF5B) return(90);//Moff drehen
	return(0);
}