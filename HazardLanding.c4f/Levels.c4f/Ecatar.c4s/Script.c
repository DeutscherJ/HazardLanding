/*-- Szenarienscript Ecatar --*/

#strict

static playerplace;


/* Inialisierung */

protected func Initialize()
{
  playerplace = 0;
  // Parallaxität des Himmels: 25%
  SetSkyParallax(0, 40,40, 0,0, SkyPar_Keep(),SkyPar_Keep());
  for(var x = 0; x<=3600; x+=700)
  {
	  CreateObject(_BGL,x,1350,-1);
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

private Places: return(6);

private PlaceX:
  if (Par(0)==0) return(400);//Links
  if (Par(0)==1) return(4720);//Rechts
  if (Par(0)==2) return(1992);//[1992, 1377]//Höhle 1
  if (Par(0)==3) return(4528);// [4528, 1507]//Höhle 2
  if (Par(0)==4) return(1139);//[1139, 2688]//Erdkern 1
  if (Par(0)==5) return(4553);//[4553, 2586]//Erdkern2
  return(0);

private PlaceY:
  if (Par(0)==0) return(865);
  if (Par(0)==1) return(820);
  if (Par(0)==2) return(1377);
  if (Par(0)==3) return(1507);
  if (Par(0)==4) return(2688);
  if (Par(0)==5) return(2586);
  return(0);

