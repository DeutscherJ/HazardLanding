/*-- Schadensregler --*/

#strict

func Initialize() {
   
  return(1);
}

public func Damage(){
  if (GetDamage() == 0) return(1);
  if (!GetActionTarget()) return(RemoveObject());
  if (GetActionTarget() ->~ Schaden(GetDamage()) == -1) return(RemoveObject());
  DoDamage(-GetDamage()); 
  return(1);
}

public func IsBulletTarget(id idBullet)
{
    //if(idBullet == STAM) return(false);
    return(true);
}

public func AttachTargetLost(){
  return(RemoveObject());
}
