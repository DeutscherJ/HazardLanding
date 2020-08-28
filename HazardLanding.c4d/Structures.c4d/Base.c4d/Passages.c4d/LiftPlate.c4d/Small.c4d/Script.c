/*-- Kleine Schwebeplatte --*/

/* Lokale Variablen */

// 0: Horizontale an/aus
// 1: Vertikale an/aus
// 2: ComDir für ResumeTravel, X/Y für SpeedTo
// 3: Y Obergrenze gesetzt
// 4: Y Obergrenze Transfer
// 5: Y Untergrenze Transfer

#strict
#include _LFP

protected UpdateTransferZone:
  // Nur vertikale Schwebeplatten
  if (Local(0)) return(0);
  // Obergrenze ermitteln
  while (And( GreaterThan(Sum(GetY(),Var(0)),5), Not(GBackSolid(0,Var(0))) ))
    SetVar(0,Sum(Var(0),-5));
  // Untergrenze ermitteln
  while (And( LessThan(Sum(GetY(),Var(1),15),Sub(LandscapeHeight(),5)), Not(GBackSolid(0,Sum(Var(1),15))) ))
    SetVar(1,Sum(Var(1),+5));
  // Transferzone setzen
  SetTransferZone(-15,Var(0),32,Sum(Sub(Var(1),Var(0)),15));
  // Ober- und Untergrenze speichern
  SetLocal(4,Sum(GetY(),Var(0)));
  SetLocal(5,Sum(GetY(),Var(1)));
  return(1);

protected Damage:
  if ( LessThan( GetDamage(), 150 ) ) return(0);
  CastObjects(SHRP,3,50,0,-5);
  CastObjects(SHRP,10,30,0,0);
  CastObjects(SHRP,3,40,0,-5);
  CastObjects(SHRP,10,20,0,0);
  
  var broken= CreateObject(BLFS);
  SetPosition(GetX(),GetY(),broken);
  SetRDir(RandomX(-2,2),broken);
  LocalN("x",broken)=GetX();
  LocalN("y",broken)=GetY();
  Local(0,broken)=Local(0);
  Local(1,broken)=Local(1);
  Local(2,broken)=Local(2);
  Local(3,broken)=Local(3);
  Local(4,broken)=Local(4);
  Local(5,broken)=Local(5);
  
  RemoveObject();  
  Sound("Discharge");
  Sound("Blast2");
  return(1);