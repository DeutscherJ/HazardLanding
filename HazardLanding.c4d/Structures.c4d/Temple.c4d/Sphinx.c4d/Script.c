/*-- Sphinx --*/

#strict

local pLight;

func Initialize() {
   
  return(1);
}

func Timer()
{
	if(pLight)
	{
		CreateParticle("PSpark",GetVertex(0),GetVertex(0,1),RandomX(-2,2),-5,50,RGB(255,128,60));
	}
	if(Abs(GetXDir())>10)
	{
		CreateParticle("Smoke",29*-PlusMinus(GetXDir()),25,0,0,Random(60),RGB(177,156,59));
		Sound("Pull",0,0,0,0,1);
	}
	if(Abs(GetXDir())<10){Sound("Pull",0,0,0,0,-1);}
	return(1);
}

func ControlDigDouble(pClonk)
{
	if(!pLight)
	{
		pLight=AddFireLight(180,RGB(255,128,60),this());
		SetPlrViewRange(20);
		Sound("Inflame");
		return(1);
	}
	RemoveObject(pLight);
	SetPlrViewRange(0);
	Sound("Pshshsh");
	return(1);
}

func LightsOn(){return(pLight);}