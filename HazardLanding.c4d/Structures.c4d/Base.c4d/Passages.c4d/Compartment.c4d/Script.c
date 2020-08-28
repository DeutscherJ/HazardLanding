#strict

ActivateEntrance: 
  if (Not(ActIdle())) return(1);
  SetAction("OpenDoor");
  return(1);

EntranceOpen:
  SetEntrance(1);
  return(1);
EntranceClose:
  SetEntrance(0);
  return(1); 
  
func SoundOpen()
{
  Sound("Airlock1");
  return(1);
}

func SoundClose()
{
  Sound("Airlock2");
  return(1);  
}

public func Damage()
{
	if(GetDamage()>50 && GetAction()ne"DoorDestroyed")
	{
		CastObjects(_DF1,4,35);
		SetAction("DoorDestroyed");
		return(0);
	}
}