#strict

local iAng;

Initialize:
  SetLocal(0,FindObject(0,-20,-20,40,40,OCF_CrewMember()));
  SetAction("Attach",Local(0));
  return(1);

func UseOn(pClonk)
{
	Local(0)=pClonk;
	SetAction("Attach",Local(0));
	return(0);
}

Check:
  SetXDir(GetWind()/10+Sin(iAng*3,5),Local(0));
  SetYDir(10,Local(0));
  if(GetProcedure(Local(0))ne"FLIGHT") return(ComingDown());
  iAng++;
  return(1);

ComingDown:
  SetAction("Down");
  return(1);

Remove:
  RemoveObject();
  return(1);

Hit:
  SetAction("Down");
  return(1);