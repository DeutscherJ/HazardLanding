/*-- Toter Panzer --*/

#strict

 
func Initialize() {
return(1);
}

public func Incineration(){
ScheduleCall(this(),"SelfExt",35 * 60,1);
}

public func SelfExt(){
  if(OnFire()) Extinguish();
  return(1);
}
