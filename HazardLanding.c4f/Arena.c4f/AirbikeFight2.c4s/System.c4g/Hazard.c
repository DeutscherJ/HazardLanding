/*-- Hazardclonk --*/

#strict
#appendto HZCK

func Initialize()
{
    if(iReady) AddEffect("SpawnProtect", this(), 1,1, this());
	return(inherited());
}

func LaterInit()
{
	AddEffect("SpawnProtect", this(), 1,1, this());
	return(1);
}

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
	  if((Contents()->~IsWeapon())==false) return(SetAction("RideThrow"));
	  if(Contents()->~IsWeapon()) return(Control2Contents("ControlThrow"));
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

//Local(5) Airbike
//Local(6) offiziell Tot?

func Death(a,b,c)
{
  DeathA();
  return(_inherited(a,b,c));
}

func DeathA()
{
  if(!Local(5)) return(0);//Airbike?
  if(!GetAlive(LocalN("pRider",Local(5))) ) Schedule("Explode(5,Local(5))",36);
  //if(!GetAlive(LocalN("pRider",Local(5))) ) Explode(5,Local(5));//hat Airbike neuen Besitzer gefunden?
}
  
/*Fallschaden*/

func ContactBottom()
{
  if(FallDamage()) Aufschlag();
  return(_inherited());
}

func Aufschlag()
{
  if(!GetAlive()) return(0);//Lebt?
  var speed= Max(Abs(GetXDir()),Abs(GetYDir()));
  if(speed<70) return(0);
  DoEnergy(2*(70-speed));
  return(Sound("Hurt*"));
}

/*Waffe rausholen*/
//Local(1337) ist die waffe, bzw, on der Clon die Waffe schong ezogen hat (BOOl)
func ControlSpecial2()
{
  if(Control2Airbike("ControlSpecial2")) return(1);
  return(_inherited());
}

/*Spawnschutz*/
func FxSpawnProtectStart(object target, int effect, int temp)
{
    EffectVar(0, target, effect) =  SPSeconds*36;
}

func FxSpawnProtectTimer(object target, int effect, int temp)
{
	var iAngle=Random(360);
	var x= Sin(iAngle,15);
	var y= -Cos(iAngle,15);
	//CreateParticle("PSpark",Sin(EffectVar(0, target, effect),10),-Cos(EffectVar(0, target, effect),10),0,0,50,RGB(Random(255),Random(255),Random(255)),this());
	CreateParticle("PSpark",x,y,0,0,50,RGB(Random(255),Random(255),Random(255)),this());
    EffectVar(0, target, effect)--;
	if(!EffectVar(0, target, effect)) return(-1);
}

func FxSpawnProtectStop(object target, int effect, int temp)
{
	return(1);
}

//Die Waffenfunktion vom Airbike wird benuzt, und der Spawnschutz mit Sicherheit abgebrochen

public func AirbikeLoads(pAirbike){return(AbortSpawnProtect());}

func ContextCallAirbike()
{
  [$Call$|Image=AB5B|Condition=Airbike]
  if(!GetCommand(Local(5))) SetCommand(Local(5),"Follow",this());//Airbike soll her-erscheinen
  else SetCommand(Local(5),"None",this());//Airbike soll her-erscheinen
  return(1);
}

func Damage(iChange)
{
	if(InSpawnProtect()) DoEnergy(iChange);//Spawnschutz... Abgezogenen Energie wieder raufrechnen
	return(_inherited(iChange));
}

func ReadyToFire()
{
	//Kann auch beim "reiten" schießen
	if(GetAction()eq"RideStill")
	{
		AbortSpawnProtect();
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

public func IsBulletTarget()
{
	if(InSpawnProtect()) return(0);
	return(1);
}
public func CheckEnemy(pObj)
{
	if(InSpawnProtect()) return(0);
	return(_inherited(pObj));
}

func InSpawnProtect(){return(GetEffect("SpawnProtect",this()));}
func AbortSpawnProtect()
{
	if(InSpawnProtect())
	{
		RemoveEffect(0, this(),InSpawnProtect());
	}
	return(1);
}