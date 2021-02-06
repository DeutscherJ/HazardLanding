/*-- Hazard --*/

#strict
#appendto HZCK
#appendto CLNK

func Initialize(a,b,c,d,e,f,g)
{
	DaytimeControlled();
	return(_inherited(a,b,c,d,e,f,g));
}

func DaytimeControlled(iTime)
{
	SetPlrViewRange(200+iTime*2);
	return(1);
}
