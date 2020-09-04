/*-- Sicht --*/

#strict
local iMinSight, iMaxSight;

global func CreateSight(pObj,iMin,iMax)
{
	var pSightArray = [];
	for(var i=0; i<20; i++)
	{
		var sight = pObj->CreateObject(SGG4,0,0,i);
		sight->SetAction("Exist",pObj);
		SetPlrViewRange(iMax,sight);
		LocalN("iMinSight",sight) = iMin;
		LocalN("iMaxSight",sight) = iMax;
		pSightArray[i]=sight;
	}
	return(pSightArray);
}

func DaytimeControlled(iTime)
{
	SetPlrViewRange(iMinSight+iTime*(iMaxSight-iMinSight)/100);
	return(1);
}

func Timer()
{
	if(!GetActionTarget())
		RemoveObject();
	return(1);
}