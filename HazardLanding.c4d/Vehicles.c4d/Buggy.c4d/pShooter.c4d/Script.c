/*-- Neues Objekt --*/

#strict
#include WEPN

func Set(pObj)
{
	SetAction("Exist",pObj);
}

public func FMData1(int data)
{
	if(data == FM_Name)			return("Normal");
	if(data == FM_Icon)			return(MIWP);	
	if(data == FM_AmmoID)		return(STAM);
	if(data == FM_AmmoLoad)		return(120);

	if(data == FM_Reload)		return(260);
	if(data == FM_Recharge)		return(4);

    if(data == FM_Auto)       return(true);
	
	return(Default(data));
}

public func Fire1()				 // fire the cannon
{ 
	// dir
	var angle = GetActionTarget()->GetAimAngle()+RandomX(-5,5);
	// Schuss an der Mündung der Waffe erstellen...
	var dir= -(GetDir(GetActionTarget())*2-1);
	var x=-3*dir+Sin(angle,14),y=-9-Cos(angle,17);
	var ammo = CreateObject(SHT1,x,y,GetOwner(Contents(0,GetActionTarget())));
    ammo->Launch(angle,300,600,4,600,5);//die letzte Zahl ist die Stärke

    // Effekte
    MuzzleFlash(RandomX(20,50),this(),x,y,angle);
  
    BulletCasing(6*dir,-5,-dir*Cos(angle-35*dir,40+Random(20)),dir*Sin(angle-35*dir,40+Random(20)),5);
	return(1);

}

/*public func OnReload()
{
  Sound("MiniLoad");
}*/

public func OnAutoStart()
{
  Sound("MiniGun",0,0,0,0,1);
  Sound("MiniTurn",0,0,0,0,1);
}

public func OnAutoStop()
{
  Sound("MiniGun",0,0,0,0,-1);
  Sound("MiniTurn",0,0,0,0,-1);
}