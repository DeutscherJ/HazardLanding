/*-- Neues Objekt --*/

#strict
//AddFireLight(400,RGB(255,200,200),10)
	//AddFireLight(200,RGBa(255,180,150,50),this(),10)
local iZitterFaktor, iCon,pLight;

global func AddFireLight(iSize,iColor,pObj,iZitterFaktor)
{
	var pLight = AddLight(iSize,iColor,pObj);
	var pFireLight = CreateObject(FRLT,0,0,GetOwner(pLight));
	LocalN("iCon",pFireLight)			=	iSize;
	if(iZitterFaktor==0)
		iZitterFaktor=10;
	LocalN("iZitterFaktor",pFireLight)	=	iZitterFaktor;
	LocalN("pLight",pFireLight)			=	pLight;
	
	return(pFireLight);
}

func Timer()
{
	if(!pLight) return(RemoveObject());
	pLight->~ChangeSize(iCon+RandomX(-iZitterFaktor,iZitterFaktor));
	return(1);
}