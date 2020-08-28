/*-- Fabrik-Objekt --*/

#strict
#include FCOB


/* Produktionsmenü */

private func OpenProductionMenu(symbol, caller)
{
  // Menü erzeugen
  Endless = (symbol==SYF3);
  CreateMenu(symbol,caller, this(),1,"Keine Baupläne vorhanden");
  // erstmal spezielle Produkte
  AddMenuItem("Holz in Kohle umwandeln",     "SpecialProduction", SYCH,caller, 0,COAL, "Kohle aus 1x Holz herstellen",    2,0);
  AddMenuItem("Kohle in Kristall umwandeln", "SpecialProduction", SYCH,caller, 0,CRYS, "Kristall aus 2x Kohle herstellen",2,1);
  // mit weiteren Bauplänen des Spielers füllen
  var num = -1;
  var plan;
  while (plan = GetPlrKnowledge(GetController(caller),0,++num,C4D_Object()))
    if (DefinitionCall(plan,"IsChemicalProduct"))
      AddMenuItem("Herstellung: %s", "SelectProduction", plan,caller);
  return(1);
}

private func SpecialProduction(par0, ID)
{
  SelectProduction(ID, 500);
}


/* Raucheffekt */

private func DoSmoke()
{
  // Fabrikschlote rauchen lassen
  Smoke(-28,-30, 5+Random(6));
  Smoke(-31,-27, 5+Random(6));
  return(1);
}


/* Eigenschaften */

private NeedEnergy: return(0);

