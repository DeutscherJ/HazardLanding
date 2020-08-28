/*--- Fackel ---*/
//CreateObject(FCKL)
#strict

public func Activate(clonk)
{ 
  CreateObject(TORC,0,16,GetOwner(clonk));
  RemoveObject();
  return(1);
}

func HitSound(){return(Sound("WoodHit*"));}
public func IsAnvilProduct(){ return(1);}

func Initialize() {
    Local(0)=-1;
    Local(1)=-1;
    Local(2)=-45;
    Local(3)=45;
	return(1);
}

func IsMeleeWeapon(){return(1);}
func AnimatedWeapon(){return(2);}
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

func Strength(){return(15);}

public func ControlThrow(pClonk)
{
  pClonk->~AlternativeBeat();
  return(1);
}