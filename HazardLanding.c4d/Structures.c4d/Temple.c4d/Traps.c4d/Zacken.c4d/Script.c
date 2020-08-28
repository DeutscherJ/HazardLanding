/*-- Zacken --*/

#strict

func Initialize()
{
  SetAction("Hang");
  return(1);
}

func Hit()
{
  CastObjects(WOOD,5+Random(2),25+Random(30));
  Explode(7);
  return(1);
}

public func Fall()
{
  SetAction("Fall");
  SetPlrViewRange(20);
  return(1);
}