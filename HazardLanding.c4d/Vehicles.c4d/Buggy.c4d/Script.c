/*-- MG Wagen --*/

#strict
#include L_TK
//#include WEPN

func IsVehicleProduct(){return(1);}
local pShooter;

func Initialize() {
	SetAction("Aim");
	SetPhase(2);
	pShooter=CreateObject(PSHT,0,0,GetOwner());
	pShooter->Set(this());
	
	// Damage effect
	AddDamageEffect(this);
	return(_inherited());
}


// X- and Y-Offset to wheels (which are 2) from the center: assumes that the distance
// to the wheels are the same from the center.
public func XOffsToWheels() { return(30); }
public func YOffsToWheels() { return(20); }

public func MaxSpeed()		{ return(2500); }	// maximum speed
public func BrakeStrengh()	{ return(200); }	// speed of braking
public func Acceleration()	{ return(200); }	// speed of speeding up

public func TurnAction()	{ return(); }	// name of turning-action. Leave out if there is none.

//public func CatLanding()	{ return(5); }

public func SpiderMode()	{ return(true);}	//experimental drive-on-walls and ceiling
public func MaxRotation()	{ return(70); }		// max. rotation of landscape it can stand (0 for no max rotation)

/* Callbacks */
/* ------------------------------------------------------------------------- */

public func OnGo() {}
public func OnStop() {}
public func OnJumpStart() {}
public func OnJumpEnd() {}


/*-- Eingang --*/
func ActivateEntrance(pClonk)
{
	if(FindObject(0,0,0,0,0,OCF_Alive,0,0,this()) && !Contained(pClonk)) return(1);//nur eine Person drinnen :-(
	SetEntrance(1);
	SetOwner(GetOwner(pClonk));
	return(Schedule("SetEntrance(0)",2,1));
}

func Collection2(pClonk)
{
	if(!GetAlive(pClonk)) return(0);//Gegenstand?
	if(ObjectCount2(Find_OCF(OCF_CrewMember), Find_Container(this()) )>1) return(SetCommand(pClonk,"Exit"));//nur eine Person drinnen !
}

/*-- Steuerung --*/

func GetAimAngle(){return((GetPhase()*10-10-90)*-(GetDir()*2-1)+GetR());}

func ContainedUp(pClonk)
{
	SetPhase(GetPhase()+1);
	return(1);
}

func ContainedDig(pClonk)
{
	SetPhase(GetPhase()-1);
	return(1);
}

public func ContainedLeft(object driver) {	// Left
    [$TxtLeft$|Image=TAN1:3]
	if(EMPShocked()) return(true);
	if(GetDir() != DIR_Left) {
		if(!IsTurning()) {
			if(BottomContact())
				Turn();
		}
	}
	else {
		if(!IsDriving())
				Go();
	}
	return(true);
}

public func ContainedRight(object driver) {	// Right
    [$TxtRight$|Image=TAN1:4]
	if(EMPShocked()) return(true);
	if(GetDir() != DIR_Right) {
		if(!IsTurning())
			if(BottomContact())
				Turn();
	}
	else {
		if(!IsDriving())
				Go();
	}
	return(true);
}


public func ContainedDown(object driver) {	// Down
    [$TxtAimDown$|Image=TAN1:2]
	if(IsDriving()) {
		Stop();
		return(1);
	}
	if(GetPlrDownDouble(GetOwner(driver)))
	{
		Exit(driver,0,20);
	}
	//PauseTurn();
	return(1);
}

public func ContainedThrow(object driver) {	// Throw (Fire)
    [$TxtFire$|Image=TAN1:0]
	// forward to turret: select the fire mode
	pShooter->~ControlThrow(driver);
	return(true);
}

public func ContainedDigDouble(object driver) {	// Dig Double (fire mode)
    [$TxtFireMode$|Image=TAN1:5]
	// forward to turret: select the fire mode
	pShooter->~ControlDigDouble(driver);
	return(true);
}

func Turn()
{
	SetDir(!GetDir());
}

func Smoking()
{
	if(!Contents()) return(1);
	var dir= GetDir()*2-1;
	if(!Random(6))CreateParticle("Smoke",Cos(GetR(),25)*-dir,Cos(GetR(),20),0,0,speed/60+35);
	return(1);
}

/*HUD*/
public func ReadyToFire(){return(1);}

public func UpdateCharge(object driver) {

	var hud = driver->GetHUD();
	if(hud) {
		hud->Update(pShooter, driver->AmmoStoring(),driver);
	}
	return(1);
}

/*Sound*/
protected func Ejection(object by) {
	Sound("tank_stop",0,0,SLvl(0));
	Sound("tank",0,0,SLvl(0),0,-1);
	Sound("tank2",0,0,SLvl(1),0,-1);
	//DoScore(GetOwner(by),-GetValue());
	//SetController(-1);
}

private func DriverIsOwner(object driver) {
	DoScore(GetOwner(),+GetValue());
	SetOwner(GetOwner(driver));
	DoScore(GetOwner(driver),-GetValue());
}

protected func Collection2(object by)
{
	// change owner of the vehicle 
	DriverIsOwner(by);
	Sound("tank_start",0,0,SLvl(0));
	Sound("tank",0,0,SLvl(0),0,1);
}

private func SLvl(bool drive) {
	if(!drive) return(50);
	if(drive) return(100);
} 

/* Damage */
/* ------------------------------------------------------------------------- */

public func OnDmg(int iDmg, int iType) {
	// full resistance to bio damage
	// vulnerable to explosions and energy
	// and a bit resistant vs everything else
	
	if(iType == DMG_Energy)		return(10);
	if(iType == DMG_Bio)		return(100);
	if(iType == DMG_Melee)		return(20);
	if(iType == DMG_Fire)		return(60);
	if(iType == DMG_Explosion)	return(0);
	
	return(50);
}

public func IsBulletTarget(){return(1);}


public func Damage() {							// Damage
	if(GetDamage() < MaxDamage()) return();

	Destroyed();
}

public func Destroyed() {
	// exit all drivers
	var bla;
	while(bla = Contents()) bla->Exit();
	Explode(40);
}

func MaxDamage(){return(250);}