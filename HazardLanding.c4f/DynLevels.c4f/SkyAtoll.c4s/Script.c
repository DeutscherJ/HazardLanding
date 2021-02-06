#strict
static aTeamFirstPlayer;

func Initialize() {

  SetSkyParallax (0,17,19,0,0,0,0); 
  SetGamma(RGB(15,15,15),RGB(118,118,118),RGB(215,215,215));

  //Nebel
  for(var i=0;i<180;++i) 
    CreateParticle("Fog",Random(LandscapeWidth()),Random(LandscapeHeight()),0,0,RandomX(900,1700));
  aTeamFirstPlayer = CreateArray(30);
}

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
  for(var pClonk in FindObjects (Find_ID(HZCK),Find_Owner(iPlr)))
  {
	var bike= CreateObject(AB5B,GetX(pClonk),GetY(pClonk),iPlr);
	Enter(bike,pClonk);
	bike-> ActivateEntrance(pClonk);
	SetComDir(COMD_Stop,bike);
	Local(5,pClonk)=bike;
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
/*
func InitializePlayer(iPlr) {
  var pClnk;

  for(var pClnk;pClnk=FindObjectOwner(0,iPlr,0,0,0,0,OCF_CrewMember(),0,0,pClnk);)
    pClnk->Initialize();

  //Clonks werden unten rechts am Bildschirmrand erzeugt
  while(pClnk=FindObjectOwner(0,iPlr,0,0,0,0,OCF_CrewMember(),0,0,pClnk))
	SetPosition(LandscapeWidth()-55,LandscapeHeight()-112,pClnk);

  //Jeder Spieler bekommt eine Flagge und einen Bausatz wenn das Ritterpack nicht aktiviert ist
  //ansonsten kriegt er statt dem Bausatz ein Zeltpack und Baupläne für Waffen und Burg
  CreateContents(FLAG,GetCrew(iPlr,0));
  if(!CreateContents(TENP,GetCrew(iPlr,1)))
    CreateContents(CNKT,GetCrew(iPlr,1));
  if(GetCrew(iPlr,2)) {
    CreateContents(CPPL,GetCrew(iPlr,2));
    CreateContents(WPPL,GetCrew(iPlr,2));
  }

  //...außerdem ein Luftschiff
  if(!FindObject(BLMP,LandscapeWidth()-80,LandscapeHeight()-130,60,60))
    CreateObject(BLMP,LandscapeWidth()-50,LandscapeHeight()-100,-1);
}