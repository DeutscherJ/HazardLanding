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
  
protected Initialize:
  SetLocal(0,0); // Transfer-Zielobjekt
	SetLocal(1,1); // Status Eingang/Ausgang
	return(1);	
	
public SetTarget:
  SetLocal(0,Par(0));
  return(1);	 
  
private CheckContents:					
  if (Not(ActIdle())) return(0);
  if (Not(Contents())) return(PrepareForOutgoing());  
  if (And(Local(0),Local(1))) return(TransferToTarget());  
  SetCommand(Contents(0),"Exit");
  SetCommand(Contents(1),"Exit");
  SetCommand(Contents(2),"Exit");
  SetCommand(Contents(3),"Exit");
  SetCommand(Contents(4),"Exit");
  SetCommand(Contents(5),"Exit");
  SetCommand(Contents(6),"Exit");
  SetCommand(Contents(7),"Exit");  
  return(1);

private PrepareForOutgoing:
  SetLocal(1,1);
  return(1);
  
private TransferToTarget:
	SetLocal(1,0,Local(0));
	if (Contents()) Enter(Local(0),Contents());
	if (Contents()) Enter(Local(0),Contents());
	if (Contents()) Enter(Local(0),Contents());
	if (Contents()) Enter(Local(0),Contents());
	if (Contents()) Enter(Local(0),Contents());
	if (Contents()) Enter(Local(0),Contents());
	if (Contents()) Enter(Local(0),Contents());
	if (Contents()) Enter(Local(0),Contents());
  return(1);  