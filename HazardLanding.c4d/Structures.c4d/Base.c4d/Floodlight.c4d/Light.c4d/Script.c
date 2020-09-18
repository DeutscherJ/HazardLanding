/*-- Scheinwerfer --*/

#strict
#include FLHH

local turn, pSightArray;

func Entrance()
{
	Turning();
	return(1);
}

func Initialize(a,b,c)
{	
	pSightArray = []; 
	for(var i=0; i<9;i++)
	{
		var pSight = CreateObject(PMG4,0,0,-1);
		pSightArray[i] = pSight;
		var val = 15*i;
		CreateSight(pSight,val,val*3/2);
	}
	return(_inherited(a,b,c));
}

protected func Turning()
{
	if(EMPShocked()||!bOn)
	{
		for(var pSight in pSightArray)
		{
			SetPosition(GetX(),GetY(),pSight);
		}
		return;
	}
	var anglediff = Normalize(GetR()-GetR(GetActionTarget()),-180);

	if(turn == -1 && anglediff < -90 || turn == +1 && anglediff > 90)
		return(SetAction("Attach",GetActionTarget()));

	SetR(GetR()+turn);
	
	var dis = 30;
	for(var pSight in pSightArray)
	{
		if(Contained()) SetPosition(GetX(),GetY(),pSight);
		else SetPosition(GetX()+Sin(GetR()+turn,dis),GetY()-Cos(GetR()+turn,dis),pSight);
		dis+=50;
	}
		
	RotateLight();
}