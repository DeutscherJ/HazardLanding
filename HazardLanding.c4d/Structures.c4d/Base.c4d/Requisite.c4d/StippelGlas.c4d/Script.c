/*-- Stippelglas --*/

#strict

func IsBulletTarget()
{
	if(Random(6)) return(0);
	DoDamage(1);
	return(0);
}

func Initialize()
{
  SetAction("beweg");
  return(1);
}

func Damage()
{
  Incinerate();
  return(1);
}