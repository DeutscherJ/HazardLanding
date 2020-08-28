/*-- Splitter --*/

#strict

local iTime;

func Timer()
{
  iTime+=15;
  if(iTime==90) RemoveObject();
  AtomExplode(Cos(90-iTime,100),CreateObject(ROCK,0,0,GetOwner()));
  SetSpeed(0,(-30+iTime/5)*5);
  return(1);
}

func Hit()
{
  Explode(60);
  return(1);
}