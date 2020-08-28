/*-- Backlight --*/

#strict
#appendto BLGH

local fDamaged;

func IsBulletTarget(){return(!Random(20));}

func Damage()
{
	if(!Random(2))
	{
		fDamaged=1;
		ScheduleCall(this(),"Flacker",RandomX(2,8));
	}
	if(GetDamage()>100)
	{
		if(Random(2)) Destroy();
		else TurnOff();
	}
	return(1);
}

func Destroy()
{
	if(!Random(4))
		CreateObject(HOL2,0,0,-1);
	Explode(10);
	return(1);
}

func Flacker()
{
	if(GameCall("MainEnergySupply"))
	{
		if(!Random(2)) SwitchOnOff();
	}
	if(fDamaged) ScheduleCall(this(),"Flacker",RandomX(2,8));
	return(1);
}

func SwitchOnOff()
{
	if(bOn) TurnOff();
	else TurnOn();
	return(1);
}