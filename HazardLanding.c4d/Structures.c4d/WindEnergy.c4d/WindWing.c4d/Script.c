/*-- Windrad --*/

#strict


/* Initialisierung */

protected func Completion()
{
  SetR(122);
}

protected func Destruction()
{
  // MotionBlur-Effekt l�schen
  var obj;
  while (obj = FindObject(SWWF, 0,0,0,0, 0,"Fade",this()))
    RemoveObject(obj);
}

public func Init(windenergy)
{
  // wird von der Windkraftanlage aufgerufen
  SetAction("Turn", windenergy);
}


/* Action-Calls */

protected func Wind2Turn()
{
  var windenergy = GetActionTarget();
  // EMP-Einwirkung?
  if (FindObject(SEMP, 0,0,0,0, 0,"Active",windenergy))
  {
    SetRDir(0);
    DoEnergy(-100, windenergy);
    return(1);
  }
  // Energie erzeugen
  DoEnergy(Abs(GetRDir()), windenergy);
  SetRDir(GetWind()/4);
  // Update f�r Energieanzeige
  ShowInfoBar(IBRE, windenergy, Abs(GetWind()),100, 0,1);
}

private func CreateFading()
{
  // MotionBlur-Effekt erzeugen
  CreateObject(SWWF,0,0,GetOwner())->Init(this(), GetR());
}

