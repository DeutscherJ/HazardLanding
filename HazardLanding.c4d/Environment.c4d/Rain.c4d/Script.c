/*-- Regen--*/

#strict

func Initialize() {
  SetAction("Rain");
  SetPhase(Random(5));
  Local(0)=100;
  Local(1)=100;
  return(1);
}

global func RainColor(clr,clr2)
{
	globalRainColor = clr;
	if(!clr2) clr2 = clr;
	for(var pObj in FindObjects(Find_Func("IsRain")))
	{
		pObj->~Initialize();
		SetClrModulation(clr2,pObj);
	}
	return(1);
}

func IsRain(){return(1);}