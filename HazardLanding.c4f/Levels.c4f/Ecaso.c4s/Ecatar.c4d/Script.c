/*-- Ecatar (Ersatz für den Mond) --*/

#strict

local phase;

protected func Initialize()
{
  // erstmal unsichtbar
  SetClrModulation(RGBa(255,255,255,255));
  SetAction("Shine");
  // Phase setzen
  phase = Random(12);
  SetPhase(phase);
  // Parallaxität: 20%
  Local(0) = 20;
  Local(1) = 20;
  return(1);
}

private func ResetPhase()
{
  SetPhase(phase);
  return(1);
}

public func SetLightness(value)
{
  // Transparenz neu setzen
  SetClrModulation(RGBa(255,255,255, 255-value));
  return(1);
}

public func Disappear()
{
  // es wird Morgen
  SetClrModulation(RGBa(255,255,255,255));
  // eine Mondphase weiter
  ++phase;
  if (phase >= 12) phase = 0;
  return(ResetPhase());
}

