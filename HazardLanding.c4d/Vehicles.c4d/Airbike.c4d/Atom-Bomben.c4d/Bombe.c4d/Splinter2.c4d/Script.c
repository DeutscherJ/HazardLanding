/*-- Splitter --*/

#strict

local iTime, iDir;

func Initialize()
{
  iTime=50;
  return(1);
}

func Timer()
{
  iTime-=5;
  if(!iTime) RemoveObject();
  AtomExplode(Sin(iTime,50),CreateObject(ROCK,0,0,GetOwner()));
  SetSpeed((iDir*20)*10,-2);
  return(1);
}

func Left()
{
  iDir=-1;
  return();
}

func Right()
{
  iDir=1;
  return();
}