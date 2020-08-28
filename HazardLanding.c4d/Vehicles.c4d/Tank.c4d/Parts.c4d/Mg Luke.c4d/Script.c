/*-- Mg Luke --*/

#strict

local spukk,mgfeuer,rapid;

func Initialize() {
   //s.p.u.k.k. = Schnell perforierendes Ultra Klein Kalieber
   spukk = CreateObject(CEMG);
   spukk -> SetAction("Attaching",this());
   spukk -> SetActionData(1);
   spukk -> SetR(90 * ((GetDir() * -2) + 1));   
   mgfeuer = 0;
  return(1);
}

public func GetCanon(){ return(spukk);}

public func Shoot(){
  if (!FindObject(NOAM)) {if (!GetActionTarget(0,GetActionTarget()) ->~ GetMgMuni()) {mgfeuer = 0; return(Message("$NoAmmoLeft$",this()));}
  GetActionTarget(0,GetActionTarget()) ->~ SetMgMuni(-1);
  }
  GetCanon() -> Shoot();
  rapid = GetCanon() -> Rapidspeed();
  return(1);
}

public func DrehbarkeitDo(){return(15);}
public func DrehbarkeitUp(){return(75);}

public func Reload(){
  
  
  //Message("%d",this(),UnMakeR(GetR(GetCanon())));
  //Maximale Dreh richtung berechnen und im ersnt fall setzen:
  //ein scheiß kompliziertes unterfangen :S
  SetR(GetR(GetActionTarget(0,GetActionTarget())));
  if (GetDir()){
    if (UnMakeR(GetR(GetCanon())) > MakeUMR(UnMakeR(MakeR(GetR() + 180 + DrehbarkeitDo() + 90)))) {GetCanon() -> SetR(GetR() + DrehbarkeitDo() + 180 + 90); SetRDir(0,GetCanon());}
    if (UnMakeR(GetR(GetCanon())) < MakeUMR(UnMakeR(MakeR(GetR() + 180 - DrehbarkeitUp() + 90)))) {GetCanon() -> SetR(GetR() - DrehbarkeitUp() + 180 + 90); SetRDir(0,GetCanon());}
  }
  else
  {
    if (UnMakeR(GetR(GetCanon())) > MakeUMR(UnMakeR(MakeR(GetR() + DrehbarkeitUp() + 90)))) {GetCanon() -> SetR(GetR() + DrehbarkeitUp() + 90); SetRDir(0,GetCanon());}
    if (UnMakeR(GetR(GetCanon())) < MakeUMR(UnMakeR(MakeR(GetR() - DrehbarkeitDo() + 90)))) {GetCanon() -> SetR(GetR() - DrehbarkeitDo() + 90); SetRDir(0,GetCanon());}
  }
  //nachlade script

  if (rapid <= 0) {
  if (mgfeuer == 1) {
    //if (!FindObject2(Find_ActionTarget(this()))) return(mgfeuer=0);
    Shoot();
  }
  else
  spukk ->   Sound("PanzerMG",0,0,0,0,-1);  
  return(1);
  }
  rapid --;
  return(1);
}

//Mg steuerung und so:

protected func ControlDownDouble(AntiSasCh){
  //SetObjectOrder(GetActionTarget(0,AntiSasCh));
  AntiSasCh -> SetAction("Walk");
  AntiSasCh -> Enter(GetActionTarget(0,GetActionTarget()));
  mgfeuer = 0;
  GetCanon() -> SetRDir(0);
  return(1);
}

protected func ControlThrow(KKenny){
  SetOwner(GetOwner(GetActionTarget()));
  spukk -> SetOwner(GetOwner());
  if (mgfeuer == 1){
  mgfeuer = 0;
  spukk -> Sound("PanzerMG",0,0,0,0,-1);
  } 
  else mgfeuer = 1;
  return(1);
}
public func UseRideThrow(){return(1);}

protected func ControlDig(){
  spukk -> SetRDir(0);
  return(1);
}

protected func ControlUp(){
  if (GetRDir(spukk) != 0) return(spukk -> SetRDir(0));
  if (GetDir() == DIR_Left()) return(spukk -> SetRDir(4));
  spukk -> SetRDir(-4);
  return(1);
}

protected func ControlUpDouble(){
  var FalschirmSpringer = FindObject(0,0,0,0,0,OCF_CrewMember(),"Ride",this());
  FalschirmSpringer -> SetAction("Dive");
  FalschirmSpringer -> SetYDir(-15);
  FalschirmSpringer -> SetXDir(-30 + (GetDir() * 60));
  mgfeuer = 0;
  GetCanon() -> SetRDir(0);
  return(1);
}

func UseRideUpDouble(){return(1);}

protected func ControlDown(){
  if (GetRDir(spukk) != 0) return(spukk -> SetRDir(0));
  if (GetDir() == DIR_Left()) return(spukk -> SetRDir(-4));
  spukk -> SetRDir(4);
  return(1);
}

protected func ControlRight(){
  if (GetR() == DIR_Right()) GetCanon() -> SetR(GetR(GetCanon()) + 180);
  SetDir(DIR_Right());
  return(1);
}

protected func ControlLeft(){
  if (GetR() == DIR_Left()) GetCanon() -> SetR(GetR(GetCanon()) + 180);
  SetDir(DIR_Left());
  return(1);
}

public func AttachTargetLost(){
  return(RemoveObject());
}
