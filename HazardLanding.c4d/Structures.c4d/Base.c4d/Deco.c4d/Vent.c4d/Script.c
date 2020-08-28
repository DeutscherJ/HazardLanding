/*-- Ventilator --*/

#strict

func Initialize() {
  SetAction("Turn");
  return(1);
}

func Energy()
{
	if(GameCall("MainEnergySupply") && GetAction()eq"Stop")
	{
		var i= GetPhase();
		SetAction("Turn");
		SetPhase(i);
	}
	if(!GameCall("MainEnergySupply") && GetAction()ne"Stop")
	{
		var i= GetPhase();
		SetAction("Stop");
		SetPhase(i);
	}
}