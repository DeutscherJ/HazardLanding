/*-- Gebäudemanager --*/

#strict

local target, light, symbol;    // Objektpointer
local lx, ly, lSize, lColor;    // Licht: Vertices, Größe, Farbe
local energycheck;              // Energie überprüfen?


/* Initialisierung */

public func Init(par_target, nrg_check)
{
  // Aufruf vom Zielobjekt
  target = par_target;
  SetAction("Attach", target);
  energycheck = nrg_check;
  return(1);
}

public func InitLight(lightX, lightY, lightsize, lightcolor)
{
  // Licht aktivieren
  lx = lightX;
  ly = lightY;
  lSize = lightsize;
  lColor = lightcolor;
  return(1);
}

protected func Destruction()
{
  LightOff();
  SymbolOff();
  return(1);
}


/* Timer-Call */

private func Check()
{
  // Spielregel Energieverbrauch
  if (!FindObject(ENRG))
    DoEnergy(100, target);
  // EMP
  var emp = HasEMP(target);
  if (emp) DoEnergy(-100, target);
  // Energieüberprüfung
  if (energycheck)
  {
    var needed = !(target->~EnoughEnergy()); 
    if (!symbol && needed)  SymbolOn();
    if (symbol && !needed)  SymbolOff();
  }
  // Licht ein/aus, wenn nötig
  if (symbol || emp)
    return(LightOff());
  //if (!light && LightNeeded)  LightOn();
  //if (light && !LightNeeded)  LightOff();
  return(1);
}


/* Licht */

private func LightOn()
{
  // Gebäude hat kein Licht
  if (!lx && !ly) return(0);
  light = CreateObject(LGHT);
  light->Init(target, lx, ly, lSize, lColor);
  return(1);
}

private func LightOff()
{
  if (light) RemoveObject(light);
  return(1);
}


/* Symbol */

private func SymbolOn()
{
  symbol = CreateObject(SNOE);
  symbol->SetTarget(target);
  return(1);
}

private func SymbolOff()
{
  if (symbol) RemoveObject(symbol);
  return(1);
}

