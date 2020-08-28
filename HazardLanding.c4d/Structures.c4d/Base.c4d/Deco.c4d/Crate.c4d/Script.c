/*Kiste*/

#strict

func Hit()
{
  Sound("RockHit*");
  return(1);
}

func Damage()
{
  if (GetDamage()< 10) return(0);
  // Crack open
  while (Contents()) Exit(Contents());
  CastObjects(_CF1,1,20,0,-10);
  CastObjects(_CF2,5,20,0,-10);
  Sound("CrateCrack");
  Sound("Blast2");
  RemoveObject();  
  return(1);
}

public func IsCraneGrabable() { return(true); }