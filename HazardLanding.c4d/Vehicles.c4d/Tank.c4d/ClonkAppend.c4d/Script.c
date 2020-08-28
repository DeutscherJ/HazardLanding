/*-- Der SFT Clonk --*/
#strict
//#appendto HZCK

public func ControlSpecial(a,b,c,d){
	//Fahrzeuge mit UseSpecial() werden bedient (zb. der panzer)
	if(Contained())
		if(GetID(Contained())->~UseSpecial())
			if (Contained() ->~ ContainedSpecial(a,b,c,d)) return(1);
	return(_inherited(a,b,c,d));
}
public func ControlSpecial2(a,b,c,d){
	//Fahrzeuge mit UseSpecial() werden bedient (zb. der panzer)
	if(Contained())
		if (GetID(Contained()) ->~ UseSpecial2())
			if (Contained() ->~ ContainedSpecial2(a,b,c,d)) return(1);
	return(_inherited(a,b,c,d));
}

protected func ControlUpDouble(a,b,c,d)
{
  //Fahrzeuge auf denen man reiter (zb. panzer mg) werden bedient
  if (IsRiding())
	if (GetActionTarget() ->~ UseRideUpDouble())
		GetActionTarget() -> ControlUpDouble(); 
  return(_inherited(a,b,c,d));
}


//ab hier das hier in den Hazard einfügen :O

protected func ControlThrow(a,b,c,d)
{
  //Fahrzeuge auf denen man reiter (zb. panzer mg) werden bedient  
  if (IsRiding())
	if (GetActionTarget() ->~ UseRideThrow())
	  return(GetActionTarget() -> ControlThrow(a,b,c,d));
  return(_inherited(a,b,c,d));
}

public func IsRiding()
{
  // Reitet der Clonk?
  return (WildcardMatch(GetAction(), "Ride*"));
}
