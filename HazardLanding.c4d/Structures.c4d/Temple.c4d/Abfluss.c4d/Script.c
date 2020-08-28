/*Abflussrohr*/

#strict

local szGraph, fEmmit;

func Initialize()
{
  SetAction("Vent");
  return(1);
}

func Gitter()
{
	ScheduleCall(this(),"UpdateGraphics",1,1);
	if(!szGraph)			return(szGraph="2");
	if(szGraph eq "2")		return(szGraph=0);
	if(szGraph eq "Kack")	return(szGraph="2Kack");
	if(szGraph eq "2Kack")	return(szGraph="Kack");
	return(1);
}

func Kack()
{
	ScheduleCall(this(),"UpdateGraphics",1,1);
	if(!szGraph)			return(szGraph="Kack");
	if(szGraph eq "Kack")	return(szGraph=0);
	if(szGraph eq "2")		return(szGraph="2Kack");
	if(szGraph eq "2Kack") 	return(szGraph="2");
	return(1);
}

func UpdateGraphics()
{
	SetGraphics(szGraph);
}

func MakeEmmitter()
{
	fEmmit=true;
	return(1);
}

func Emmit()
{
	if(fEmmit) CastPXS("Kack",20,0,0,23);
	return(1);
}