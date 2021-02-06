/*-- Szenarienscript Peerleos --*/

#strict

static playerplace;

protected func Initialize()
{
  playerplace = 0;
  // Parallaxität des Hintergrunds: 25%
  SetSkyParallax(0, 40,40, 0,0, SkyPar_Keep(),SkyPar_Keep());
  // Brücke
  var n = 0;
  for (n; n < 3; n++)
    CreateObject(_BGL, 1945+n*66, 200, -1);
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

private Places: return(3);

private PlaceX:
  if (Par(0)==0) return(400);//Unten Links
  if (Par(0)==1) return(3150);//Unten Rechts Höhle
  if (Par(0)==2) return(2000);//Mitte Gipfel
  return(0);

private PlaceY:
  if (Par(0)==0) return(1360);
  if (Par(0)==1) return(1340);
  if (Par(0)==2) return(450);
  return(0);
