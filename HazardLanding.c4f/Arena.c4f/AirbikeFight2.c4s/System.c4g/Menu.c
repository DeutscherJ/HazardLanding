/*-- Men� v3--*/

#strict
#appendto CHOS

protected func OpenMenu()
{
  _inherited();
  
  var pClonk = GetCursor();
  if(!GetLength(aGoals)) AddMenuItem("Wurfgegenstand", "ThrowObject", idThrowObject, pClonk,0,0,"$DarknessChose$");
  return(1);
}

protected func ThrowObject()
{
  var pClonk = GetCursor();
  // Men� aufmachen
  CreateMenu(idThrowObject, pClonk, 0,0,0,0, 1);
  AddMenuItem("%s", "TO", ROCK, pClonk, 0, 0, " ");
  AddMenuItem("%s", "TO", FLNT, pClonk, 0, 0, " ");
  AddMenuItem("%s", "TO", SFLN, pClonk, 0, 0, " ");
  AddMenuItem("%s", "TO", EFLN, pClonk, 0, 0, " ");
  AddMenuItem("%s", "TO", BALL, pClonk, 0, 0, " ");
  // Letzten Eintrag ausw�hlen
}

static idThrowObject;

func TO(id object)
{
	idThrowObject= object;
	return(OpenMenu());
}