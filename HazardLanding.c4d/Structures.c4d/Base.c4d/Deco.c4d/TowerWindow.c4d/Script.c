/*Sichtfenster*/

#strict

func Damage()
{
  if (GetDamage()< 30) return(0);
  CastObjects(_TF1,2,30,0,+10);
  CastObjects(_TF2,5,40,0,-10);
  CastObjects(SHRD,40,20,0,0);
  RemoveObject();  
  Sound("Discharge");
  Sound("GlassBreak");
  return(1);
}