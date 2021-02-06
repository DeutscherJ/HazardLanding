#strict
#include BCTG

public func IsCraneGrabable() { return(1); }

func IsGrabbed()
{
	SetAction("Kaputt");
	//CreateObject(BCTN,0,0,GetOwner());
	//Unset();
	var tank = CreateObject(BCTN,-2,27,GetOwner());
	LocalN("pTank",TankContent())=tank;
	SetSolidMask(); 
	return(tank);
}

func Destroy()
{
	Sound("Blast2");
	Sound("GlassBreak");
	SetAction("Kaputt");
	var tank = CreateObject(BCTN,-2,27,GetOwner());
	tank->~Destroy();
	if(TankContent()) TankContent()->~Free();
	SetSolidMask(); 
	RemoveObject();
	return(1);
}
func ContentAngle(contentID)
{
	if(contentID==MF5B) return(90);//Moff drehen
	return(0);
}
public func HazardBuilding(){return(2);}