/*-- MG-Geschütz --*/

#strict

public func Shoot()    // Projektil-Dauerfeuer
{
  var angle;
  angle = GetR() +RandomX(-6,+6);
 
  var ammo = CreateObject(SHT1,  Sin(angle, 18), -Cos(angle, 18), GetOwner(GetActionTarget()));
  //int iAngle, int iSpeed, int iDist, int iSize, int iTrail, int iDmg
  ammo->Launch(angle, 300, 600, 3, 100, 33,1);

  // Effekte
  MuzzleFlash(RandomX(20,50),this(),Sin(angle, 18), -Cos(angle,18),angle,0);
  Sound("PanzerMG",0,0,0,0,1);
}

func MuzzleFlash(int iSize, object pClonk, int iX, int iY, int iAngle, int iColor)
{
  if(!pClonk) pClonk = this();

  //Doofes Westernpack, klaut uns einfach den Partikelnamen.
  CreateParticle("MuzzleFlash2",iX,iY,
                 +Sin(iAngle,500),
                 -Cos(iAngle,500),
                 iSize*5,iColor,pClonk);
}


public func AttachTargetLost(){
  return(RemoveObject());
}

public func Rapidspeed(){ return(0);}

