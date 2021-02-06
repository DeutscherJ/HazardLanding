/*-- globale Funktionen --*/

#strict
static list;

/*Vergleicht das Objekt mit dem angegebenen*/
global func IsObject(i)
{
	return(ObjectNumber(i)==ObjectNumber(this()));
}

/*Gibt zurück, ob an dem angegebenen Punkt ein Tunnel ist*/
global func GBackTunnel(int xOffset, int yOffset)
{
  return(FindObject2(Find_AtPoint(xOffset,yOffset),Find_Func("CastlePartRange"))||(GetMaterial(xOffset,yOffset)!=-1&&!GBackSemiSolid(xOffset,yOffset)));
}

/*Minimiert wert auf -1 und +1*/
global func PosNeg(int i)
{
	if(i>0) return(1);
	if(i<0) return(-1);
	return(0);
}

/*findet feste Bereiche wie z.B. Decken*/
global func FindSolidTop(pObj)
{
  if(!pObj) pObj=this();
  for(var y=-5; !GBackSolid(0,y); y--)
  {
   if(1>GetY(pObj)+y) break;
  }
  return(y);//höchsten Punkt zurückgeben
}

/*ID des Objektes, welche Als ACtion Target verwendet wird vergleichen*/
global func HasActionTargetID(i)
{
	if(!GetActionTarget())return(0);
	return(GetID(GetActionTarget())==i);
}

/*Standposition*/
global func StandPosition(iX,iY,pClonk)
{
	if(Contained(pClonk)) Exit(pClonk);
	pClonk->SetAction("Walk");
	SetPhase(Random(7),pClonk);
	SetPosition(iX,iY,pClonk);
	return(pClonk);
}

/*Zufallsname*/
global func RandomName()
{
	var i= Random(19);
	if(i == 18) return("Florian");
	if(i == 17) return("Maximilian");
	if(i == 16) return("Oskar");
	if(i == 15) return("Fabian");
	if(i == 14) return("Torben");
	if(i == 13) return("Tobias");
	if(i == 12) return("Philip");
	if(i == 11) return("Manuel");
	if(i == 10) return("Dominik");
	if(i ==  9) return("Heinz");
	if(i ==  8) return("Lukas");
	if(i ==  7) return("Thomas");
	if(i ==  6) return("Nico");
	if(i ==  5) return("Timon");
	if(i ==  4) return("Christian");
	if(i ==  3) return("Sebastian");
	if(i ==  2) return("Helmut");
	if(i ==  1) return("Sven");
	if(i ==  0) return("Tim");
}