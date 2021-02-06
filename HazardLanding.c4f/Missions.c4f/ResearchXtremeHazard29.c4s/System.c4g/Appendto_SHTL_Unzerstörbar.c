/*-- Das Shuttle ist unzerst�rbar, damit man die Datenw�rfel auch ganz sicher abgegeben kann. Und wer au�er Lames sollte das Raumschiff schon zerst�ren? Miffel bestimmt nicht. --*/

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