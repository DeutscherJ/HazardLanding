/*-- Ast timer --*/

#strict

local harden, hard;

func Initialize()
{
  SetAction("Exist");
  SetPhase(Random(3));
  return(1);
}

func Timer()
{
	if(!harden) return(0);
	if(FindObject2(Find_InRect(-85,-25,190,12),Find_OCF(OCF_Alive)))
	{
		hard=true;
		SetSolidMask(0,20*GetPhase(),150,20);
	}
	if(hard&& !FindObject2(Find_InRect(-85,-25,190,30),Find_OCF(OCF_Alive)))
	{
		hard=false;
		SetSolidMask();
	}
}