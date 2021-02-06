/*-- Neues Szenario --*/

#strict
static aTeamFirstPlayer;

func Initialize() {
  AddEffect("Water",0,32,1);
  SetSkyParallax(0,16,12);
  aTeamFirstPlayer = CreateArray(30);
  return(1);
}

global func FxWaterTimer(pObj,iNum,iA)
{
  iA*=2;
  SetGamma(
    RGB(0,   0,   SinX(iA,20,100)),
    RGB(100, 100, CosX(iA,140,160)),
    RGB(200, 200, CosX(iA,220,255))
  );
}
 
global func SinX(iA,iMin,iMax) { return(Sin(iA,(iMax-iMin)/2)+(iMax+iMin)/2); }
global func CosX(iA,iMin,iMax) { return(Cos(iA,(iMax-iMin)/2)+(iMax+iMin)/2); }

protected func InitializePlayer(int iPlr, int iX, int iY, object pBase, int iTeam)
{
	SetFoW(1,iPlr);
	if(!aTeamFirstPlayer[iTeam])
	{
		var pos = RandomPosition();
		SetPlayer(iPlr,pos[0],pos[1]);
		aTeamFirstPlayer[iTeam]=[GetX(GetCrew(iPlr)),GetY(GetCrew(iPlr))];
	}
	else
	{
		var pos = aTeamFirstPlayer[iTeam];
		SetPlayer(iPlr,pos[0],pos[1]);
	}
	return(1);
}

private func SetPlayer(num, px, py)
{
  var obj;
  while (obj = FindObjectOwner(0,num, 0,0,0,0,0,0,0, obj))
	  if(!(GetCategory(obj)& C4D_Parallax || GetCategory(obj)&C4D_MouseIgnore || GetCategory(obj)&C4D_IgnoreFoW))
		SetPosition(px+Random(25)-12, py-GetObjHeight(obj)/2, obj);
  return(1);
}

public func LatePlayerInit(iPlr)
{
  var pClonk = GetCrew(iPlr);
  var sub = CreateObject(SUB1,GetX(pClonk),GetY(pClonk),iPlr);
  for(var pClonk in FindObjects (Find_ID(HZCK),Find_Owner(iPlr)))
  {
	Enter(sub,pClonk);
	sub-> ActivateEntrance(pClonk);
	pClonk->~LaterInit();
  }
  return(1);
}

func ExamplePos()
{
	var pos = RandomPosition();
	var sub= CreateObject(SUB1,pos[0],pos[1]);
	SetPlrView (0,sub); 
	return(1);
}

func RandomPosition()
{
	var searchPos = 1, x, y, itNum=0;
	while(searchPos && itNum<1000)
	{
		searchPos=0;
		itNum ++;
		x = RandomX(160,LandscapeWidth()-160);
		y = RandomX(160,LandscapeHeight()-160);
		if(GetMaterial(x,y)!=Material("Water")){ searchPos=1; continue;}
		for(var l=10; l<=50; l+=10)
		{
			if(searchPos) continue;
			for(var r= 0; r<360; r+=2)
			{
				if(searchPos) continue;
				if(GetMaterial(x+Sin(r,l),y+Cos(r,l/2))!=Material("Water")) searchPos=1;
			}
		}
	}
	//Log("%d",itNum);
	return([x,y]);
}