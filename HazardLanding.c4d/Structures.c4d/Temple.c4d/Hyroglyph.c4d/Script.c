/*-- Hyroglyph --*/

#strict
local active;


func Initialize() {
  SetAction("Random");
  SetPhase(13);
  SetDir(Random(3));
  SetColorDw(RGB(100,242,239));
  return(1);
}

func Activate()
{
	active = true;
	SetVisibility(VIS_All);
	return(1);
}

func Timer()
{
	var iX,iY,iF=1, pL;
	if(IsPoint())
	{
		iX=-7;
		iY=-8;
		iF=2;
	}
	if(pL=FindObject2(Find_Distance(58*iF,iX,iY),Find_ID(LGHT),Find_Func("HasObject",SPHX)))
	{
		//if(ObjectDistance(this(),pL)<30 && !Random(25)) CreateParticle("NoGravSpark",0,0,0,0,20);
		SetVisibility(VIS_All);
		if(IsPoint()) SetClrModulation(RGBa(255,255,255,ObjectDistance(this(),pL)*2));
	}
	else
		if(!active) SetVisibility(VIS_None);
}

func CreateLine(iLength,iDir)
{
	SetPhase(0);
	SetDir(iDir);
	for(var i; i<iLength; i++)
	{
		var pHyro= CreateObject(GetID(),i*18+18,0,-1);
		SetPhase(i,pHyro);
		SetDir(iDir);
	}
}

func MakePoint(iX,iY)
{
	var pHyro= CreateObject(GetID(),iX,iY,-1);
	pHyro->SetAction("Point");
	SetDir(0,pHyro);
}

func Draw(iR,iL)
{
	for(var i; i<iL; i+=2)
	{
		MakePoint(Sin(iR,i),-Cos(iR,i));
	}
	return(1);
}

func IsPoint(){return(GetAction()eq"Point");}