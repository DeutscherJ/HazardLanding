#strict

Completion:
  SetAction("Scroll");
  return(1);
Damage:
  if (SEqual(GetAction(),"Broken")) return(0);
  SetAction("Broken");
  CastObjects(SHRD,20,10,0,0);
  Sound("GlassBreak");
  return(1);