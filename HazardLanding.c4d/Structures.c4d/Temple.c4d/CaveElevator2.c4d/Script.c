/*-- Fahrstuhl --*/

#strict

func CreateCage()
{
	var pCage = CreateObject(_CAG,9,70,GetOwner());
	SetAction("LiftCase",pCage);
	return(pCage);
}
