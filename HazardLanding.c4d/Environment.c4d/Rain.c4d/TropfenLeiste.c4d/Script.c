/*-- Regenleiste --*/

#strict

local width, rnd; 

func Initialize()
{
	rnd = 30;
	SetVisibility(VIS_God);
	SetClrModulation(RGBa(255,255,255,60));
	Sound("HeavyRain",0,this(),60,0,1);
	if(!width) width=10;
	return(1);
}

func Set(widthPixel)
{
  SetShape(-widthPixel/2,-5,widthPixel,10);
  SetObjDrawTransform(1000*widthPixel/10,0,0,0,1000);
  width = widthPixel;
  return(1);
}

func Droplets()
{
	for( var i = Random(width/5); i; i--)
	{
		if(!Random(rnd*2)) CreateObject(TPG4,RandomX(-width/2,width/2),5,-1);
	}
	return(1);
}
func IsRain(){return(1);}