/*-- Sturmgewehr --*/

#strict
#include WEPN

local rocketupgrade,redlight,aiming,laserupgrade,laser;

public func IsWeaponProduct(){return(1);}
public func HandSize()	{ return(1000); }
public func HandX()			{ return(5000); }
public func HandY()			{ return(500); }

public func OnReload(int i)
{
	if(i == 1) Sound("AssaultRifleLoad");
	if(i == 2) Sound("AssaultRifleLoad");
	if(i == 3) Sound("PumpgunLoad");
	if(i == 4) Sound("GrenadeLoad");
	if(i == 5) Sound("GrenadeLoad");
	if(i == 6) Sound("Grab");
}

public func OnAimStart(int iFireMode)
{
	if(laser == 1) if(laserupgrade)
	{
	aiming = 1;
	redlight->TurnOn();
	}
	if(laser == 0) if(laserupgrade) redlight->TurnOff();
}

public func OnAimStop(int iFireMode)
{
	aiming = 0;
	if(laser == 1) if(laserupgrade) redlight->TurnOff();
	if(laser == 0) if(laserupgrade) redlight->TurnOff();
}

public func Check()
{
	if(laser == 0) return(0);
	if(aiming == 0) return(0);
  redlight->ChangeR(GetUser()->~AimAngle());
}

//Automatikfeuer - Kugeln
public func FMData1(int data)
{
	if(data == FM_Name)					return("$Fire1$");
	
  if(data == FM_AmmoID)				return(STAM);
  if(data == FM_AmmoLoad)			return(30);
  
  if(data == FM_Reload)				return(140);
  if(data == FM_Recharge)			return(6);

  if(data == FM_Auto)					return(true);
  
  if(data == FM_Damage)    return(9);

  return(Default(data));
}

// Einzelfeuer - Kugeln
public func FMData2(int data)
{
	if(data == FM_Name)					return("$Fire2$");
	
  if(data == FM_AmmoID)				return(STAM);
  if(data == FM_AmmoLoad)			return(30);
  
  if(data == FM_Reload)				return(140);
  if(data == FM_Recharge)			return(18);
  
  if(data == FM_Damage)    return(18);

  return(Default(data));
}

// Stossfeuer - Kugeln
public func FMData3(int data)
{
	if(data == FM_Name)					return("$Fire3$");
	
  if(data == FM_AmmoID)				return(STAM);
  if(data == FM_AmmoLoad)			return(30);
	if(data == FM_AmmoUsage)		return(3);
  
  if(data == FM_Reload)				return(100);
  if(data == FM_Recharge)			return(25);
  
  if(data == FM_Damage)    		return(9);

  return(Default(data));
}

// Granatenwerferaufsatz
public func FMData4(int data)
{
  if(data == FM_Name)     return("$Grenade$");
  if(data == FM_AmmoID)   return(GRAM);
  if(data == FM_AmmoLoad) return(2);

  if(data == FM_Reload)   return(140);
  if(data == FM_Recharge) return(90);

  if(data == FM_Damage)   return(30);
  if(data == FM_Condition) return(!rocketupgrade);

  return(Default(data));
}

// Raketenwerferaufsatz (Waffenteileupgrade)
public func FMData5(int data)
{
  if(data == FM_Name)   return("$Rocket$");
  if(data == FM_AmmoID)   return(MIAM);
  if(data == FM_AmmoLoad) return(1);
	if(data == FM_AmmoRate) return(2); //Es lassen sich zwei Raketen abfeuern
  if(data == FM_Reload)   return(140);
  if(data == FM_Recharge)   return(1);

  //if(data == FM_Aim)    return(1);

  if(data == FM_Condition) return(rocketupgrade);

  if(data == FM_Damage) return(20+RandomX(0,5));

  return(Default(data));
}

// Laserzielen an o. aus
public func FMData6(int data)
{
  if(laser == 1) if(data == FM_Name)   return("$LaserIsOn$");
  if(laser == 0) if(data == FM_Name)   return("$LaserIsOff$");
  if(data == FM_AmmoID)   return(ENAM);
  if(data == FM_AmmoLoad) return(1);
	if(data == FM_AmmoRate) return(1); 
  if(data == FM_Reload)   return(1);
  if(data == FM_Recharge)   return(1);
  if(data == FM_Icon) return(KLAS);

  //if(data == FM_Aim)    return(1);

  if(data == FM_Condition) return(laserupgrade);

  return(Default(data));
}

public func Fire1()
{
	var user = GetUser();
	var dir = GetDir(user)*2-1;
	var angle = user->AimAngle(12) + RandomX(-3,+3);
	var x,y;
	GetUser()->WeaponEnd(x,y);
	var ammo = CreateObject(SHT1,x,y,GetController(user));
	ammo->Launch(angle,300,650,5,75,GetFMData(FM_Damage, 1));
	
	MuzzleFlash(45,user,x,y-2,angle,RGB(255,175,0));
	BulletCasing(dir*1,0,-dir*14,-15,4);
	
	Sound("AssaultRifle");
}

public func Fire2()
{
	var user = GetUser();
	var dir = GetDir(user)*2-1;
	var angle = user->AimAngle(18) + RandomX(-1,+1);
	var x,y;
	GetUser()->WeaponEnd(x,y);
	var ammo = CreateObject(SHT1,x,y,GetController(user));
	ammo->Launch(angle,325,750,5,75,GetFMData(FM_Damage, 2));
	
	MuzzleFlash(55,user,x,y-2,angle,RGB(255,175,0));
	BulletCasing(dir*1,0,-dir*20,-14,4);
	
	Sound("AssaultRifle");
}

public func Fire3()
{ 
  var user = GetUser();
  var x,y; user->WeaponEnd(x,y);
  var angle = user->AimAngle(20);
  var ammo;

  for(var i=0; i<3; i++)
  {
    ammo = CreateObject(SHT1, x, y, GetController(user));
    ammo -> Launch(angle+RandomX(-5, 5), 300+Random(100), 300+Random(50), 4, 400, GetFMData(FM_Damage, 3), 1);

    BulletCasing(dir*1, 0, -dir*(Random(15)+5), -Random(15)-15, 3);
  }

  var dir = GetDir(user)*2-1;
  MuzzleFlash(RandomX(50,65), user,x,y,angle);

  // Sound
  Sound("PumpgunFire");
}


public func Fire4()
{
 LaunchGrenade(GREN, 75,Contained()->~AimAngle( 5)+RandomX( -5, 5),1);
}

public func LaunchGrenade(id idg, int speed, int angle, int mode) {
  var user = Contained();
  var dir = GetDir(user)*2-1;

  // Adjust angle
  angle = BoundBy(angle+GetYDir(user)*dir,-360,360);
  // calculate speed
  var xdir = Sin(angle,speed);
  var ydir = -Cos(angle,speed);

  var x,y;
  user->WeaponEnd(x,y);

  // create and launch
  var grenade=CreateObject(idg, x+xdir/10, y+ydir/10, GetController(user));
  grenade->Launch(xdir+GetXDir(user)/2, ydir+GetYDir(user)/2, GetFMData(FM_Damage, 4));

  // effect
  Sound("GrenadeFire");

  CreateParticle("Thrust",x,y,GetXDir(user),GetYDir(user),80,RGBa(255,200,200,0),0,0);

  for(var i=0; i<20; ++i) {
    CreateParticle("Smoke2",x+RandomX(-5,+5),y+RandomX(-5,+5),
                   GetXDir(user)+RandomX(0,xdir/4),GetYDir(user)+RandomX(0,ydir/4),
                   RandomX(80,140),RGBa(200,200,200,0),0,0);
  }
}

public func Fire5()
{ 
	LaunchRocket(MISS,Contained()->~AimAngle(20), GetFMData(FM_Damage, 5));
}

public func LaunchRocket(rid, angle, dmg) {

  var user = Contained();
  var x,y;
  user->WeaponEnd(x,y);
  // not too near to clonk
  x = x*3/2;
  y = y*3/2;

  var rocket = CreateObject(rid,x,y,GetController(user));
  rocket->Launch(angle, dmg);

  // Effekte
  var ax, ay, xdir, ydir;
  user->WeaponBegin(ax,ay);
  xdir = ax-x;
  ydir = ay-y;

  CreateParticle("Thrust",ax,ay,xdir/2,ydir/2,60,RGBa(255,200,200,0),0,0);

  for(var i=0; i<20; ++i) {
    var rand = RandomX(-10,+10);
    CreateParticle("Smoke2",ax+Sin(angle,rand),ay-Cos(angle,rand),
                   RandomX(0,2*xdir),RandomX(0,2*ydir),
                   RandomX(50,110),RGBa(220,200,180,0),0,0);
  }

  // Sound
  Sound("Rocket");
}

public func Fire6()
{
	if(laser == 1) { laser = 0; return(0); }
	if(laser == 0) { laser = 1; return(0); }
}

public func IsUpgradeable(id idUpgrade) {
  if(idUpgrade == KRFL) return("$KRFLUpgrade$");
  if(idUpgrade == KLAS) return("$KLASUpgrade$");
}

public func Upgrade(id idUpgrade)
 {
     var own = GetOwner(Contained());
  if(idUpgrade == KRFL)
  {
    SetFireMode(5);
    rocketupgrade = true;
    if(Contained()) HelpMessage(own,"$KRFLUpgraded$",Contained());
    return(true);
  }
  
  if(idUpgrade == KLAS)
  {
  	laserupgrade = true;
  	if(Contained()) HelpMessage(own,"$KLASUpgraded$",Contained());
  	redlight = AddLightCone(2000, RGB(255,0,0), GetUser());
		redlight->TurnOn();
		redlight->ChangeR(90);
		redlight->ChangeSizeXY(150,12000);
		redlight->TurnOff();
  	return(true);
  }
}

