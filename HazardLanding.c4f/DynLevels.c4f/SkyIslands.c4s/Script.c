/* Himmelsinseln */

#strict

static aTeamFirstPlayer;
/* Initialisierung */

protected func Initialize()
{
  SetSkyParallax(1);
  SetGamma(RGB(10,9,10), RGB(161,157,159), RGB(255,254,255) );
  aTeamFirstPlayer = CreateArray(30);
}


protected func InitializePlayer(int iPlr, int iX, int iY, object pBase, int iTeam)
{
	if(!aTeamFirstPlayer[iTeam])
		aTeamFirstPlayer[iTeam]=[GetX(GetCrew(iPlr)),GetY(GetCrew(iPlr))];
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
  for(var pClonk in FindObjects (Find_ID(HZCK),Find_Owner(iPlr)))
  {
	var bike= CreateObject(AB5B,GetX(pClonk),GetY(pClonk),iPlr);
	Enter(bike,pClonk);
	bike-> ActivateEntrance(pClonk);
	SetComDir(COMD_Stop,bike);
	Local(5,pClonk) = bike;
	pClonk->~LaterInit();
  }
  return(1);
}

func RandomPosition()
{
	var badPos = 1, x, y;
	while(badPos)
	{
		x = RandomX(40,LandscapeWidth()-40);
		y = RandomX(40,LandscapeHeight()-40);
		if(GBackSemiSolid(x,y)) continue;
		for(var l=10; l<=50; l+=10)
		{
			for(var r= 0; r<360; r+=20)
			{
				if(GBackSemiSolid (x+Sin(r,10),y+Cos(r,10))) continue;
			}
		}
		if(FindObject2(Find_Distance(30,x,y),Find_OCF(OCF_Alive)))
			continue;
		badPos = 0;
	}
	return([x,y]);
}