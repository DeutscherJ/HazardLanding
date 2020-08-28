/*-- Wolfsgeheul --*/

#strict

protected func Initialize()
{
  // Eigene Position festlegen
  SetPosition();
  return(1);
}

/* Sauberkeit überprüfen.. */
private func Howl()
{
  if(FindObject(TIME) && !IsNight()) return(0);
  if(Random(14)) return(0);//nur mit ein bissl Glück ist auch nen Wolf da
  Sound("Howl*",1,0,RandomX(80,120));
  return(1);
}