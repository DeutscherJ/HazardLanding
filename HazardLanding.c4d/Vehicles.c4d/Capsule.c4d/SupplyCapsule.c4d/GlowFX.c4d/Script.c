/*-- Glüheffekt --*/

#strict

local step;


/* Aufruf durch die Landekapsel */

public func Init(capsule, angle)
{
  SetAction("Burn",capsule);
  SetR(angle);
  // immer vor der Kapsel
  SetObjectOrder(capsule,this());
  return(1);
}

public SwitchOff:
  SetAction("SwitchOff");
  step = 0;
  return(1);


/* Action-Calls */

private func Burning()
{
  // Effekte
  Smoke(0, 0, 10);
  CastParticles("PxSpark", 5, 50, Random(21)-10, Random(21)-10, 40, 50, RGBa(255,0,0,0), RGBa(255,128,0,128));
  return(1);
}

private StepOff:
  step += 51;
  if (step >= 255)
    return(RemoveObject());
  SetClrModulation(RGBa(255,255,255,step));
  return(1);

