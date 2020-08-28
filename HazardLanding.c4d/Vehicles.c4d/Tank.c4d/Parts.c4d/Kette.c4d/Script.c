/*-- Kette --*/

#strict

local schaden,kaputt,dmgprott,rollen,dmg;

func Initialize() {
   SetAction("Attach");
    var i;
    //alle schadensregler erstellen  
    dmg = [];
    while (i < GetVertexNum()){
    dmg[i] = CreateObject(CEDM,0,0,GetOwner());
    dmg[i] -> SetAction("Attach",this());
    dmg[i] -> SetActionData(i);
    i ++;
    }
  return(1);
}

local Boss;

public func Set(Chef){
  Boss = Chef;
  SetDir(1);
  return(1);
}

public func Rad1(){return(Get() ->~ Rad1());}
public func Rad2(){return(Get() ->~ Rad2());}
public func Get(){return(Boss);}

public func Posing(){
  //[Timer Funktion]
  //lebt der panzer noch?
  if (GetID(Get()) != CETA) return(RemoveObject());
  //Sonst kommt es zu unangenehmen turbolenzen :S :
  SetRDir(0);
  SetDir(GetDir(Get()));
  //erstmal position setzen:
  var angle = Angle(GetX(Rad1()),GetY(Rad1()),GetX(Rad2()),GetY(Rad2()));
  var dir;
  if (GetDir(Get()) == 1) dir = 180;
  var distanz = ObjectDistance(Rad1(),Rad2());
  SetPosition(GetX(Rad1()) + Sin(angle,distanz / 2),GetY(Rad1()) + Cos(angle,-distanz / 2)-2);
  /*if (!Inside(MakeUMR(UnMakeR(GetR())),UnMakeR(MakeR(angle + 90 + dir - 3)),UnMakeR(MakeR(angle + 90 + dir + 3))))
  {*/
  SetR(angle +90 + dir);
  SetYDir(-1);
  //jetzt ganz böse clonkz überrollen. Und nebenbei die engine ärgern
  var i,clonk;
  if (!Rad1() -> GetComDir()) return(1);
  if (rollen == 0) return(1);
  while (i < GetVertexNum()){
  if (clonk = FindObject2(Find_AtPoint(GetVertex(i),GetVertex(i,1) - 5 ),Find_OCF(OCF_Alive()),Find_Not(Find_AnyContainer()))){
  //den clonk so richtig durchr0xx0rn
  Fling(clonk,0,10);
  clonk -> DoEnergy(-1);
  }                           
  i ++;  
  clonk = 0;
  }
  return(1);
}

public func Roll(clnk){
  if (rollen == 0) {PlrMessage("$Override$",GetOwner(clnk)); return(rollen = 1);}
  if (rollen == 1) {PlrMessage("$OverrideNot$",GetOwner(clnk)); return(rollen = 0);}
  return(1);
}

public func AttachTargetLost(){
  return(RemoveObject());
}

public func GetDMG(){
return(schaden);
}

public func MaxSchaden(){return(100);}

public func Schaden(Val){
  if (kaputt == 1) return(1);
  if (dmgprott) return(1);
  schaden += Val;
  if (schaden > MaxSchaden()) {
  Boss ->~ RadKaputt();
  kaputt = 1;
  CreateObject(FLNT) ->~ Explode(50);
  while (FindObject(0,0,0,0,0,0,"Attach",this())) RemoveObject(FindObject(0,0,0,0,0,0,"Attach",this()));
  Message("$ChainBroke$",this());
  SetGraphics(0,this(),TOTR);
  SetAction("Attach2");
  }
  dmgprott = 1;
  ScheduleCall(this(),"reset",1,1);
  return(1);
}

public func reset(){ return(dmgprott = 0);}

/*public func IsBulletTarget(id idBullet,kugel)
{
    //Das teil ist bullet proofed oO
    if(idBullet == STAM) return(false);
    //mit doofen altmodischen scripts geben wir und nicht ab!
    if (kugel == 0) return(false);
    //Nur gewähren lassen wenn es in der nähe eines vertex ist:
    var i;
    while (i < GetVertexNum()){
      //ist es in x nähe?
      //Log("i:%d|k: %d/%d|ich: %d/%d",i,GetX(kugel),GetY(kugel),GetX() - GetVertex(i), GetY() - GetVertex(i,1));
      if (Inside(GetX(kugel),GetX() - GetVertex(i) - 8,GetX() - GetVertex(i) + 8)) if (Inside(GetY(kugel),GetY() - GetVertex(i,1) - 5,GetY() - GetVertex(i,1) + 5)) return(true);
      i++;
    //ein toll umfangreicher log
    }
    return(false);
}

public func Damage(){Message("Aua!");}
*/
local No;
public func SetOwner(iNewOwner,pObj){

  for(var obj in dmg){
  if (obj) obj -> SetOwner(iNewOwner,obj);
}
  No = 0;
  return(_inherited(iNewOwner,pObj));
}
