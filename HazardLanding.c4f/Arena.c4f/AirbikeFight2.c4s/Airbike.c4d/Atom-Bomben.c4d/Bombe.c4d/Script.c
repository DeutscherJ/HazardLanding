/*-- Atombombe --*/

#strict
#include BM5B

func Hit()
{
  AtomExplode(60);
  SetSpeed(0,-100,CreateObject(SPT5,0,-5,GetOwner()));
  CreateObject(SPT6,0,-5,GetOwner())->Left();
  CreateObject(SPT6,0,-5,GetOwner())->Right();
  return(1);
}

global func AtomExplode(int iLevel, object pObj, id idEffect, string szEffect) {
  // Viewport wackeln
  ShakeViewPort(iLevel, pObj);
  // Sound muss vor dem Löschen des Objektes erzeugt werden, damit die Position stimmt
  var grade = BoundBy((iLevel/10)-1,1,3);
  Sound(Format("Blast%d", grade), false, pObj);
  // Explosionsparameter
  if (!pObj) if (!(pObj = this())) return false;
  var x=GetX(pObj), y=GetY(pObj);
  var cause_plr = GetController(pObj);
  var container = Contained(pObj);
  var exploding_id = GetID(pObj);
  var layer = GetObjectLayer(pObj);
  // Explosionsparameter gesichert: Jetzt das Objekt entfernen, damit es von der Explosion selber nicht betroffen ist
  RemoveObject(pObj);
  // Und die Explosion im globalen Kontext ausführen
  // Leider gibt es keine Möglichkeit, auf den globalen Kontext zuzugreifen (außer GameCall, aber das löst die Funktion immer neu auf)
  // Also zumindest den Objektkontext entfernen
  exploding_id->DoExplosion(x, y, iLevel, container, cause_plr, idEffect, szEffect, layer);
}

/*
global func AtomExplosion(int iLevel)
{
  BlastObjects(GetX(),GetY(),iLevel);
  CreateParticle("Smoke2",0,0,0,0,iLevel*10+Random(30),RGB(0,255,0));
  //CreateParticle("Smoke",0,0,0,0,iLevel*10,RGB(0,255,0));
  return(1);
}