/*-- Hazardclonk --*/

#strict
#appendto HZCK

/*func Initialize(a,b,c,d,e,f,g)
{
	//DoAmmo (CXIV,1,this());
	return(_inherited(a,b,c,d,e,f,g));
}*/


ControlUp:
  if(Control2Airbike("ControlUp")) return(1);
  return(_inherited());

func ControlUpDouble(a,b,c,d,e)
{
  if(Control2Airbike("ControlUp")) return(1);
  return(_inherited(a,b,c,d,e));
}

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
  if(GetAction() eq "Scale" || GetAction() eq "Hangle") return(0);
  if(Control2Airbike("ControlThrow")) return(1);
  if(GetAction() eq "RideStill" && Contents())
  {
	if((Contents()->~IsWeapon())==false) return(SetAction("RideThrow"));
	else return(Control2Contents("ControlThrow"));
  }
  return(_inherited());
}

ControlThrowDouble:
  if(Control2Airbike("ControlThrow")) return(1);
  return(_inherited());

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

public func AirbikeLoads(pAirbike){return(Local(101)=1);}

func ReadyToFire()
{
	if(GetAction()eq"RideStill")
	{
		Local(101)=1;
		return(1);
	}
	return(_inherited());
}

func Airbike(){
	if(Local(5) && GetAction() eq "Walk" || GetAction() eq "WalkArmed") return(1);//muss stehen
	return(0);
}

func CheckStuck()
{
	if(Local(5) && LocalN("pRider",Local(5))==this()) Local(5)->~ ClonkLost();
	return(_inherited());
}