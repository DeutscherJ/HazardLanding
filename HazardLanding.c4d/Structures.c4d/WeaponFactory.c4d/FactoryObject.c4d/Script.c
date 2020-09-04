/*-- Fabrik-Objekt --*/

#strict
#include FCOB


/* Produktionsmen� */

private func OpenProductionMenu(symbol, caller)
{
  // Men� erzeugen und mit Baupl�nen des Spielers f�llen
  Endless = (symbol==SYF3);
  CreateMenu(symbol,caller, this(),1,"Keine Baupl�ne vorhanden");
  var num = -1;
  var plan;
  while (plan = GetPlrKnowledge(GetController(caller),0,++num,C4D_All()))
    if (DefinitionCall(plan,"IsWeaponProduct") || DefinitionCall(plan,"IsAnvilProduct"))
      AddMenuItem("Herstellung: %s", "SelectProduction", plan,caller);
  return(1);
}


/* Raucheffekt */

private func DoSmoke()
{
  // Fabrikschlote rauchen lassen
  if (Random(2)) Smoke(-40,-26, 5+Random(6));
  if (Random(2)) Smoke(-38,-26, 5+Random(6));
  if (Random(2)) Smoke(-28,-26, 5+Random(6));
  if (Random(2)) Smoke(-23,-26, 5+Random(6));
  return(1);
}

