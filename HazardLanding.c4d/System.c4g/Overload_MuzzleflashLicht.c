/*-- Da dass Muzzleflash in der Standardeinstellung ein grelles Licht abgibt,d ass beim Airbike zu stark sein kann, wird hier das Licht deaktiviert. --*/

#strict

global func MuzzleFlash(int iSize, object pClonk, int iX, int iY, int iAngle, int iColor, bool fLight)
{
  if(!pClonk) pClonk = this();

  //Doofes Westernpack, klaut uns einfach den Partikelnamen.
  CreateParticle("MuzzleFlash2",iX,iY,
                 +Sin(iAngle,500),
                 -Cos(iAngle,500),
                 iSize*5,iColor,pClonk);
  if(!IsDark() || fLight)
    return();
  
  if(!iColor)
    iColor = RGB(255,255,255);
  
  var r,g,b,a;
  SplitRGBaValue(iColor,r,g,b,a);
  iColor = RGBa(r,g,b,Min(a+65,255));
  
  AddLightFlash(iSize*25, iX, iY, iColor);
}
