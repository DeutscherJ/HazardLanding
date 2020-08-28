/*-- Bubble --*/

#strict

global func Bubble(int iX, int iY)
{
  var bubble= CreateObject(FXU1,iX,iY,-1);
  return(bubble);
}

global func Smoke(int iX,int iY,int iLevel)
{
  if(GBackLiquid(iX,iY))
  {
   for(var iNum= iLevel; iNum; iNum--) Bubble(iX+Sin(Random(366),Random(iLevel)),iY-Cos(Random(366),Random(iLevel)));
   return(1);
  }
  return(inherited(iX,iY,iLevel));
}