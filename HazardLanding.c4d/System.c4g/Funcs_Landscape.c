/*-- Neues Script --*/

#strict

/*Material Kreis oder Ring*/
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

global func MatArea(string szMat, iX, iY, iWidth, iHeight)
{
  return(DrawMaterialQuad (szMat,iX,iY,iX+iWidth,iY,iX+iWidth,iY+iHeight,iX,iY+iHeight,1)); 
}

//Window(GetX(),GetY(),20,50)
global func Window(iX,iY,x,y)
{
	MatCircle("Tunnel-Sky",iX,iY,x,1,-90,90,4);
	MatArea("Tunnel-Sky", iX-x, iY, x*2, y);
	return(1);
}

global func SideString(i)
{
	if(i==COMD_Up) return("Up");
	if(i==COMD_Down) return("Down");
	if(i==COMD_Right) return("Right");
	if(i==COMD_Left) return("Left");
}

global func SideInt(i)
{
	if(i==COMD_Right) return(1);
	if(i==COMD_Left) return(-1);
}

/*--Verfügbare horizontale Länge in festem Material--*/
global func MeasureSolidX(iX,iY,dir)
{
	if(!dir) dir=1;
	var x = iX;
	var y = iY;
	var i = 0;
	while(GetMaterial(AbsX(x*10-5),AbsY(y*10-5))==Material("Brick"))
	{
		x+=dir;
		i++;
	}
	return(i);
}

/*--Verfügbare vertikale Länge in festem Material--*/
global func MeasureSolidY(iX,iY,dir)
{
	if(!dir) dir=1;
	var x = iX;
	var y = iY;
	var i = 0;
	while(GetMaterial(AbsX(x*10-5),AbsY(y*10-5))==Material("Brick"))
	{
		y+=dir;
		i++;
	}
	return(i);
}

/*In einen bestimmten Winkel von Punkt iX iY gehen bis festes Material gefunden wurde. Die Position von diesem Zurückliefern*/
global func FindSolidInAngle(iX,iY,iAng,i)
{
	var x = iX, y = iY;
	while(!GBackSolid(AbsX(x),AbsY(y)))
	{
		x += Sin(iAng,10);
		y -= Cos(iAng,10);
		if(x<0 || x>LandscapeWidth() || y<0 || y>LandscapeHeight() || !PathFree(iX,iY,x,y)) break;
	}
	if(i==1) return(x);
	if(i==2) return(y);
	return([x,y]);
}

/*- Karte Malen -*/
global func DrawMapRect(iX,iY,iXSize,iYSize,szMapDef)
{
	if(!iXSize) iXSize=10;
	if(!iYSize) iYSize=10;
	DrawDefMap(iX,iY,iXSize,iYSize,szMapDef);
	return(1);
}
//Draw10MapRect(0,0,200,10,"Caves")
global func Draw10MapRect(iX,iY,iXSize,iYSize,szMapDef)
{
	iX*=10;
	iY*=10;
	iXSize*=10;
	iYSize*=10;
	DrawMapRect(iX,iY, iXSize,iYSize,szMapDef);
	return(1);
}

/*- Material Malen -*/
global func DrawRect(szMat,iX,iY,iXSize,iYSize)
{
	if(!iXSize) iXSize=10;
	if(!iYSize) iYSize=10;
	DrawMaterialQuad(szMat,iX,iY, iX+iXSize,iY, iX+iXSize,iY+iYSize,iX,iY+iYSize,1);
	return(1);
}

global func Draw10Rect(szMat,iX,iY,iXSize,iYSize)
{
	iX*=10;
	iY*=10;
	iXSize*=10;
	iYSize*=10;
	DrawRect(szMat,iX,iY, iXSize,iYSize);
	return(1);
}

/*Diese Funktion malt Landschaftsrechtecke aber nur in "hartes" Material
dadurch soll verhindert werden, dass Beispielsweise in den Himmel gemalt wird oder andere Tunnel überschrieben werden
wird ein anderer Tunnel gefunden wird am Ende nicht 1 sondern 0 ausgegeben

*/
global func Draw10RectSolid(szMat,X,Y,iXSize,iYSize,boolMustTunnel)
{
	X=Min(X,X+iXSize);
	X*=10;
	Y=Min(Y,Y+iYSize);
	Y*=10;
	iXSize=10*Abs(iXSize);
	iYSize=10*Abs(iYSize);
	var output = 1;
	/*Ist irgendwo da ein Teil frei?*/
	if(boolMustTunnel)
	{
		for(var iX=X; iX<X+iXSize; iX+=10)
		{
			for(var iY=Y; iY<Y+iYSize; iY+=10)
			{
				//GBackSolid
				if(GetMaterial(AbsX(iX+5),AbsY(iY+5))!=Material("Brick")) return(0);//Wenn ein Teil frei ist gebe eine 0 aus
			}
		}
	}
	/*Wenn nicht ist die Bauerlaubnis hiermit erteilt*/
	for(var iX=X; iX<X+iXSize; iX+=10)
	{
		for(var iY=Y; iY<Y+iYSize; iY+=10)
		{
			if(GBackSolid (AbsX(iX+5),AbsY(iY+5))) DrawRect(szMat,iX,iY,10,10);
			else output = 0;
		}
	}
	return(output);
}

//Spinnenweben
global func RandomWeb(x,y)
{
	var pos = FindSolidInAngle(x,y,RandomX(-80,80));
	return(ObjOnHard(SWEB,AbsX(pos[0]+10),AbsY(pos[1]),-1,Random(5),2));
}

//Objekt so verschieben das es auf harter Oberfläche liegt
global func PlaceHard(pObj,dir,ySpac)
{
	if(!pObj) pObj=this();
	if(!dir) dir=1;
	while(GetY(pObj)>0 && GetY(pObj)<LandscapeHeight() && (GetVertexNum(pObj)&&!Stuck(pObj)) || (!GetVertexNum(pObj) && !GBackSolid(AbsX(GetX(pObj)),AbsY(GetY(pObj))-GetDefCoreVal("Offset","Defcore",GetID(pObj),2))))
	{
		SetPosition(GetX(pObj),GetY(pObj)+1*dir,pObj);
	}
	if(dir!=-1) SetPosition(GetX(pObj),GetY(pObj)-1*dir,pObj);
	if(!ySpac) ySpac = pObj->~FloorDis();
	SetPosition(GetX(pObj),GetY(pObj)+ySpac,pObj);
	
	if(pObj->~HardPlace(dir,ySpac)) return(pObj);
	return(pObj);
}

/*Erzeuge Objekt und plaziere es auf oder unter einer festen Oberfläche am Ende
um +dirBeg versetzen
dir = 1 auf oberfläche plazieren
dir = -1 unter Oberfläche plazieren
*/
global func ObjOnHard(objID,iX,iY,dir,ySpac,dirBeg)
{
	var pObj = CreateObject(objID,iX,iY,-1);
	var i = 1;
	while(Stuck(pObj) && GetY(pObj)>5 && i<10000)
	{
		i++;
		SetPosition(GetX(pObj),GetY(pObj)-1+dirBeg,pObj);
	}
	PlaceHard(pObj,dir,ySpac);
	return(pObj);
}