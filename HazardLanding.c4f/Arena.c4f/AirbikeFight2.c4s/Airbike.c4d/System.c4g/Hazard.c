/*-- Hazardclonk --*/

#strict
#appendto HZCK

ControlUp:
  if(Control2Airbike("ControlUp")) return(1);
  return(_inherited());

ControlUpDouble:
  return(ControlUp());

ControlDown:
  if(Control2Airbike("ControlDown")) return(1);
  return(_inherited());

ControlDownDouble:
  if(Control2Airbike("ControlDown")) return(1);
  return(_inherited());

ControlDownSingle:
  return(_inherited());

ControlLeft:
  if(Control2Airbike("ControlLeft")) return(1);
  return(_inherited());

ControlLeftDouble:
  if(Control2Airbike("ControlLeftDouble")) return(1);
  return(_inherited());

ControlRight:
  if(Control2Airbike("ControlRight")) return(1);
  return(_inherited());

ControlRightDouble:
  if(Control2Airbike("ControlRightDouble")) return(1);
  return(_inherited());

func ControlThrow()
{
  if(GetPlrDownDouble(GetOwner())) return(_inherited()); 
  if(Control2Airbike("ControlThrow")) return(1);
  if(GetAction() eq "RideStill" && Contents())
  {
	  if((Contents()->~IsWeapon())==false) return(SetAction("RideThrow"));
	  if(Contents()->~IsWeapon()) return(Control2Contents("ControlThrow"));
  }
  return(_inherited());
}

ControlThrowDouble:
  return(ControlThrow());

/* Steuerung Richtung (an Inhalt weitergeben, sonst internen Befehl ausführen) */

protected func ControlUpdate(object clonk, int comdir, bool dig, bool throw)
{
  if(Control2Airbike("ControlUpdate",comdir,dig,throw)) return(1);
  if(IsAiming()) {
    AimUpdate(this(), comdir, 1, "ControlConf");
    return(1);
  }
  if(Control2Contents("ControlUpdate", comdir, dig, throw)) return(1);
  if(ControlLadder("ControlUpdate", comdir, dig, throw)) return(1);
  return(_inherited());
}

protected func ControlDigDouble()
{
  if (Control2Airbike("ControlDigDouble")) return(1);
  return(_inherited());
}

func Control2Airbike(string szCall, int comdir, bool dig, bool throw)
{
  if(GetAction() ne "RideStill") return(0);
  if(szCall eq "ControlUpdate") return(ObjectCall(GetActionTarget(),"ControlUpdate",this(),comdir,dig,throw));
  if(szCall eq "ControlThrow" && LocalN("firemode",GetActionTarget())==5) return(0);
  return(ObjectCall(GetActionTarget(),szCall,this()));
}