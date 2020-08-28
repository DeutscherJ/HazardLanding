/*-- Raum --*/

#strict

func Initialize()
{
	SetVisibility(VIS_God);
	SetClrModulation(RGBa(255,255,255,60));
	return(1);
}

func Set(iW,iH)
{
	SetObjDrawTransform(1000*iW/100,0,0,0,1000*iH/100);
	SetShape(-iW/2,-iH/2,iW,iH);
	return(1);
}