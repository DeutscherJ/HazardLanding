/*-- Neues Objekt --*/

#strict
#include TNF1
func Set(i)
{
  if(i>=1)
	  SetGraphics(Format("%d",i));
	SetRDir(RandomX(-5,5));
	SetSpeed(-RandomX(-20,20),RandomX(-20,20));
  return(1);
}