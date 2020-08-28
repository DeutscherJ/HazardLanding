/*-- Neues Script --*/

#strict
#appendto CLNK
#appendto HZCK

func Damage(a,b,c)
{
	CheckAutoHealing();
	return(_inherited(a,b,c));
}

public func OnDmg(a,b,c,d,e)
{
	CheckAutoHealing();
	return(_inherited());
}

func CheckAutoHealing()
{
	if(GetEnergy()<20)
		if(FindObject2(Find_Func("HealAmount"),Find_Container(this())))
			FindObject2(Find_Func("HealAmount"),Find_Container(this()))->~Activate(this());
	return(1);
}