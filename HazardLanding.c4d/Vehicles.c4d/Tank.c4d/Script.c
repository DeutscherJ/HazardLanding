/*-- Panzer --*/

#strict

local rad1,rad2,turm,boost,Kette,kette,dmgprott,schaden,On,MgMuni,Muni,Energie;
 
 
local dmg1,dmg2,dmg3;
   
func Initialize() {
  rad1 = CreateObject(CEWE,0,0,GetOwner());
  rad2 = rad1 -> Set(0,this());
  rad2 -> BeRad1();
  //SetEntrance(1);
  SetAction("Be");
  turm = CreateObject(CETO,0,0,GetOwner());
  turm  -> SetAction("Attach",this());
  turm -> SetObjectOrder(this(),0,1);
  kette = CreateObject(CEKE,0,0,GetOwner());
  kette -> Set(this());
  kette -> SetObjectOrder(this(),0,1);
  if (!Random(2)) {
  SetDir(1);
  if (rad1 -> IsRight()) rad1 -> Change();
  SetVertex(0,0,-18,0,1);
  SetVertex(0,1,16,0,1);  
  }
   else { 
  if (!rad1 -> IsRight()) rad1 -> Change();
  SetDir(0);
  SetVertex(0,0,18,0,1);
  SetVertex(0,1,16,0,1);
   }
  ContainedDown();
  //schadens regel objekte
  var blubb;
  dmg1 = CreateObject(CEDM,0,0,GetOwner());
  dmg1 -> SetAction("Attach",this());
  dmg1 -> SetActionData(2); 
  dmg1 -> DoCon(+100); 
  dmg2 = CreateObject(CEDM,0,0,GetOwner());
  dmg2 -> SetAction("Attach",this());
  dmg2 -> SetActionData(1); 
  dmg2 -> DoCon(+100);
  dmg3 = CreateObject(CEDM,0,0,GetOwner());
  dmg3 -> SetAction("Attach",this());
  dmg3 -> SetActionData(3); 
  dmg3 -> DoCon(+100);  
  Energie = 200 * 35;
  Muni = 5;
  MgMuni = 50;
  //Glim();
  return(1);
}
func GetMgMuni(){return(MgMuni);}
func SetMgMuni(Val){MgMuni += Val;}
func Rad1(){return(rad1);}
func Rad2(){return(rad2);}

public func Tanken(){
  if (!turm) RemoveObject();
  SetRDir(0);
  if (boost >= 0) boost --;
  //erstmal position setzen:
  var angle = Angle(GetX(rad1),GetY(rad1),GetX(rad2),GetY(rad2));
  var distanz = ObjectDistance(rad1,rad2);
  var dir;
  if (rad1 -> IsRight()) dir = 180;
  SetPosition(GetX(rad1) + Sin(angle,distanz / 2),GetY(rad1) + Cos(angle,-distanz / 2)-2);
  /*if (!Inside(MakeUMR(UnMakeR(GetR())),UnMakeR(MakeR(angle + 90 + dir - 3)),UnMakeR(MakeR(angle + 90 + dir + 3))))
  {*/
  SetR(angle +90  + dir);
  turm -> SetR(angle +90  + dir);
  SetYDir(-1);
  if (On){
    if (!FindObject(0,0,0,0,0,OCF_CrewMember(),0,0,this())) {Sound("PanzerOff"); On = 0;}
    if (!Random(5)) Smoke(-(GetDir() * -2 + 1) * 35,-10,2);
    //if (KetteKaputt()) { Sound("PanzerDrive",0,0,0,0,-1); if (On = 1) Sound("PanzerOff"); On = 0;}
  }
  //Sound("PanzerDrive",0,0,0,0,-1);
  if (!FindObject(NOAM)) if(!KetteKaputt()) {
    if (Energie <= 0) {
    SetPhysical("Walk",0,PHYS_Temporary,rad1);
    SetPhysical("Walk",0,PHYS_Temporary,rad2);    
    if (On == 1) Sound("PanzerOff");
    On = 0;
    //Sound("PanzerDrive",0,0,0,0,-1);
    }
    if (Energie > 0) {
    if (GetComDir(rad1)) Energie --;
    if (GetEffect("Boost",this())) return(1);
    if (GetEffect("PrepBoost",this())) return(1);
    SetPhysical("Walk",50000,PHYS_Temporary,rad1);
    SetPhysical("Walk",50000,PHYS_Temporary,rad2);       
    }
  }
  //haben wir noch saft :O?
  return(1);
}

public func KetteKaputt(){
  if (Kette == 1) return(1);
  return(0);
 }

public func RadKaputt(){
  Kette = 1;
  if (On = 1) Sound("PanzerOff");
  On = 0;
  SetPhysical("Walk",0,PHYS_Temporary,rad1);
  SetPhysical("Walk",0,PHYS_Temporary,rad2);
  Sound("PanzerDrive",0,0,0,0,-1);
  return(1);
}

public func ContainedLeft(dumy,fnormal){
  if (fnormal) return(_inherited(dumy,fnormal));
  if (!On) return(1);
  if (KetteKaputt()) return(PlayerMessage(GetOwner(dumy),"$ChainBreak$",dumy));
  rad1 -> SetComDir(COMD_Left());
  rad2 -> SetComDir(COMD_Left());  
  SetDir(1);
  //Wenn rad1 vorne liegt kommt der panzer auch nicht durch Wände und so
  if (rad1 -> IsRight()) rad1 -> Change();
  SetVertex(0,0,-18,0,1);
  SetVertex(0,1,16,0,1);  
  return(1);
}

public func ContainedRight(dummy,fnormal){
  if (fnormal) return(_inherited(dummy,fnormal));
  if (!On) return(1);
  if (KetteKaputt()) return(PlayerMessage(GetOwner(dummy),"$ChainBreak$",dummy));
  rad1 -> SetComDir(COMD_Right());
  rad2 -> SetComDir(COMD_Right());  
  if (!rad1 -> IsRight()) rad1 -> Change();
  SetDir(0);
  SetVertex(0,0,18,0,1);
  SetVertex(0,1,16,0,1);
  return(1);
}



public func ContainedUp(pClonk){
  //Ein doofes menü  
  CreateMenu(CETA,pClonk,this(),0,"Panzer menü");
  AddMenuItem("asdasda",0,CEDM,pClonk,0,pClonk);
  AddMenuItem("Informationen","Info",RMMG,pClonk,0,pClonk,"$P_Information$");
  AddMenuItem("asdasda",0,CEDM,pClonk,0,pClonk);
  //AddMenuItem("",0,CEDM,pClonk,0,pClonk,"Sasch zwingt mich so doofe menüs zu machen :_(");
  AddMenuItem("$GoUp$","Aufstieg",MASC,pClonk,0,pClonk,"$MgMessage$");
  AddMenuItem("$Engine$","Anaus",CTSM,pClonk,0,pClonk,"$EngineInfo$");
  AddMenuItem("$Muni$","Munition",STAP,pClonk,0,pClonk,"$MuniInfo$");
  AddMenuItem("asdasda",0,CEDM,pClonk,0,pClonk);
  AddMenuItem("$OverrideSwitch$","Roll",CEKE,pClonk,0,pClonk,"$OverrideInfo$");
  AddMenuItem("asdasda",0,CEDM,pClonk,0,pClonk);
  SelectMenuItem(4,pClonk);
  Schedule("SetMenuSize(3,3)",2,1,pClonk);
  return(1);
}

public func Munition(blubb,pClonk){
  if (!Contents(0,pClonk)) return(1);
  if (!Contents(0,pClonk) ->~ IsAmmoPacket()) return(1);
  if (FindObject(NOAM)) return(PlayerMessage(GetOwner(pClonk),"$NoAmmoNeeded$",pClonk));
  if (GetID(Contents(0,pClonk)) ->~ AmmoID() == GSAM) {Energie += Contents(0,pClonk)-> AmmoCount() * 35; RemoveObject(Contents(0,pClonk)); return(1);}
  if (GetID(Contents(0,pClonk)) ->~ AmmoID() == STAM) {MgMuni += Contents(0,pClonk)-> AmmoCount(); RemoveObject(Contents(0,pClonk)); return(1);}
  if (GetID(Contents(0,pClonk)) ->~ AmmoID() == GRAM) {Muni += Contents(0,pClonk)-> AmmoCount(); RemoveObject(Contents(0,pClonk)); return(1);}
  PlayerMessage(GetOwner(pClonk),"Keine Munition Gefunden ({{STAP}}{{GRAP}}{{GSAP}})!",pClonk);
  return(1);
}

public func Nix(){return(1);}

public func Roll(dummy,pClonk){
  if (KetteKaputt()) return(PlayerMessage(GetOwner(pClonk),"$ChainBreak$",pClonk));
  kette -> Roll(pClonk);
  return(1);
}

public func Info(Doofkopp,pClonk){
  CreateMenu(RMMG,pClonk,this(),0,"Informationen:",0,3);
  AddMenuItem("$ExistAmmo$",0,CEDM,pClonk);
  AddMenuItem(Format("$EGrenades$",Muni),0,GRAP,pClonk);
  AddMenuItem(Format("$EPatrone$",MgMuni),0,STAP,pClonk);
  AddMenuItem(Format("$EEnergy$",Energie / 35),0,GSAP,pClonk);  
  AddMenuItem("",0,CEDM,pClonk);
  AddMenuItem("$Condition$",0,CEDM,pClonk);
  AddMenuItem(Format("$CChassi$",100 - (schaden * 100) / MaxSchaden()),0,CETA,pClonk);
  AddMenuItem(Format("$CTower$",100 - turm -> GetDMG() * 100 / turm -> MaxSchaden()),0,CETO,pClonk);
  AddMenuItem(Format("$CChain$",100 - kette -> GetDMG() * 100 / kette -> MaxSchaden()),0,CEKE,pClonk);
  return(1);
}

public func GetDMG(){
return(schaden);
}


public func ActivateEntrance(pObj){
  if (ObjectCount2(Find_Container(this()),Find_OCF(OCF_CrewMember())) >= 3) return(1);
  if (FindObject2(Find_Container(this()),Find_OCF(OCF_CrewMember()))) if (Hostile(GetOwner(),GetOwner(pObj))) return(1);
  SetOwner(GetOwner(pObj));
  Enter(this(),pObj);
  return(1);
}

  
public func Anaus(dumy,pclnk){
  if (KetteKaputt()) return(PlayerMessage(GetOwner(pclnk),"$ChainBreak$",pclnk));
  if (!On) {Sound("PanzerOn"); return(On = 1);}
  rad1 -> SetComDir(COMD_None());
  rad2 -> SetComDir(COMD_None());
  Sound("PanzerDrive",0,0,0,0,-1);
  Sound("PanzerOff");
  if (On)  return(On = 0);  
  }
  
public func Aufstieg(SasCh,mgheinz){
  if (!turm ->~ GetLuke()) return(PlayerMessage(GetOwner(mgheinz),"$TowerBreak$",mgheinz));
  if (FindObject(0,0,0,0,0,OCF_CrewMember(),"Ride",turm -> GetLuke())) return(PlayerMessage(GetOwner(mgheinz),"Besetzt",mgheinz));
  mgheinz -> Exit();
  if (!mgheinz -> SetAction("Ride",turm -> GetLuke())) {PlayerMessage(GetOwner(mgheinz),"$MsgNoGoodRider$",mgheinz,GetName(mgheinz));}
  mgheinz -> SetActionData(2);
  if (!FindObject(0,0,0,0,0,OCF_CrewMember(),0,0,this())){
  ContainedDown();
  if (On = 1) Sound("PanzerOff");
  On = 0;
  }
  return(1);
}
  
public func ContainedDown(){
  rad1 -> SetComDir(COMD_None());
  rad2 -> SetComDir(COMD_None());
return(1);
}

public func ContainedDownDouble(opfer){
  if (On == 1) Sound("PanzerOff");
  On = 0;
return(Exit(opfer));
}

public func ContainedThrow(Sven3,fnormal){
  if (fnormal) return(_inherited(Sven3,fnormal)); 
  if (!FindObject(NOAM)) if (Muni <= 0) return(PlayerMessage(GetOwner(Sven3),"$NoAmmo$",Sven3));
  if (turm -> Shoot(Sven3)) if (!FindObject(NOAM)) Muni --;
  return(1);
}

public func ContainedDig(){
  if (turm -> LocalN("kaputt")) return(Message("$TowerBreak$",this()));
  turm -> Turn();
  return(1);
}

public func ContainedSpecial(){
  turm -> Hoch();
  return(1);
}

public func ContainedSpecial2(){
  turm -> Runter();
  return(1);
}

public func UseSpecial() { return(1);  }
public func UseSpecial2(){ return(1);  }


public func ContainedRightDouble(){
  if (!On) return(1);
  if (KetteKaputt()) return(Message("$ChainBreak$",this()));
  Boost();
  return(1);
 }
 

public func ContainedLeftDouble(){
  if (!On) return(1);
  if (KetteKaputt()) return(Message("$ChainBreak$",this()));
  Boost();
  return(1);
 }
 
 public func Collection2(pObj){
   SetOwner(GetOwner(pObj));
   kette -> SetOwner(GetOwner(pObj));
   turm -> SetOwner(GetOwner(pObj));
   return(0);
 }
 
 public func Boost(){
   if (boost > 0) return(1);
   if (!FindObject(NOAM)){ if (Energie <= 3 * 35) return(Message("$LowEnergy$",this()));
   Energie -= 3 * 35;}
   boost = 10 * 35 / 2;
  AddEffect("PrepBoost", this(), 300, 70,this(),0,rad1,rad2);
   for(var objs in FindObjects(Find_ActionTarget(kette))) objs ->  CreateParticle("Fire2",0,0,0,-5,100);
   return(1);
 }

public func FxPrepBoostStart(object pTarget, int iEffectNumber, int iTemp,Rad1,Rad2){
  EffectVar(0,pTarget,iEffectNumber) = Rad1;
  EffectVar(1,pTarget,iEffectNumber) = Rad2;
  SetPhysical("Walk",1,PHYS_Temporary,EffectVar(0,pTarget,iEffectNumber));
  SetPhysical("Walk",1,PHYS_Temporary,EffectVar(1,pTarget,iEffectNumber));
 // Log("Start");
  return(1);
}

public func FxPrepBoostStop(object pTarget, int iEffectNumber, int iReason, bool fTemp){
  SetPhysical("Walk",50000,PHYS_Temporary,EffectVar(0,pTarget,iEffectNumber));
  SetPhysical("Walk",50000,PHYS_Temporary,EffectVar(1,pTarget,iEffectNumber));
 // Log("Stop");
  AddEffect("Boost", pTarget, 300, 70,pTarget,0,EffectVar(0,pTarget,iEffectNumber),EffectVar(1,pTarget,iEffectNumber));
  return(1);
}

public func FxBoostStart(object pTarget, int iEffectNumber, int iTemp,Rad1,Rad2){
  EffectVar(0,pTarget,iEffectNumber) = Rad1;
  EffectVar(1,pTarget,iEffectNumber) = Rad2;
  SetPhysical("Walk",70000,PHYS_Temporary,EffectVar(0,pTarget,iEffectNumber));
  SetPhysical("Walk",70000,PHYS_Temporary,EffectVar(1,pTarget,iEffectNumber));
  //Log("Start2");
}

public func FxBoostStop(object pTarget, int iEffectNumber, int iReason, bool fTemp){
  SetPhysical("Walk",50000,PHYS_Temporary,EffectVar(0,pTarget,iEffectNumber));
  SetPhysical("Walk",50000,PHYS_Temporary,EffectVar(1,pTarget,iEffectNumber));
 // Log("Stop2");
}


local down, glimmer;
func Glim(){
  ScheduleCall(this(),"Glimmering",1,10);
  ScheduleCall(this(),"Glim",10,1);
  return(1);
}

func Glimmering(){
    if (down == true) glimmer -= 10;
    if (down == false) glimmer += 10;
    if (glimmer >= 50) {down = true; glimmer = 50;}
    if (glimmer <= 1) {down = false; glimmer = 1;}        
    SetClrModulation(HSLa(170,205,255 - glimmer));
  return(1);
}

func IsCEVehilce() {return(1);}
//Schedule("CreateObject(GOLD) -> Explode(10)",1,100)
global func PanzerKaputt(){CreateObject(CETA) -> Schedule("CreateObject(GOLD) -> Explode(10)",1,100); return(1);}

public func Schaden(Val){
  if (dmgprott) return(1);
  schaden += Val;
  if (schaden > MaxSchaden()) {
  while (FindObject(0,0,0,0,0,0,"Attach",this())) RemoveObject(FindObject(0,0,0,0,0,0,"Attach",this()));
  //wir sind heute mal ganz verschwenderisch
  CreateObject(GOLD) -> Explode(50);
  Sound("PanzerExplode");
  //alles doofe unnötige entfernen und kurz und klein schlagen:
  CreateObject(TOTC) -> Incinerate();
  //zu faul um neue variablen zu erzeugen :S
  turm = CreateObject(TOTT);
  turm -> Incinerate();
  turm -> SetSpeed(RandomX(-30,30),-Random(50) - 30);
  turm -> SetRDir(RandomX(-20,20));
  turm = CreateObject(TOTK);
  turm -> SetSpeed(RandomX(-30,30),-Random(50) - 30);
  turm -> SetRDir(RandomX(-20,20));
  turm = CreateObject(TOTR);
  turm -> Incinerate();
  while (FindObject(CEDM,0,0,0,0,0,0,this())) RemoveObject(FindObject(CEDM,0,0,0,0,0,0,this()));
  RemoveObject();
  return(-1);
  }
  dmgprott = 1;
  ScheduleCall(this(),"reset",1,1);
  return(1);
}

public func MaxSchaden(){return(500);}

public func reset(){ return(dmgprott = 0);}


public func Destruction(){
Incinerate();
rad1 -> RemoveObject();
rad2 -> RemoveObject();
}


//dooofe unnötige blink effekte

/*
global func BLINK(){
  Blink(20,RGBa(255,0,255),10);
  return(1);
}

global func Blink(int Times,iRGB,int Speed,object pObj){
  if (!pObj) pObj = this();
  if (!this()) return(0);
  if (!Speed) Speed = 5;
  AddEffect("FXBlink",pObj,350,1,0,CETA,Times,iRGB,Speed);
  return(1);
}

protected func FxFXBlinkStart(object pTarget, int iEffectNumber, int iTemp,Times,iRGB,Speed){
  EffectVar(0,pTarget,iEffectNumber) = Times;
  EffectVar(1,pTarget,iEffectNumber) = iRGB;  //farbe
  EffectVar(2,pTarget,iEffectNumber) = GetObjectBlitMode(pTarget);
  EffectVar(3,pTarget,iEffectNumber) = GetClrModulation(pTarget);
  EffectVar(4,pTarget,iEffectNumber) = Speed;
  SetObjectBlitMode(4, pTarget);
  return(1);
}

protected func FxFXBlinkTimer(object pTarget, int iEffectNumber, int iTimes){ 
  pTarget -> SetClrModulation(RGBa(255 - iTimes *EffectVar(4,pTarget,iEffectNumber) * GetRGBaValue(EffectVar(1,pTarget,iEffectNumber),1) /255,255 - iTimes *EffectVar(4,pTarget,iEffectNumber) * GetRGBaValue(EffectVar(1,pTarget,iEffectNumber),2) /255,255 - iTimes *EffectVar(4,pTarget,iEffectNumber)  * GetRGBaValue(EffectVar(3,pTarget,iEffectNumber),1) /255));          
  if (iTimes * EffectVar(4,pTarget,iEffectNumber) > 255) return(-1);
  return(1);
}

protected func FxFXBlinkStop(object pTarget, int iEffectNumber, int iTemp){
  SetObjectBlitMode(EffectVar(2,pTarget,iEffectNumber),pTarget);
  SetClrModulation(EffectVar(3,pTarget,iEffectNumber),pTarget);
  AddEffect("FXBackBlink",pTarget,350,1,0,CETA,EffectVar(0,pTarget,iEffectNumber) - 1,EffectVar(1,pTarget,iEffectNumber),EffectVar(4,pTarget,iEffectNumber));
  return(1);
}

protected func FxFXBackBlinkStart(object pTarget, int iEffectNumber, int iTemp,Times,iRGB,Speed){
  EffectVar(0,pTarget,iEffectNumber) = Times;
  EffectVar(1,pTarget,iEffectNumber) = iRGB;  //farbe
  EffectVar(2,pTarget,iEffectNumber) = GetObjectBlitMode(pTarget);
  EffectVar(3,pTarget,iEffectNumber) = GetClrModulation(pTarget);
  EffectVar(4,pTarget,iEffectNumber) = Speed;  
  SetObjectBlitMode(4, pTarget);
  return(1);
}

protected func FxFXBackBlinkTimer(object pTarget, int iEffectNumber, int iTimes){ 
  pTarget -> SetClrModulation(RGBa(255 - ((iTimes - 51) * -1) *EffectVar(4,pTarget,iEffectNumber) * GetRGBaValue(EffectVar(1,pTarget,iEffectNumber),1) /255 ,255 - ((iTimes - 51) * -1) *EffectVar(4,pTarget,iEffectNumber) * GetRGBaValue(EffectVar(1,pTarget,iEffectNumber),2) /255 ,255 - ((iTimes - 51) * -1) *EffectVar(4,pTarget,iEffectNumber)  * GetRGBaValue(EffectVar(3,pTarget,iEffectNumber),1) /255 ));          
  if (iTimes * EffectVar(4,pTarget,iEffectNumber) > 255) return(-1);
  return(1);
}

protected func FxFXBackBlinkStop(object pTarget, int iEffectNumber, int iTemp){
  SetObjectBlitMode(EffectVar(2,pTarget,iEffectNumber),pTarget);
  SetClrModulation(EffectVar(3,pTarget,iEffectNumber),pTarget);
  if (EffectVar(0,pTarget,iEffectNumber) == 0) AddEffect("FXBlink",pTarget,350,1,0,CETA,EffectVar(0,pTarget,iEffectNumber),EffectVar(1,pTarget,iEffectNumber),EffectVar(4,pTarget,iEffectNumber));
  return(1);
}


//Blink(255,RGBa(255,255,255),this())





/*

func ControlThrow()
{
	var TGrenade = CreateContents(GetGrenadeTyp(GrenadeTyp), ExeClonk);
	var TWinkel = GetWinkel(Winkel);

var dir = -1;
if (GetDir(ExeClonk) == 1) dir = 1;
Exit(TGrenade, -20 * dir, -5, TWinkel,Sin(TWinkel, Power * 2) * dir,Cos(TWinkel,-Power * 2) * dir);
 
		TGrenade->PrepareMain();
		SetCursor(GetOwner(ExeClonk), ExeClonk, 1, 1);
		ExeClonk->SetAction("Walk");
		RemoveObject();
}




/*var dir = -1;
if (GetDir(ExeClonk) == 1) dir = 1;
Exit(TGrenade, -4, -5, TWinkel,Sin(TWinkel, Power * 2) * dir,Cos(TWinkel,-Power * 2) * dir);

GetDir(ExeClonk) -1*Cos(TWinkel, Power*2), -Sin(TWinkel,Power*2) );
*/
local No;

public func SetOwner(iNewOwner,pObj){
  if(dmg1) dmg1 -> SetOwner(iNewOwner,dmg1);
  if(dmg2) dmg2 -> SetOwner(iNewOwner,dmg2);
  if(dmg3) dmg3 -> SetOwner(iNewOwner,dmg3);
  if(kette)kette -> SetOwner(iNewOwner,kette);
  if(turm) turm -> SetOwner(iNewOwner,turm);
  return(_inherited(iNewOwner,pObj));
}
