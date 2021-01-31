/*-- Neues Objekt --*/

#strict
local xLast, yLast, rLast;


func Initialize() {
    Local(0)=0;
    Local(1)=-5;
    Local(2)=0;
    Local(3)=60;
	Local(4)=6;
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
func Anim(r,x,y,pClonk)
{
	var dir = GetDir(pClonk)*2-1;
	xLast = x+Sin(r,Local(4))*dir;
	yLast = y-Cos(r,Local(4));
	rLast = r;
	return(1);
}

func AnimSchedule()
{
	if(!Contained()) 					return(0);
	if(Contents(0,Contained())!=this()) return(0);
	var action = GetAction(Contained());
	if(action ne "Walk" && action ne "Jump" && action ne "AlternativeBeat")
		return(0);
	if(Random(4))CreateParticle("PSpark",xLast,yLast,0,0,RandomX(900,1000),RGBa(180,180,255,175));
	var dir = GetDir(Contained())*2-1;
	CreateParticle("Plasma",xLast,yLast,Sin(rLast,40),-Cos(rLast,40)*dir,RandomX(-5,5)+80,RGBa(180,180,255,50));
	return(1);
}

func Entrance(pContained)
{
	if(Contents(0,pContained)!=this()) return(0);
	return(ShiftedTo(pContained));
}

func ShiftedTo(pClonk)
{
	if(!Contained()) 					return(0);
	if(!GetAlive(pClonk)) 				return(0);
	Sound("PlasmaStatic",0,this(),10,0,1);
	return(1);
}
func Unshifted(pClonk)
{
	Sound("PlasmaStatic",0,this(),0,0,-1);
	return(1);
}
func Departure()
{
	Sound("PlasmaStatic",0,this(),0,0,-1);
	return(1);
}