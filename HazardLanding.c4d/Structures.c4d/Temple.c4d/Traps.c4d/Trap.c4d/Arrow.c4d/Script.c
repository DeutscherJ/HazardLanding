/*-- Pfeil --*/

#strict
#include SHT1

private func Color(int iATime) {
  return(RGBa(255,255,255));
}

public func TrailColor(int iATime) {
  var iPrg = 100*iATime/iTime;
  return(RGBa(255-iPrg*2,255-iPrg*2,255-iPrg*2,iPrg*3));
}

public func GlowColor(int iATime) {
  return(RGBa(0,0,0,255));
}

// Extern für Überladung
private func CreateTrail(int iSize, int iTrail) {
  pTrail = CreateObject(ATRI,0,0,-1);
  if(pTrail) {
    pTrail->Set(iSize-2,iTrail,this());
    SetObjectBlitMode(GetObjectBlitMode(),pTrail);
  }
}

private func HitObject(object pObject)
{
  if(BulletStrike(pObject))
    Remove();
}
