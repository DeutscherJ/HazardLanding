/*-- Krabbenpistole --*/

#strict
#include WEPN

local rocketupgrade,redlight,aiming,laserupgrade,laser;

public func HandSize()	{ return(1000); }
public func HandX()		{ return(4000); }
public func HandY()		{ return(-2000); }
/*
func OnSelect(int iFireMode)
{
	if(Contained())
		DoAmmo(ENAM,1,Contained());
	return(1);
} 
func OnDeselect(int iFireMode)
{
	if(Contained())
		DoAmmo(ENAM,-1,Contained());
	return(1);
} */

//func CheckAmmo(){return(1);}

func Initialize()
{
	DoAmmo(ENAM,1,this());
	return(_inherited());
}

public func FMData1(int data)
{
  if(data == FM_Name)      return("$Standard$");
  if(data == FM_AmmoID)    return(ENAM);
  if(data == FM_AmmoLoad)  return(1);

  if(data == FM_Reload)    return(25);
  if(data == FM_Recharge)  return(25);

  if(data == FM_AmmoUsage) return(1);
  if(data == FM_AmmoRate)  return(1);
  if(data == FM_Auto)      return(false);

  if(data == FM_Damage)    return(12);

  return(Default(data));
}

public func BotData1(int data)
{
  if(data == BOT_Range)    return(350);
  if(data == BOT_DmgType)  return(DMG_Energy);
  if(data == BOT_Power)    return(BOT_Power_2);

  return(Default(data));
}

public func Fire1()    // Projektil-Dauerfeuer
{ 
  var user = GetUser();
  var angle = user->~AimAngle(10) + RandomX(-1,+1);
  var x,y; user->WeaponEnd(x,y);
  var ammo = CreateObject(SHT2,x,y,GetController(user));
  // int iAngle, int iSpeed, int iDist, int iSize, int iTrail, int iDmg, int iDmgPrec, int iGlowSize, int iAPrec
  ammo->Launch(angle,300,600,6,100, GetFMData(FM_Damage, 1),0,80);

  DoAmmo(ENAM,1,this());
		
  // Effekte
  MuzzleFlash(70,user,x,y,angle,RGBa(96,64,255,0));
  // Sound
  Sound("EnergyRifle",0,ammo);
}