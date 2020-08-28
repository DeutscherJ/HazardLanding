#strict 2

local pFire;

func Initialize()
{
	if(!pFire) pFire=AddFireLight(400,RGBa(255,180,150,50),this(),10);
	CreateSight(this(),50,100);
//	burnSize = 2000;
}

private func Timer()
{
	if(pFire)
	{
		var size = 100;

		var dirrand = RandomX(-size/15,size/15);
		var xdir = +Sin(GetR()+dirrand,size/4);
		var ydir = -Cos(GetR()+dirrand,size/4);
		CreateParticle("Thrust",GetVertex (0,0),GetVertex (0,1),xdir,ydir,RandomX(size*4/5,size),RGBa(255,200,200,60),0,0);
		if(!Random(5))
		{
			Smoke(GetVertex (0,0),GetVertex (0,1),20);
		}
	}
}

func ControlDigDouble()
{
	if(pFire)
	{
		RemoveObject(pFire);
		Sound("Pshshsh");
	}
	else
	{
		Split2Components();
	}
	return(1);
}