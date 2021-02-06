/*-- Szenarienscript Wildwest --*/

#strict

static playerplace;


/* Inialisierung */

protected func Initialize()
{
  playerplace = 0;
  // Parallaxität des Himmels: 25%
  SetSkyParallax(0, 40,40, 0,0, SkyPar_Keep(),SkyPar_Keep());
  for(var x = 0; x<=3600; x+=900)
  {
	  CreateObject(_BGL,x,1450,-1);
  }
  return(1);
}
func OpenScenario(){return(1);}

protected func InitializePlayer(int iPlr, int iX, int iY, object pBase, int iTeam)
{
  SetPlayer(iPlr,PlaceX(iTeam-1), PlaceY(iTeam-1));
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

func ShowPos()
{
	CreateObject(LORY,AbsX(PlaceX(Global(30))),AbsY(PlaceY(Global(30))));
	if(!Global(30))
		Global(30)=1;
	else
		Global(30)++;
}

private Places: return(2);

private PlaceX:
  if (Par(0)==0) return(600);
  if (Par(0)==1) return(2400);
  return(0);

private PlaceY:
  if (Par(0)==0) return(460);
  if (Par(0)==1) return(460);
  return(0);

