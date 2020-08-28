/*-- Pfeil --*/

#strict
#include ARW2

local fade;

public func FadeMeOut()
{
	fade+=5;
	SetClrModulation(RGBa(255,255,255,fade));
	if(fade>200) RemoveObject();
	//else ScheduleCall(this(),"FadeMeOut",1);
	return(1);
}
