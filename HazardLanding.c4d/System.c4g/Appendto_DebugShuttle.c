/*-- Macht, dass das Shuttle auch richtig landet, und auﬂerdem den Eingang nicht immer verbarrikadiert --*/

#strict
#appendto SHTL

protected func ContainedDownDouble()
{
    [$TxtDown$|Image=SAN1:3]
	if (IsFlying()  || IsTurning()) {
		txspeed = 0;
	}
	if(Stuck()) ContactBottom();
	return 1;
}

//Immer Clonks reinlassen
func CrewInside(){return(0);}

//Automatisches Verlassen
func ContactBottom()
{
	//UpdateTransferZone();
	return(_inherited());
}

func ExitCommand(pClonk)
{
	if(Contained(pClonk)==this())
		ContainedDown(pClonk);
	return(1);
}
//protected func UpdateTransferZone() { return(SetTransferZone(-100,-100,200,200));}
