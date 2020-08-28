/*-- Scherbe --*/

#strict

local alpha;

/* Langsam verschwinden */
protected func FadeMeOut()
{
	SetClrModulation(RGBa(200,200,200,alpha++));
  
	if(alpha==200) return(RemoveObject());
	return(1);
}