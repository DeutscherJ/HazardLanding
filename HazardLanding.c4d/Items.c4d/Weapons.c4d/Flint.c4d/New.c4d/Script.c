/*-- Neues Objekt --*/

#strict

local iterations;

func Timer()
{
	SetSpeed(Sin(GetR(),20),-Cos(GetR(),20));
	return(1);
}

func Hit()
{
	if(GetMaterial(Sin(GetR(),4),-Cos(GetR(),4))!=Material("Gold") && GetMaterial(Sin(GetR(),4),-Cos(GetR(),4))!=Material("Ore") && GetMaterial(Sin(GetR(),4),-Cos(GetR(),4))!=Material("Rock")) return(RemoveObject()); 
	if(iterations>0)
	{
		CreateNanite(GetR()+10,iterations-1);
		//CreateNanite(GetR()  ,iterations-1);
		CreateNanite(GetR()-10,iterations-1);
	}
	Explode(7);
	return(1);
}

global func CreateNanite(r,it)
{
	var pObj = CreateObject(NAG4,0,0,GetOwner());
	SetR(r,pObj);
	LocalN("iterations",pObj)=it;
	pObj->~Timer();
	return(1);
}

func End()
{
	return(RemoveObject());
}