/*-- Szenarienscript Gebirge --*/

#strict

static playerplace;


/* Initialisierung */

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
//Startpunkte 
private Places: return(4);

private PlaceX:
  if (Par(0)==0) return(2950);//Unten Rechts
  if (Par(0)==1) return(450);//Unten Links Höhle
  if (Par(0)==2) return(425);//Oben Links Schnee
  if (Par(0)==3) return(1850);//Mitte gefrorener See
  return(0);

private PlaceY:
  if (Par(0)==0) return(2120);
  if (Par(0)==1) return(2160);
  if (Par(0)==2) return(720);
  if (Par(0)==3) return(1230);
  return(0);

