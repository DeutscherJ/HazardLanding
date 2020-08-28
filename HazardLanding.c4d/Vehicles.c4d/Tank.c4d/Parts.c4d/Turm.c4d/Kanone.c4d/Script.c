/*-- K.O-Gesch�tz --*/

#strict

public func Shoot(feuerer)    // Projektil-Dauerfeuer
{
  SetOwner(GetOwner(feuerer));
  var angle = GetR();
  var Granate = CreateObject(SFLN,Sin(GetR(), 50), -Cos(GetR(), 50));
  //Mal b�se rum tricksen:
  SetGraphics(0, Granate, GREN);
  Granate -> SetSpeed(Sin(GetR(), 101), -Cos(GetR(), 101));
  Granate -> SetRDir(3 * BoundBy(GetR(),-1,1));
  Granate -> SetOwner(GetOwner(feuerer));
  SetObjectOrder(GetActionTarget(),0,1);
  SetPlrView(GetOwner(feuerer),Granate);
  //Granate-> SetSpeed(Sin(GetR(), 101), -Cos(GetR(), 101));
  Sound("Blast3");
  MuzzleFlash(RandomX(60,100),this(),Sin(angle, 47), -Cos(angle,47),angle,0);
  return(Granate);
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


public func ResCat(){
//Durch einen doofen engine bug der Forerground objekte nicht wieder zur�ck setzt muss das objekt neu erschaffen werden :S
GetActionTarget() -> ResetCanon(GetR());
return(1);
}

public func AttachTargetLost(){
  return(RemoveObject());
}
//kann ge�ndert werden (In 2 frames)
public func SingleShotSpeed(){return(7 * 5);}

