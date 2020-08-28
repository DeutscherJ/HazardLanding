/*-- Käfig --*/

#strict

func Incineration()
{
  CastObjects(WOOD,1,25);
  RemoveObject();
  return(1);
}

func Open()
{
	SetSolidMask(25,0,25,18);
	SetAction("Open");
	Sound("Connect");
	return(1);
}