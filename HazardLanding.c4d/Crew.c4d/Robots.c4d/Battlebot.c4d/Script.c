/*-- Roboter --*/

#strict
#include L_CA

local fActive, iPhase, fAim, ammobag, iFireChange, pWeapon;

func IsBulletTarget(pObjID,pObj){return(GetOwner(pObj)!=GetOwner());}

func Initialize()
{
  SetAction("Walk");
  pWeapon=CreateContents(BTWP);
  SetDir(Random(2));
  AmmoStoring();
  SetVertexXY(1,0,-5);
  DoAmmo(STAM,10000,this());
  DoAmmo(MIAM,500,this());
  //SetCon(80);
  return(1);
}

protected func Death(int iKilledBy)
{
  RemoveObject(pWeapon);
  var plr = GetOwner();

// HIER GEHÖRT KEIN INHERITED HIN
// das macht die ganze aufrufkette kaputt!
//  _inherited();

  // Info-Broadcasts für sterbende Clonks
  GameCallEx("OnClonkDeath", this(), iKilledBy);
  
  if(GetPlayerType(GetOwner()) == C4PT_Script)
    GameCallEx("RelaunchPlayer",GetOwner(),this(), GetKiller());
  else
  {
    var gotcrew;
    for(var i; i < GetCrewCount(plr); i++)
      if(GetOCF(GetCrew(plr,i)) & OCF_Alive)
        gotcrew = true;
  
    if(!gotcrew)
      GameCallEx("RelaunchPlayer",GetOwner(),this(), GetKiller());
  }
	
  Explode(30);
  return(1);
}

func ContextAusfahren()
{
	[Ausfahren|Image=BLBT|Condition=Deactive]
	if(GetAction()ne"Ausklapp")SetAction("Ausklapp");
	SetPhysical("Walk", 50000, PHYS_Temporary);
	SetPhysical("Jump", 60000, PHYS_Temporary);
	return(1);
}
func ContextEinfahren()
{
	[Einfahren|Image=BLBT|Condition=Active]
	StopAiming();
	if(GetAction()ne"Einklapp")SetAction("Einklapp");
	SetPhysical("Walk", 100000, PHYS_Temporary);
	SetPhysical("Jump", 30000, PHYS_Temporary);
	return(1);
}
func ContextAim()
{
	[Zielen|Image=BLBT|Condition=Active]
	if(!fAim)
	{
		var fFly= OnFly();
		fAim=true;
		StartAiming();
		if(fFly) StartFly();
	}
	else StopAiming();
	return(1);
}
func Active(){return(!Deactive());}
func Deactive(){return(GetAction()ne"Aim" && GetAction()ne"AimJump" && GetAction()ne"AimFly");}

public func AmmoStoring()
{
  // keiner da: neuen erstellen
  if(!ammobag) {
    ammobag = CreateObject(ABAG);
    //ammobag->Init(this());
  }
  return(ammobag);
}

func Activated()
{
	SetPhase(9);
	iPhase=9;
	SetVertexXY(1,0,-17);
	fActive=true;
	return(1);
}

func Deactivated()
{
	iPhase=0;
	SetVertexXY(1,0,-5);
	fActive=false;
	return(1);
}

func ActionControl()
{
	if(fActive)
	{
		SetAction("Aim");
		SetPhase(iPhase);
		return(1);
	}
	if(iPhase<15)SetPhase(iPhase);
	return(1);
}

func Timer()
{
	UpdateCharge();
	if(!fActive)
	{
		iPhase=GetPhase();
	}
	if(GetAction()eq"AimJump")
	{
		if(GetYDir()<-10) CreateParticle("JetSpark",0, 20, GetXDir(), GetYDir(), 130, RGBa(155,255,205,100), this);
		if(GetYDir()>40)
		{
			CreateParticle("JetSpark",0, 20, GetXDir(), GetYDir(), 130, RGBa(155,255,205,100), this);
			SetSpeed(GetXDir(),40);
		}
	}
	if(OnFly())
	{
		//if(!Random(3))MuzzleFlash(100,this(),-2,18,Angle(0,0,GetXDir()*5,GetYDir()*5),RGB(100,100,255));
		CreateParticle("JetSpark",0, 20, GetXDir(), GetYDir(), 130, RGBa(155,255,205,100), this);
	}
	return(1);
}

public func UpdateCharge()
{
  // Nur wenn ich Cursor bin
  if(GetCursor(GetOwner()) != this()) return();

  if(GetOwner() < -1) return();

  // in Gebäuden/Fahrzeugen
  if(Contained())
    if(Contained()->~UpdateCharge(this()))
      return(1);

  // ggf. an angefasstes Objekt weiterleiten
  var Content = Contents();
  if(GetAction() S= "Push")
  	if(GetActionTarget()->~IsWeapon())
  		Content = GetActionTarget();

  // HUD
  var hud = GetHUD();
  if(hud) hud->Update(Content, AmmoStoring(),this());

  return(1);
}

func JumpStart()
{
	if(fActive)
	{
		SetAction("AimJump");
		SetPhase(iPhase);
	}
	else SetPhase(iPhase);
	return(1);
}

protected func CheckStuck()
{                   
  // Verhindert Festhängen am Mittelvertex
  if(!GetXDir()) if(Abs(GetYDir()) < 5)
    if(GBackSolid(0, 3))
      SetPosition(GetX(), GetY() + 1);
}

/*Steuerung*/
protected func ControlSpecial2()
{
  [$CtrlMenuDesc$|Image=CXTX]
  // In einem Gebäude oder Fahrzeug: das Kontextmenü des Gebäudes öffnen
  if (Contained())
    if ((Contained()->GetCategory() & C4D_Structure) || (Contained()->GetCategory() & C4D_Vehicle))
      return(SetCommand(this(),"Context",0,0,0,Contained()), ExecuteCommand());
  // Fasst ein Objekt an: Kontextmenü des angefassten Objekts öffnen
  if (GetAction() eq "Push")
    return(SetCommand(this(),"Context",0,0,0,GetActionTarget()), ExecuteCommand());
  // Trägt ein Objekt: Kontextmenü des ersten getragenen Objekts öffnen
  if (Contents(0))
    return(SetCommand(this(),"Context",0,0,0,Contents(0)), ExecuteCommand());
  // Ansonsten das Kontextmenü des Clonks öffnen
  return(SetCommand(this(),"Context",0,0,0,this()), ExecuteCommand());
}

protected func ControlSpecial()
  {
  [$CtrlInventoryDesc$|Image=INVT]
  if(!Contents()) return();
  // Hardcode: BR-Bombe darf man nicht abwählen
  if(Contents()->GetID() == GBRB)
    return();
  // wenn wir zielen, wollen wir nur Waffen haben
  if(IsAiming() && Contents(0)->~IsWeapon())
  {
  	// nächste Waffe suchen
  	for(var i = 1; i < ContentsCount(); i++)
  		if(Contents(i)->~IsWeapon())
  		{
  			// zur Waffe wechseln
  			ShiftContents(0,0,Contents(i)->GetID(),true);
  			break;
  		}
  }
  else
	  // Inventory verschieben
  	ShiftContents(0,0,0,1);
  UpdateCharge();
  }
  
func ControlThrow()
{
	if(Deactive()) return(1);
	if (Control2Contents("ControlThrow") ) return(1);
	return(1);
}

func SpezShot()
{
	var angle=AimAngle(10);
	var dir= GetDir()*2-1;
	
	if(!iFireChange)
	{
		MuzzleFlash(70,this(),18*dir,-Cos(angle,7)+2,angle);
		CreateObject(SHT1,18*dir,-Cos(angle,7)+2,GetOwner())->Launch(angle+RandomX(-3,3),300,600,6,100,4);
	}
	else
	{
		MuzzleFlash(70,this(),-15*dir,-Cos(angle,7)+2,angle);
		CreateObject(SHT1,-15*dir,-Cos(angle,7)+2,GetOwner())->Launch(angle+RandomX(-3,3),300,600,6,100,4);
	}
	iFireChange=!iFireChange;
	return(1);
}

func RocketShot()
{
	var angle=AimAngle(10);
	var dir= GetDir()*2-1;
	
	if(!iFireChange)
	{
		MuzzleFlash(70,this(),18*dir,-Cos(angle,7)+2,angle);
		var rocket1= CreateObject(MISS,18*dir,-Cos(angle,7)+2,GetOwner());
		rocket1->Launch(angle, 10);
		rocket1->Sound("Bazooka");
		iFireChange=true;
		return(1);
	}
	if(iFireChange)
	{
		MuzzleFlash(70,this(),-15*dir,-Cos(angle,7)+2,angle);
		var rocket1= CreateObject(MISS,-15*dir,-Cos(angle,7)+2,GetOwner());
		rocket1->Launch(angle, 10);
		rocket1->Sound("Bazooka");
		iFireChange=false;
		return(1);
	}
	return(1);
}

func ControlDigDouble()
{
	if (Control2Contents("ControlDigDouble") ) return(1);
	return(0);
}

func ControlDown()
{
	if(crosshair) if (ControlAim("ControlDown")) return(0);
	if (OnFly())
	{
		SetComDir(COMD_Down);
		return(1);
	}
	else return(_inherited());
}

func ControlUp()
{
	if (ControlAim("ControlUp")) return(1);
	if (GetAction()eq"AimJump") StartFly();
	if (OnFly())
	{
		SetComDir(COMD_Up);
		return(1);
	}
	if(!fAim&&(GetAction()eq"Aim"||GetAction()eq"Walk")) return(Jump());
	else return(_inherited());
}

func ControlUpDouble()
{
	if(Deactive()) ContextAusfahren();
	else return(_inherited());
}

func ControlLeft()
{
	if (ControlAim("ControlLeft"))
	{
		if(GetDir()==DIR_Right) return(1);
		return(0);
	}
	if (OnFly())
	{
		if(GetComDir()==COMD_Right) return(SetComDir(COMD_Stop));
		SetDir(DIR_Left);
		SetComDir(COMD_Left);
		return(1);
	}
	else return(_inherited());
}

func ControlRight()
{
	if (ControlAim("ControlRight"))
	{
		if(GetDir()==DIR_Left) return(1);
		return(0);
	}
	if (OnFly())
	{
		if(GetComDir()==COMD_Left) return(SetComDir(COMD_Stop));
		SetDir(DIR_Right);
		SetComDir(COMD_Right);
		return(1);
	}
	else return(_inherited());
}

func ControlRightDouble()
{
	if (ControlAim("ControlRightDouble")) return(1);
	else return(_inherited());
}

func ControlLeftDouble()
{
	if (ControlAim("ControlLeftDouble")) return(1);
	else return(_inherited());
}

func AbortAim()
{
	StopAiming();
	return(1);
}

func StopAiming()
{
	fAim=false;
	return(_inherited());
}
func ControlDownDouble()
{
	if(OnFly()&&!IsAiming()){return(StopFly());}
	if((GetAction()eq"Aim" || GetAction()eq"AimJump") && !fAim)
	{
		StartAiming();
		fAim=true;
	}
	else return(_inherited());
}

func IsAiming(){return(fAim);}
func CheckArmed()
{
	SetAction("Aim");
	return(1);
}
func ReadyToAim(){return(GetAction()eq"Aim"||GetAction()eq"AimJump"||OnFly());}
global func aids(){return(MakeCrewMember(CreateObject(BLBT)));}

private func Control2Contents (string command)
{
  // Haben wir was angefasst?
  if(GetAction() S= "Push")
    return(0);
  // Pause Reload: nicht wieder anfangen ey!!!
  if(command S= "ControlThrow") {
	if(WildcardMatch(GetAction(),"Scale*") || GetAction() S= "Hangle")
	  return(1);
  }
	
  // Getragenes Objekt hat spezielle Steuerungsauswertung
  if(ObjectCall(Contents(), command, this(), Par(1), Par(2), Par(3), Par(4), Par(5), Par(6), Par(7)))
    return(1);
  return(0);
}

func StartFly()
{
	SetAction("AimFly");
	return(1);
}
func StopFly()
{
	SetAction("AimJump");
	return(1);
}
func OnFly(){return(GetAction()eq"AimFly");}

func IsRobot(){return(1);}
/*func Timer()
{
	if(fActive)
	{
		SetSpeed(GetXDir(),-5);
	}
	return(0);
}*/

//MakeCrewMember(CreateObject(BLBT))