/*-- Musikbox --*/

#strict

local off;

func Initialize()
{
  Sound("AsterixTechno",0,this(),100,0,1);
  return(1);
}

func Damage()
{
  if (GetDamage()< 30) return(0);
  // Crack open
  while (Contents()) Exit(Contents());
  CastObjects(_CF1,1,20,0,-10);
  CastObjects(_CF2,5,20,0,-10);
  Sound("CrateCrack");
  Sound("Blast2");
  Explode(20);  
  return(1);
}

public func EMPShock()
{
	off=0;
	ControlThrow();
	return(1);
}

func IsBulletTarget(){return(1);}
public func IsMachine() { return(true); } // Für EMP
public func IsCraneGrabable() { return(true); }

func ControlThrow()
{
	off=!off;
	if(off)
	{
	Sound("AsterixTechno",0,this(),100,0,-1);
	}
	else 
	Sound("AsterixTechno",0,this(),100,0,1);
	return(1);
}