#strict

protected ActivateEntrance: 
  if (Not(ActIdle())) return(1);
  SetAction("OpenDoor");
  return(1);

private EntranceOpen:
  SetEntrance(1);
  return(1);
private EntranceClose:
  SetEntrance(0);
  return(1); 
  
private SoundOpen:
  Sound("Airlock1");
  return(1);  
private SoundClose:
  Sound("Airlock2");
  return(1);  