#strict

func IsBulletTarget()
{
	if(!Random(6)) return(1);
	//DoDamage(Random(4));
	return(0);
}

func Damage()
{
	if(GetDamage()>20)
	{
		if(GetAction() ne "Leck")SetAction("Leck");
		else Explode(20);
	}
}

func Leck()
{
	if(!Random(2))CreateParticle("Smoke2",-2,-10,RandomX(-2,2),-30,80,RGB(0,255,125));
	return(1);
}