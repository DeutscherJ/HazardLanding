/* Bergland */

#strict
static aTeamFirstPlayer;

func Initialize() 
{
  SetSkyParallax(0,14,14, 0,0,SkyPar_Keep(),SkyPar_Keep());
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