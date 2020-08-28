/*-- Blut --*/

#strict

local alpha;

protected func Initialize()
{
	SetClrModulation(RGB(200,0,0));
	FadeMeOut();
	return(1);
}

func ContactBottom()
{
	if(ObjectCount(BLUT)>1000) RemoveObject();
	SetGraphics("2");
}

/* Langsam verschwinden */
protected func FadeMeOut()
{
	SetObjAlpha(alpha++);
  
	if(alpha==200) return(RemoveObject());
	return(1);
}