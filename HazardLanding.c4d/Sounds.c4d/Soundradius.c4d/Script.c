/*-- Neues Objekt --*/

#strict

local pHelper;

func Initialize()
{
	SetVisibility(VIS_God());
	SetColorDw(RGBa(255,255,255,200));
	return(1);
}

global func SoundRadius(iRadius,pObj)
{
	return(ShowSoundRadius(iRadius,pObj));
}

global func ShowSoundRadius(iRadius,pObj)
{
	var circle = CreateObject(SRG4);
	circle->~Set(iRadius,pObj);
	return(circle);
}

global func ShowAllSoundRadii(pObj)
{
	if(!pObj)
		pObj=this();
	var i=0;
	for(var soundType in [1,2,4,8,16,32,64,128])
	{
		var iRadius = DefaultSoundRange(soundType);
		var pCircle = ShowSoundRadius(iRadius,pObj);
		SetClrModulation(HSL(255*i/7,255,128),pCircle);
		
		//Außerdem den Soundtyp anzeigen
		var yDir = -1;//Mod(i,2)*2-1;
		var messageHelper = pCircle->CreateObject(ROCK,0,iRadius*yDir-yDir*23);
		Message("@%s",messageHelper,SoundTypeName(soundType));
		LocalN("pHelper",pCircle)=messageHelper;
		
		i++;
	}
	return(1);
}

func Set(iRadius,pObj)
{
	SetCon(iRadius);
	if(!pObj)
		pObj=this();
	if(pObj)
		SetPosition(GetX(pObj),GetY(pObj));
	return(1);
}

func Remove()
{
	RemoveObject();
	if(pHelper) RemoveObject(pHelper);
	return(1);
}