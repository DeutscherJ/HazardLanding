/*-- Klumpen --*/

#strict

local innercount;

func SetTo(string Action) {
  SetAction(Action);
  return(1);
}

func Hit ()
{
  Sound("FleshHit*", 0, 0, 50);
  if(ObjectCount(BLUT)>1000) return(RemoveObject());
  Blood();
}

private func Blood () {
  //CastPXS("Blood", Random(20), Random(20));
  CastObjects(BLUT,Random(20),20);
  if(innercount >= 3) RemoveObject();
  innercount++;
}
