/*-- Neues Objekt --*/

#strict

func Initialize() {
    Local(0)=0;
    Local(1)=-5;
    Local(2)=0;
    Local(3)=60;
	return(1);
}

public func IsWeaponProduct(){return(1);}
func IsMeleeWeapon(){return(1);}
func AnimatedWeapon(){return(1);}
func AnimateAngle(){return(Local(2));}
func AnimateAngle2(){return(Local(3));}
func XOffset(){return(Local(0));}
func YOffset(){return(Local(1));}
func Mirror()		 {return(1);}

func Hit()
{
	Sound("MetalHit*");
	return(1);
}

func Strength(){return(100);}

public func ControlThrow(pClonk)
{
  pClonk->~AlternativeBeat();
  return(1);
}