#strict

func Damage()
{
  if (GetDamage()<30) return(0);
  CastObjects(_TF1,1,30,0,+10);
  CastObjects(_TF2,3,40,0,-10);
  CastObjects(SHRD,30,30);
  RemoveObject();  
  Sound("Discharge");
  Sound("GlassBreak");
  return(1);
}