/*-- Panzer Turm --*/

#strict

local bumsmacher,reload,Luke,balken,schaden,dmgprott,kaputt,dmg;

func Initialize() {
   bumsmacher = CreateObject(CEBU,0,0,GetOwner());
   bumsmacher -> SetAction("Attaching",this());
   bumsmacher -> SetActionData(1);
   bumsmacher -> SetR(90 * ((GetDir() * -2) + 1));
  SetObjectOrder(GetActionTarget(),0,1);
   Luke = CreateObject(CELU,0,0,GetOwner());
   Luke -> SetAction("Attach",this());
   Luke -> SetActionData(2);
   dmg = CreateObject(CEDM);
   dmg -> SetAction("Attach",this());
   dmg -> SetActionData(2);
   dmg -> DoCon(100);
   /*spukk = CreateObject(CEMG);
   spukk -> SetAction("Attaching",this());
   spukk -> SetActionData(3);
   spukk -> SetR(90 * ((GetDir() * -2) + 1));   
   mgfeuer = -1;*/
  return(1);
} 
public func GetLuke() { return(Luke);}
public func GetCanon(){ return(bumsmacher);}

public func Turn(){
  if (kaputt == 1) return(1);
  if (WildcardMatch(GetAction(),"Turn*")) return(1);
  GetCanon() -> SetR(GetR(GetCanon()) + 180/* * -1*/);
  if (GetDir() == 1) {
  SetVertex(1,0,6,0,1);
  SetAction("TurnRight");
  GetCanon() -> SetAction("TurnFront");
  return(SetDir(0));
  }
  SetVertex(1,0,-6,0,1);
  SetAction("TurnLeft");
  SetCategory(8388612,GetCanon());
  GetCanon() -> SetAction("TurnBack");
  SetDir(1);
  return(1);
}

public func ResetCanon(dir){
  RemoveObject(bumsmacher);
  bumsmacher = CreateObject(CEBU,0,0,GetOwner());
  bumsmacher -> SetAction("Attaching",this());
  bumsmacher -> SetActionData(1);
  bumsmacher -> SetR(dir);
  return(1);
}

public func Shoot(Shooter){
  if (kaputt == 1) {Message("Defekt :S",this()); return(0);}
  if (WildcardMatch(GetAction(),"Turn*")) return(0);
  if (reload != 0) return(0);
  balken = CreateObject(CEBA);
  balken -> SetAction("Balken",this());
  balken -> SetActionData(3);
  GetCanon() -> Shoot(Shooter);
  reload = 1;
  return(1);
}

public func Hoch(){
  if (kaputt == 1) return(1);
//  if (WildcardMatch(GetAction(),"Turn*")) return(1);
  if (GetCanon() -> GetRDir() != 0) return(GetCanon() -> SetRDir(0)); 
  if (GetDir() == DIR_Left()) return(GetCanon() -> SetRDir(-4));
  GetCanon() -> SetRDir(4);
return(1);
}
public func Runter(){
  if (kaputt == 1) return(1);
///  if (WildcardMatch(GetAction(),"Turn*")) return(1);
  if (GetCanon() -> GetRDir() != 0) return(GetCanon() -> SetRDir(0)); 
  if (GetDir() == DIR_Left()) return(GetCanon() -> SetRDir(4));
  GetCanon() -> SetRDir(-4);
  return(1);
}

public func DrehbarkeitDo(){return(10);}
public func DrehbarkeitUp(){return(35);}

public func Reload(){
  if (kaputt == 1){ 
    if (GetDir()) {
    GetCanon() -> SetR(GetR() + DrehbarkeitDo() + 180 + 90);
    SetRDir(0,GetCanon());
    }
    else
    {
    GetCanon() -> SetR(GetR() - DrehbarkeitDo() + 90); 
    SetRDir(0,GetCanon());
    }  
  return(1);
  }
  if (GetAction() ne "Attach" &&! WildcardMatch(GetAction(),"Turn*")) RemoveObject();
  //Message("%d",this(),UnMakeR(GetR(GetCanon())));
  //Maximale Dreh richtung berechnen und im ersnt fall setzen:
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
  if (reload == 0) return(1);
  reload ++;
  balken ->~ SetPhase(reload * 10 /GetCanon() -> SingleShotSpeed());
  if (reload > GetCanon() -> SingleShotSpeed()) { reload = 0; RemoveObject(balken);}
  return(1);
}


//wichtige funktion die ein wert wie zb. 340 in -20 umwandelt. Also nach dem R wert
//denn es ist ja allgemein bekannt das es nur -180 bis 0 bis 180 gibt

global func UnMakeR(Val){
  if (Val < 0){
    Val += 360;
  return(Val);
  } 
  return(Val); 
}


//tranformiert zahlen wie 360° in eine clonk verstädnliche version
global func MakeR(Val){
  //ist er größer als 180?
  if (Val == 0) return(0);
  var dummy;
  dummy = CreateObject(ARRW);
  if (!dummy) return(Log("ERROR:Der Dummy pfeil wurde nicht erzeugt"));
  dummy -> SetR(Val);
  //if (GetR(dummy) == 0) return(Log("ERROR:Der pfeil wurde nicht gedreht"));
  Val = GetR(dummy);
  RemoveObject(dummy);
  return(Val); 
}

//transformiert grad werte über 360 oder so in 0-360 werte
global func MakeUMR(Val){
  return(UnMakeR(MakeR(Val)));
}
func IsCEVehilce() {return(1);}

public func AttachTargetLost(){
  return(RemoveObject());
}


public func GetDMG(){
return(schaden);
}

public func MaxSchaden(){return(200);}

public func Schaden(Val){
  if (kaputt == 1) return(1);
  if (dmgprott) return(1);
  schaden += Val;
  if (schaden > MaxSchaden()) {
  FindObject(CELU,0,0,0,0,0,"Attach",this()) ->~ RemoveObject();
  kaputt = 1;
  CreateObject(FLNT) ->~ Explode(30);
  SetGraphics(0,this(),TOTT);
  SetGraphics(0,GetCanon(),TOTK);
  RemoveObject(FindObject(CEDM,0,0,0,0,0,0,this()));
  return(1);
  }
  dmgprott = 1;
  ScheduleCall(this(),"reset",1,1);
  return(1);
}

public func reset(){ return(dmgprott = 0);}



public func GanzKaputt(){
  CastObjects(TOTT,1,60) -> Incinerate();
  CastObjects(TOTK,1,60);
  RemoveObject();
  return(1);
}
local No;
public func SetOwner(iNewOwner,pObj){


  if (dmg) dmg -> SetOwner(iNewOwner,dmg);

  return(_inherited(iNewOwner,pObj));
}
