/*--Airbike--*/

//Local(1) - Pilot
//Local(2) - Modus

//Local(6) - Anzahl MG-Kugeln
//Local(7) - Anzahl Raketen
//Local(8) - Anzahl Bomben

local haken;

#strict
#include AB5B//Grundfunktionen des Airbikes
  
public func FMData1(int data)
{
  if(data == FM_Condition) return(0);
  return(Default(data));
}
public func FMData2(int data)
{
  if(data == FM_Condition) return(0);
  return(Default(data));
}
public func FMData4(int data)
{
  if(data == FM_Condition) return(0);
  return(Default(data));
}
public func FMData6(int data)
{
  if(data == FM_Condition) return(0);
  return(Default(data));
}
public func FMData2(int data) 
{
  if(data == FM_Name)      return("Koppeln");
  if(data == FM_AmmoID)    return(CXIV);
  if(data == FM_AmmoLoad)  return(0);

  if(data == FM_Reload)    return(5);
  if(data == FM_Recharge)  return(0);

  if(data == FM_AmmoUsage) return(0);
  if(data == FM_AmmoRate)  return(1);
  if(data == FM_Auto)      return(0);

  if(data == FM_Condition) return(1);

  if(data == FM_Damage)    return(1);
  if(data == FM_Icon) 	   return(STMS); 

  return(Default(data));
}

func Initialize(a,b,c,d,e,f,g,h)
{
  haken= CreateObject(HAKN);
  LocalN("bike",haken)= this();
  return(_inherited(a,b,c,d,e,f,g,h));
}

public func Fire2()
{
  Sound("Grab");
  haken->~Koppel();
}