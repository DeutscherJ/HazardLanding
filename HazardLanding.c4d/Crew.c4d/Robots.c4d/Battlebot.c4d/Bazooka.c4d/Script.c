/*-- Bazooka --*/

#strict

#include WEPN

public func FMData1(int data)
{
  if(data == FM_Name)       return("MG");
  if(data == FM_AmmoID)     return(STAM);
  if(data == FM_AmmoLoad)   return(50);

  if(data == FM_Reload)     return(260);
  if(data == FM_Recharge)   return(3);

  if(data == FM_AmmoUsage)  return(1);
  if(data == FM_AmmoRate)   return(2);
  if(data == FM_Auto)       return(true);
  if(data == FM_Aim)        return(-1);

  if(data == FM_Damage)     return(3);

  return(Default(data));
}

public func FMData2(int data)
{
  if(data == FM_Name)       return("Raketen");
  if(data == FM_AmmoID)     return(MIAM);
  if(data == FM_AmmoLoad)   return(10);

  if(data == FM_Reload)     return(80);
  if(data == FM_Recharge)   return(10);

  if(data == FM_AmmoUsage)  return(1);
  if(data == FM_AmmoRate)   return(1);
  if(data == FM_Auto)       return(true);
  if(data == FM_Aim)        return(-1);

  if(data == FM_Damage)     return(3);

  return(Default(data));
}

public func Fire1()
{
	Contained()->~SpezShot();
	return(1);
}

public func Fire2()
{
	Contained()->~RocketShot();
	return(1);
}

// Soundeffekte
public func OnReload()
{
  Sound("MiniLoad");
}

public func OnAutoStart()
{
  if(GetFireMode()==2) return(1);
  Sound("MiniGun",0,0,0,0,1);
  Sound("MiniTurn",0,0,0,0,1);
}

public func OnAutoStop()
{
  Sound("MiniGun",0,0,0,0,-1);
  Sound("MiniTurn",0,0,0,0,-1);
}
