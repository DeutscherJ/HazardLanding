#strict

Initialize:
  SetAction("Walk");
  return(1);
Damage:
  if(LessThan(30,GetDamage())) And(Sound("WoodDestruction*")&&CastObjects(W43V,5,25,0,0),RemoveObject());
  return(1);
IsHolz:
  return(1);

Hit:
  return(SetAction("Walk"));