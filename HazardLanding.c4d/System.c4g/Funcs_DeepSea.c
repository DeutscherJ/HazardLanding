/*-- Funktionen --*/

#strict

static const iDH=32;//Türhöhe
static const iFH=50;//Flurhöhe
static const iWS=20;//Wallstärke
static const Wall="Granite-Rough";
static const BWall="Tunnel-Smooth";

global func MatArea(string szMat,int iX,int iY,int iWidth,int iHeight, object pObj)
{
	if(!pObj) pObj=this();
	iX+= GetX(pObj);
	iY+= GetY(pObj);
  return(DrawMaterialQuad (szMat,iX,iY,iX+iWidth,iY,iX+iWidth,iY+iHeight,iX,iY+iHeight,1)); 
}

global func XSMatArea(string szMat,int iX,int iY,int iHeight, object pObj)
{
	if(!pObj) pObj=this();
	return(MatArea(szMat,iX,iY,-iX*2,iHeight,pObj)); 
}

global func XSyncMatAreas(string szMat,int iX,int iY,int iWidth,int iHeight, object pObj)
{
	if(!pObj) pObj=this();
	MatArea(szMat,iX,iY,iWidth,iHeight,pObj);
	return(MatArea(szMat,-iX,iY,-iWidth,iHeight,pObj)); 
}

global func MatCircle(string szMat, iX, iY, iORadius, iIRadius, iAAngle, iOAngle, iCorners)
{
	if(!iOAngle) iOAngle=360;
	if(!iCorners) iCorners= Distance(0,iOAngle,0,iAAngle);
	var iPlus=Distance(0,iOAngle,0,iAAngle)/iCorners;
	for(var iNum=iCorners;iNum;iNum--)
	{
		DrawMaterialQuad (szMat,iX+Sin(iAAngle,iORadius),iY-Cos(iAAngle,iORadius),iX+Sin(iAAngle+iPlus,iORadius),iY-Cos(iAAngle+iPlus,iORadius),iX+Sin(iAAngle+iPlus,iIRadius),iY-Cos(iAAngle+iPlus,iIRadius),iX+Sin(iAAngle,iIRadius),iY-Cos(iAAngle,iIRadius),1);
		iAAngle+=iPlus;
	}
	return(1);
}

global func ShortObject(pObj,iTime)
{
	Schedule(Format("RemoveObject(Object(%d))",ObjectNumber(pObj)),iTime,1,pObj);
	return(pObj);
}
//MatCircle("Gold-Smooth",GetX(),GetY(),200,150,90,180)
//	DrawMaterialQuad ("Gold-Smooth",GetX()+Sin(0,100),GetY()-Cos(0,100),GetX()+Sin(45,100),GetY()-Cos(45,100),GetX()+Sin(45,60),GetY()-Cos(45,60),GetX()+Sin(0,60),GetY()-Cos(0,60))