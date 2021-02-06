/*-- Schmetterling --*/

#strict

protected func Initialize()
{
  // Farbe zufällig festlegen
  SetColorDw(RGB(Random(256),Random(256),Random(256)));
  SetAction("Fly");
  MoveToTarget();
  return(1);
}


/* TimerCall */  
 
private func Activity()
{
  // unter Wasser
  if (InLiquid()) return(SetComDir(COMD_Up()));
  // sitzt: warten
  if (SEqual(GetAction(),"Sit")) return(1);
  // neues Ziel
  if (!GetCommand() || !Random(5)) MoveToTarget();
  return(1);  
}

  
/* Bewegung */

private func Flying()
{
  // Richtung anpassen
  if (GetXDir() > 0)  SetDir(DIR_Right());
  if (GetXDir() < 0)  SetDir(DIR_Left());  
  // Aktion ändern
  if (!Random(3)) SetAction("Flutter");
  return(1);
}

private func Fluttering()
{
  // Richtung anpassen
  if (GetXDir() > 0)  SetDir(DIR_Right());
  if (GetXDir() < 0)  SetDir(DIR_Left());  
  // Aktion ändern
  if (!Random(7)) SetAction("Fly");
  return(1);
}

  
/* Kontakt */  
  
protected func ContactBottom()
{
  SetCommand(this(),"None");
  SetComDir(COMD_Up());
  return(1);  
}

public func SitDown()
{
  SetXDir(0);
  SetYDir(0);
  SetComDir(COMD_Stop());
  SetAction("Sit");
  SetCommand(0,"None");
  return(1);  
}

public func TakeOff()
{
  SetComDir(COMD_Up());
  return(1);  
}

private func MoveToTarget()
{
  var x = Random(LandscapeWidth());
  var y = Random(GetHorizonHeight(x)-60) + 30;
  SetCommand(this(),"MoveTo",0,x,y);
  return(1);
}

private func GetHorizonHeight(x)
{
  var y = 0;
  while ((y < LandscapeHeight()) && !GBackSemiSolid(x,y))
    y += 10;
  return(y);
 }
 
