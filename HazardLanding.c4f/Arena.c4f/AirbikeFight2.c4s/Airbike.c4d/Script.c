/*--  Airbike v2  --*/

//pRider - Pilot
//Local(2) - Modus

local pRider, fUpgraded;

//Local(6) - Anzahl MG-Kugeln
//Local(7) - Anzahl Raketen
//Local(8) - Anzahl Bomben

#strict
#include WEPN

public func IsStill(){return(1);}
public func IsAirbike(){return(1);}
func IsUpgradeable(id uid)
{
	if(uid==KLAS && !fUpgraded)return("Laser Upgrade");
	return(0);
}

public func OnUpgrade(id uid)
{
	SetGraphics("Laser");
	Message("Laser Upgrade",this());
	fUpgraded=true;
	return(1);
}

func Initialize(){
  SetAction("Fliegen");
  SetComDir(COMD_Down());
  return(_inherited());
}

func Hit()
{
  if(GetXDir()+GetYDir()<70) return(0);
  pRider-> SetAction("Tumble");
  ObjectCall(pRider,"Inventar");
  for(var y=-20;Stuck(pRider);y++)SetPosition(GetX(pRider),GetY(pRider)+y,pRider);
  return(Explode(50));
}

func Damage(){
  if(GetDamage()<60) return(0);
  ObjectCall(pRider,"Inventar");
  for(var y=-20;Stuck(pRider);y++)SetPosition(GetX(pRider),GetY(pRider)+y,pRider);
  return(Explode(50));
}
  
func ActivateEntrance(pClonk)
{
  if(FindObject(0,0,0,0,0,0,"RideStill",this()))  return(0);
  if(!ObjectSetAction(pClonk,"RideStill",this())) return(ZuDoof(pClonk));
  
  if(pClonk!=pRider) ObjectCall(pRider,"Departure");
  
  pRider=pClonk;  
  SetPhysical("Float",200,2);
  
  Local(5,pClonk)=this();
  
  SetCommand(this(),"None");
  
  SetOwner(GetOwner(pClonk));//damit die Schüsse auch den richtigen Erschaffer bekommen

  return(1);
}

func RiderUnRides()
{
	return(GetAction(pRider)ne"RideStill" && GetAction(pRider)ne"RideThrow");
}

func ControlUp(pClonk)
{
  if(RiderUnRides()) return(0);
  return(SetComDir(COMD_Up()));
}

func ControlDown(pClonk)
{
  if(RiderUnRides()) return(0); 
  if(Stuck()||(GBackSolid(0,8) && GetXDir()<2))    return(Absteigen(pClonk));
  return(SetComDir(COMD_Down()));
}

func ControlDownDouble(pClonk)
{
	if(RiderUnRides())		return(0); 
	if(Stuck()||(GBackSolid(0,8) && GetXDir()<20)) return(Absteigen(pClonk));
	return(1);
}

func ControlLeft(pClonk)
{
  if(RiderUnRides()) return(Fehler(pClonk));
  if(GetPlrCoreJumpAndRunControl(pClonk->GetController())) return(JnRLeft());
	  
  if(GetAction()ne"Fliegen") SetAction("Fliegen");
  SetDir(DIR_Left);
  SetDir(DIR_Left,pClonk);
  return(SetComDir(COMD_Left()));
}

func ControlLeftDouble(pClonk)
{
  if(RiderUnRides()) return(Fehler(pClonk));
  if(GetDir()!=DIR_Left())        return(0);
  if(InLiquid())                  return(0);
  if(GetPlrCoreJumpAndRunControl(pClonk->GetController())) return(JnRLeftDouble());
  
  SetPhysical("Float",800,2);
  return(SetAction("Hyperfly"));
}

func ControlRight(pClonk)
{
  if(RiderUnRides()) return(Fehler(pClonk));
  if(GetPlrCoreJumpAndRunControl(pClonk->GetController())) return(JnRRight());
  
  if(GetAction()ne"Fliegen") SetAction("Fliegen");
  SetDir(DIR_Right);
  SetDir(DIR_Right,pClonk);
  
  return(SetComDir(COMD_Right()));
}

func ControlRightDouble(pClonk)
{
  if(RiderUnRides()) return(Fehler(pClonk));
  if(GetDir()!=DIR_Right())       return(0);
  if(InLiquid())                  return(0);  
  if(GetPlrCoreJumpAndRunControl(pClonk->GetController())) return(JnRRightDouble());

  SetPhysical("Float",800,2);
  return(SetAction("Hyperfly"));
}

func ZuDoof(pClonk)
{
  if(GetOCF(pClonk) & OCF_CrewMember())
    Message("$NotAble$",pClonk,GetName(pClonk));
  return(Sound("Error"));
}

func Fehler(pClonk)
{
  Message("$First$",pClonk);
  return(Sound("Error"));
}

func Absteigen(pClonk)
{
  pClonk->~Departure(this());
  ObjectSetAction(pRider,"Walk");
  SetSpeed(0,0);
  SetPhysical("Float",100,2);
  return(1);
}

func Fliegen(){return(SetPhysical("Float",200,2));}

func Hyperfly()
{
  var angle =90;
  if(GetDir()== DIR_Right()) angle=-90;
  // Schuss an der Mündung der Waffe erstellen...
  var x=Sin(angle,15),y;
  // Effekte
  MuzzleFlash(RandomX(20,50),this(),x,y,angle,0,1);
  
  if(GetDir()==DIR_Left())  SetVar(0,19);
  if(GetDir()==DIR_Right()) SetVar(0,-19);
  if(!Random(3)) Smoke(Var(0),4,5);
  return(1);
}

func ClonkLost()
{
	pRider=0;
	return(1);
}

func Wasser(){return(SetPhysical("Float",100,2));}

func Test()
{
  if(pRider)
   if(GetAction(pRider)eq"RideStill")
    if(GetActionTarget(0,pRider)==this())
     if(GetPlrCoreJumpAndRunControl(pRider->GetController())) JnRTimer();
	  
  SetVertexXY(0,2*((GetDir()*2)-1),-4);//Vertex-setzung
  
  if(GetCommand())//Folgt Clonk
  {
	//if(GetCommand()eq"Follow" && ObjGetCommand(this(),1))
	if(GetXDir()<0) SetDir(DIR_Left());
	if(GetXDir()>0) SetDir(DIR_Right());
  }

  if(FindObject(0, 0,0,0,0,OCF_CrewMember(),"RideStill",this())) return(0);
  if(GetAction()ne"Fliegen") SetAction("Fliegen");
  return(SetComDir(COMD_Down()));
  /*if(GetAction()eq"Wasser") if(!InLiquid()) SetAction("Fliegen");

  ObjectCall(pRider,"Inventar");*/
}

func Auswahl(){  return(Sound("ABAuswahl"));}

/*Feuermodus und HUD*/

public func FMData1(int data)
{
  if(data == FM_Name)      return("$MG$");
  if(data == FM_AmmoID)    return(STAM);
  if(data == FM_AmmoLoad)  return(100);

  if(data == FM_Reload)    return(140);
  if(data == FM_Recharge)  return(4);

  if(data == FM_AmmoUsage) return(1);
  if(data == FM_AmmoRate)  return(1);
  if(data == FM_Auto)      return(true);

  if(data == FM_Condition) return(1);

  if(data == FM_Damage)    return(14);

  return(Default(data));
}

public func FMData2(int data)
{
  if(data == FM_Name)      return("$Rockets$");
  if(data == FM_AmmoID)    return(MIAM);
  if(data == FM_AmmoLoad)  return(10);

  if(data == FM_Reload)    return(50);
  if(data == FM_Recharge)  return(25);

  if(data == FM_AmmoUsage) return(1);
  if(data == FM_AmmoRate)  return(1);
  if(data == FM_Auto)      return(0);

  if(data == FM_Condition) return(1);

  if(data == FM_Damage)    return(26);

  return(Default(data));
}

public func FMData3(int data)
{
  if(data == FM_Name)      return("$Bombs$");
  if(data == FM_AmmoID)    return(MNI2);
  if(data == FM_AmmoLoad)  return(10);

  if(data == FM_Reload)    return(50);
  if(data == FM_Recharge)  return(5);

  if(data == FM_AmmoUsage) return(1);
  if(data == FM_AmmoRate)  return(1);
  if(data == FM_Auto)      return(0);

  if(data == FM_Condition) return(1);

  if(data == FM_Damage)    return(26);

  return(Default(data));
}

public func FMData4(int data)
{
  if(data == FM_Name)      return("$AB$");
  if(data == FM_AmmoID)    return(MNI1);
  if(data == FM_AmmoLoad)  return(3);

  if(data == FM_Reload)    return(50);
  if(data == FM_Recharge)  return(5);

  if(data == FM_AmmoUsage) return(1);
  if(data == FM_AmmoRate)  return(1);
  if(data == FM_Auto)      return(0);

  if(data == FM_Condition) return(1);

  if(data == FM_Damage)    return(26);

  return(Default(data));
}

public func FMData5(int data)
{
  if(data == FM_Name)      return("$Nothing$");
  if(data == FM_AmmoID)    return(CXIV);
  if(data == FM_AmmoLoad)  return(0);

  if(data == FM_Reload)    return(5);
  if(data == FM_Recharge)  return(0);

  if(data == FM_AmmoUsage) return(0);
  if(data == FM_AmmoRate)  return(1);
  if(data == FM_Auto)      return(0);

  if(data == FM_Condition) return(1);

  if(data == FM_Damage)    return(1);

  return(Default(data));
}

public func FMData6(int data)
{
  if(data == FM_Name)      return("Laser");
  if(data == FM_AmmoID)    return(ENAM);
  if(data == FM_AmmoLoad)  return(50);

  if(data == FM_Reload)    return(120);
  if(data == FM_Recharge)  return(40);

  if(data == FM_AmmoUsage) return(10);
  if(data == FM_AmmoRate)  return(1);
  if(data == FM_Auto)      return(false);

  if(data == FM_Condition) return(fUpgraded);
  
  if(data == FM_Damage)    return(240);

  return(Default(data));
}

public func FMData7(int data)
{
  if(data == FM_Name)      return("Beam");
  if(data == FM_AmmoID)    return(ENAM);
  if(data == FM_AmmoLoad)  return(50);

  if(data == FM_Reload)    return(1);
  if(data == FM_Recharge)  return(40);

  if(data == FM_AmmoUsage) return(5);
  if(data == FM_AmmoRate)  return(1);
  if(data == FM_Auto)      return(false);
  
  if(data == FM_Condition) return(fUpgraded);

  if(data == FM_Damage)    return(0);

  return(Default(data));
}

public func UpdateCharge(object driver) {

	var hud = driver->GetHUD();
	if(hud) {
		hud->Update(this(), driver->AmmoStoring(),driver);
	}
	return(1);
}

public func OnReload(int i)
{
  Local(101,pRider)=1;//beende Spawnschutz
  
  if(i == 1) Sound("ABLaden1");
  if(i == 2) Sound("ABLaden2");
  if(i == 3) Sound("ABLaden2");
  if(i == 4) Sound("ABLaden2");
  if(i == 6) Sound("MoteGunLoad");
}

public func Fire1()    // Projektil-Dauerfeuer
{
  Local(101,pRider)=1;//beende Spawnschutz
  
  var angle =90;
  if(GetDir()== DIR_Right()) angle=-90;
  // Schuss an der Mündung der Waffe erstellen...
  var x=-Sin(angle,15),y;
  var ammo = CreateObject(SHT1,x,y,GetOwner());
  ammo->Launch(-angle+RandomX(-5,5),300,600,4,600,5);

  // Effekte
  MuzzleFlash(RandomX(20,50),this(),x,y,-angle);
  return(0);
}

public func OnAutoStart()
{
  if(firemode==1) Sound("MiniGun",0,0,0,0,1);
  if(firemode==1) Sound("MiniTurn",0,0,0,0,1);
}

public func OnAutoStop()
{
  if(firemode==1) Sound("MiniGun",0,0,0,0,-1);
  if(firemode==1) Sound("MiniTurn",0,0,0,0,-1);
}

public func Fire2()    // Rakete
{ 
  Local(101,pRider)=1;//beende Spawnschutz
  
  var angle =90;
  if(GetDir()== DIR_Right()) angle=-90;
  // Schuss an der Mündung der Waffe erstellen...
  var x=-Sin(angle,15),y;
  
  var rocket = CreateObject(MISS,x,y,GetOwner());
  rocket->Launch(-angle,20);
  
  Sound("Rocket");
}

public func Fire3()    // Bombe
{ 
  Local(101,pRider)=1;//beende Spawnschutz
  
  SetVar(0,CreateContents(BM5B));
  SetOwner(GetOwner(),Var());
  SetVar(1,GetDir());
  Exit(Var(0),0,15,-90+Var(1)*180,GetXDir()/10,GetYDir()/10);
  Sound("ABAbwurf");
}

public func Fire4()    // Atombombe
{ 
  Local(101,pRider)=1;//beende Spawnschutz
  
  SetVar(0,CreateContents(ATMB));
  SetOwner(GetOwner(),Var());
  SetVar(1,GetDir());
  Exit(Var(0),0,15,-90+Var(1)*180,GetXDir()/10,GetYDir()/10);
  Sound("ABAbwurf");
}

public func Fire5()    // Nichts
{ 
  SetCommand(pRider,"Throw");//Wirft
}

public func Fire6()    // Laser
{ 
  Local(101,pRider)=1;//beende Spawnschutz
  
  var angle =pRider->~AimAngle(10);
  //if(GetDir()== DIR_Right()) angle=-90;
  // Schuss an der Mündung der Waffe erstellen...
  var x=Sin(angle,15),y;
  
  //var user = GetUser();
  //var angle = user->~AimAngle(10) + RandomX(-3,+3);
  //var x,y; user->WeaponEnd(x,y);
  
  //var ammo = CreateObject(SHT2,x,y,GetOwner());//<-
  
  // int iAngle, int iSpeed, int iDist, int iSize, int iDmg, int iTrail, int iDmgType
  
  //ammo->Launch(angle,180,400,8,400, GetFMData(FM_Damage, 1),0,60);//<-


  var user = GetUser();
  y+=3;
  x=(GetDir()*2-1)*5;
  var laser = CreateObject(LASR,x,y,GetOwner(pRider));
	
  laser->SetClrModulation(RGBa(255,255,255,64));
  laser->SetContinuous(1);
  laser->Set(angle,7,700,15,this(),pRider);
//laser->Set(angle,7,GetBotData(BOT_Range,2),15,this());

	// Laser an einer ungültigen Position?
	if(!laser)
		return FM_Error;

  Sound("RailGunShot");
  
  // Effekte
  MuzzleFlash(250,this(),x,y,angle,RGBa(96,64,255,0));
  //Sound("EnergyRifle",0,ammo);
}

public func Fire7()    // Laser
{ 
  Sound("RailGunShot");
  var x= GetX()+GetXDir()*2;
  var y= GetY()+GetYDir()*2;
  DrawParticleLine ("EMPShock",0,0,x-GetX(),y-GetY(),3,120,RGBa(96,64,255,0),RGBa(96,64,255,0)); 
  SetPosition(x,y);
}

/*Jump and Run*/

public func ControlUpdate(object caller, int comdir, bool dig, bool throw)
{
  if(!caller) return(1);
  if(caller!= pRider) return(1);
  //SetUser(caller);
  //Message("%s",this(),GetName(caller));
  // autom. Schuss beenden, wenn Werfen losgelassen (JumpAndRun)
  UpdateComDir(comdir,dig,throw);
  if(IsRecharging() && !throw)
    StopAutoFire();
  // Nicht nachladen, wenn die Munition ausging und der Controller rechtzeitig
  // werfen wieder loslÃ¤sst.  
  else if(!throw)
    ClearScheduleCall(this(), "Reload");
  return(1);
}

func UpdateComDir(comdir)
{
	if(!comdir) SetComDir(COMD_Stop());
	return(1);
}

func JnRTimer()
{
	if(GetComDir()==COMD_UpRight() || GetComDir()==COMD_DownRight() || GetComDir()==COMD_UpLeft() || GetComDir()==COMD_DownLeft()) return(1);
	var xcom= GetComDir()==COMD_Right() || GetComDir()==COMD_Left();
	var ycom= GetComDir()==COMD_Up() || GetComDir()==COMD_Down();;
	JumpNRunControl(xcom,ycom);
	return(1);
}

func JumpNRunControl(iXCom,iYCom)
{
	if(!iXCom)
	{
	  if(GetXDir()>7) SetXDir(GetXDir()-1);
	  if(GetXDir()<-7) SetXDir(GetXDir()+1);
	}
		
	if(!iYCom)
	{
	  if(GetYDir()>7) SetYDir(GetYDir()-1);
	  if(GetYDir()<-7) SetYDir(GetYDir()+1);
	}
	if(!iXCom && !iYCom)
	 if(GetAction() eq "Hyperfly") SetAction("Fliegen");
	return(1);
}

/*Nach Links*/
func JnRLeft()
{
  if(GetComDir()==COMD_Left() || GetComDir()==COMD_UpLeft() || GetComDir()==COMD_DownLeft()) return(0);
  if(GetAction()ne"Fliegen") SetAction("Fliegen");
  SetDir(DIR_Left());
  return(SetComDir(COMD_Left()));
}

func JnRLeftDouble()
{
  if(GetAction()eq"Hyperfly") return(0);
  SetComDir(COMD_Left());
  SetPhysical("Float",800,2);
  return(SetAction("Hyperfly"));
}

/*Nach Rechts*/
func JnRRight()
{
  if(GetComDir()==COMD_Right() || GetComDir()==COMD_UpRight() || GetComDir()==COMD_DownRight()) return(0);
  if(GetAction()ne"Fliegen") SetAction("Fliegen");
  SetDir(DIR_Right());
  return(SetComDir(COMD_Right()));
}

func JnRRightDouble()
{
  if(GetAction()eq"Hyperfly") return(0);
  SetComDir(COMD_Right());
  SetPhysical("Float",800,2);
  return(SetAction("Hyperfly"));
}