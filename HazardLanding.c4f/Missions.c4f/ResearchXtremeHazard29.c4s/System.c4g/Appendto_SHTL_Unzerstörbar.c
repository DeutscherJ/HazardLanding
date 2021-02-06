/*-- Das Shuttle ist unzerstörbar, damit man die Datenwürfel auch ganz sicher abgegeben kann. Und wer außer Lames sollte das Raumschiff schon zerstören? Miffel bestimmt nicht. --*/

#strict
#appendto SHTL

public func Damage() {
	if(GetDamage() < MaxDamage()) return;
	txspeed = 0;
	tyspeed = 0;
	SetAction("Landed");
	return;
}

func IsFlying()
{
	if(GetDamage() >= MaxDamage()) return(0);
	return(_inherited());
}
func IsTurning()
{
	if(GetDamage() >= MaxDamage()) return(0);
	return(_inherited());
}


protected func ContainedUpDouble(pClonk)
{
    [$TxtUp$|Image=SAN1:2]
	if(GetDamage() >= MaxDamage()) return(0);
	return(_inherited(pClonk));
}

func IsBulletTarget(){return(0);}