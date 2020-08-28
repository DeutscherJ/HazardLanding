/*-- Neues Script --*/

#strict
#appendto CLNK
#appendto HZCK

func ContactBottom()
{
  if(FallDamage()) Aufschlag();
  return(_inherited());
}

func Aufschlag()
{
  if(!GetAlive()) return(0);//Lebt?
  var speed= Max(Abs(GetXDir()),Abs(GetYDir()));
  if(speed<70) return(0);
  DoEnergy(2*(70-speed));
  return(Sound("Hurt*"));
}