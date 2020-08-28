/*-- Tropfen --*/

#strict

static globalRainColor;

func Initialize() {
	SetAction("Rain");
	SetDir(Random(4));
	SetCon(RandomX(70,120));
	if(!globalRainColor)
		SetClrModulation(globalRainColor);
	return(1);
}

func Remove()
{
	RemoveObject();
	return(1);
}
func IsRain(){return(1);}