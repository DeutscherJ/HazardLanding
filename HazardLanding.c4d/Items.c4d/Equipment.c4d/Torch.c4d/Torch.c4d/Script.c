/*--- Fackel ---*/
//CreateObject(FCKL)
#strict
local xLast, yLast;

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
	Local(4)=5;
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

func Anim(r,x,y,pClonk)
{
	var dir = GetDir(pClonk)*2-1;
	xLast = x+Sin(r,Local(4))*dir;
	yLast = y-Cos(r,Local(4));
	return(1);
}

func AnimSchedule()
{
	if(!Contained()) return(0);
	if(Contents(0,Contained())!=this()) return(0);
	var action = GetAction(Contained());
	if(action ne "Walk" && action ne "Jump" && action ne "AlternativeBeat")
		return(0);
	CreateParticle("PSpark",xLast,yLast,0,0,RandomX(900,1000),RGBa(255,180,150,165)); 
	if(!Random(36)) CreateParticle("Smoke",xLast,yLast,0,0,RandomX(140,190),RGBa(200,200,180,200));
	CreateParticle("Fire2",xLast+RandomX(-1,1),yLast+RandomX(-1,1),RandomX(-1,1),-RandomX(1,8),RandomX(90,120),RGBa(255,RandomX(130,150),100,RandomX(140,160)));
	return(1);
}