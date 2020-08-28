/*-- Fabrik-Objekt --*/

#strict
#include FCOB


/* Produktionsmenü */

private func OpenProductionMenu(symbol, caller)
{
  // Menü erzeugen und mit Bauplänen des Spielers füllen
  Endless = (symbol==SYF3);
  CreateMenu(symbol,caller,this(),1,"Keine Baupläne vorhanden");
  var num = -1;
  var plan;
  while (plan = GetPlrKnowledge(GetController(caller),0,++num,C4D_Vehicle()))
    if (DefinitionCall(plan,"IsVehicleProduct"))
      AddMenuItem("Herstellung: %s", "SelectProduction", plan,caller);
  return(1);
}


/* Raucheffekt */

private func DoSmoke()
{
  // Fabrikschlote rauchen lassen
  Smoke(51,-33, 8+Random(8));
  Smoke(46,-29, 8+Random(8));
  if (!Random(4)) Smoke(-24,10, 3+Random(3));
  if (!Random(4)) Smoke(-17,10, 3+Random(3));
  return(1);
}

