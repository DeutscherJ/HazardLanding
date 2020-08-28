#strict

protected Initialize:
  SetAction("Nothing");
  return(1);
  
protected Damage:
  if ( LessThan( GetDamage(), 65 ) ) return(0);
  CastObjects(SHRP,10,30,0,0);
  Explode(15);  
  return(1);

Incineration:
  return(Extinguish());


protected func CastSparks() {
  // Ab und zu mal
  if (Random(8)) return(0);
  Sound("Electric");
  CastParticles("MSpark", 10, 10, 0, +3, 10, 50, RGB(RandomX(100, 150), RandomX(200, 255), 255), RGB(RandomX(100, 150), RandomX(200, 255), 255));
}