/*-- Hatch --*/

#strict
#include DOOR

local pBeam, fU, fLocked;

func Collection2()
{
	if(fU) return(0);
	pBeam-> UnUseable();
	while(Contents())
	{
		SetCommand(Contents(),"Exit");
		Enter(pBeam,Contents());
		if(LocalN("fLocked",pBeam)) pBeam-> Unlock();
	}
	ScheduleCall(pBeam,"Useable",5);
	return(1);
}

func UnUseable(){fU=true;}
func Useable(){fU=false;}

func ActivateEntrance(pObj)
{
	if(fLocked)
	{
		Message("$MsgLocked$",this());
		Sound("Click");
		SetCommand(pObj,"None");
		return(1);
	}
	return(_inherited(pObj));
}

func Unlock()
{
	fLocked=false;
	LocalN("fLocked",pBeam)=false;
	Sound("Click");
}

private func DoorClosed(a,b)
{
  Sound("Discharge");
  return(_inherited(a,b));
}