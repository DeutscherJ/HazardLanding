/*-- Neues Script --*/

#strict
#appendto FLAK
#appendto PRCA

public func ControlThrow(object clonk)
{
	[$TxtFire$|Image=TAN3:0]
	if(GetUser() != clonk) return false;
	if(ObjectCount2(Find_ID(_SWT),Find_Action("Off")))
	{
		Sound("Error");
		return(Message(Format("%s Deaktiviert",GetName()),this()));
	}
	return _inherited(clonk,...);
}

public func Damage() {
	if(GetDamage() < MaxDamage()) return;

	// boom
	SetCon(2);
	Sound("Blast2");
	DoDamage(-GetDamage());
}

func Initialize()
{
	DoDamage(-GetDamage());
	return(_inherited());
}