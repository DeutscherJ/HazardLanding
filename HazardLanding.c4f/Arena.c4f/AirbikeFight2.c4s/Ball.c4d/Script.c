/*-- Ball --*/

#strict

protected func Departure()
{
  SetXDir(GetXDir()*2);
}

protected func Hit ()
{
  var x = GetXDir();
  if(x > 0) x = 1;
  if(x < 0) x = -1;
  if(!GBackSolid(x, 0) && !GBackSolid(x*2, 0) && !GBackSolid(x*3, 0)) SetXDir(2 * GetXDir() / 3);
   else SetXDir(-2 * GetXDir() / 3);
  if(!Inside(GetXDir(), -1, 1) && !GBackSolid(0, -3)) SetYDir(RandomX(-50, -15));
  SetRDir(GetRDir() / 2);
  Sound("bump");
}
