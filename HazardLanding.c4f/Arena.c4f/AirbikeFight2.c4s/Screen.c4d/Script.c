/*Bildschirm*/
#strict

func Initialize(){ return(SetAction("Scroll"));}
  
func Damage()
{
  if (GetAction()eq"Broken") return(0);
  SetAction("Broken");
  CastObjects(SHRD,20,10,0,0);
  Sound("GlassBreak");
  return(1);
}
