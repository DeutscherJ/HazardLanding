/*-- Flammeneffekt --*/

#strict

local step;


/* Aufruf durch die Landekapsel */

public func Init(capsule)
{
  SetAction("Burn",capsule);
  // immer vor der Kapsel
  SetObjectOrder(capsule,this());
  return(1);
}

public SwitchOff:
  SetAction("SwitchOff");
  step = 0;
  return(1);

/* Action-Call */

private StepOff:
  step += 15;
  if (step >= 255)
    return(RemoveObject());
  SetClrModulation(RGBa(255,255,255,step));
  return(1);

/* TimerCall */

private Burning:
  // Objekte anbrennen
  var obj;
  while (obj = FindObject(0, -35,0,70,35, OCF_Inflammable(),0,0,NoContainer(),obj))
    if (!Random(10))
      Incinerate(obj);
  // Schnee/Eis schmelzen
  var i;
  for (i; i < 10; i++)
    MeltPixel(Random(70)-35);
  return(1);

private func MeltPixel(x)
{
  // oberstes Pixel suchen
  var y, mat;
  for (y = 0; y < 35; y++)
  {
    mat = GetMaterial(x,y);
    if ((mat == Material("Ice")) || (mat == Material("Snow")))
      break;
  }
  // Materialpixel schmelzen
  if ((mat != Material("Ice")) &&
      (mat != Material("Snow"))) return(1);
  DigFreeRect(GetX()+x, GetY()+y, 1,1);
  // Wasser rein
  InsertMaterial(Material("Water"), x,y);
  return(1);
}

