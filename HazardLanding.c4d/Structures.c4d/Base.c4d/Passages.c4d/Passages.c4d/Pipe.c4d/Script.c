#strict


func IsPassage(){return(1);}
func Set(iDistance,factor)
{
	if(!factor)
		factor = 2;
	if(GBackSemiSolid())
	{
		var r = Min(255,GetMaterialVal("Color","Material",GetMaterial(),0)*factor);
		var g = Min(255,GetMaterialVal("Color","Material",GetMaterial(),1)*factor);
		var b = Min(255,GetMaterialVal("Color","Material",GetMaterial(),2)*factor);
		SetClrModulation(RGB(r,g,b));
	}		
	if(!iDistance)
		iDistance = 150;
	var target = FindObject2(Find_Func("IsPassage"),Find_Distance(iDistance));
	if(!target) return(Message("kein Ziel",this()));
	Local(0)=target;
	Local(0,target)=this();
	Message("Ziel",target);
	return(1);
}


Initialize:
  SetAction("Pipe");
  SetPhase(0);

  SetEntrance(1);
  SetLocal(0,0); // Internes Ziel
  SetLocal(1,1); // Status eingehender/ausgehender Clonk
  SetLocal(2,0); // Externe Ziel
  return(1);


SetTarget:
  SetLocal(0,Par(0));
  return(1);	 
  
SetExtTarget:  
  SetLocal(2,Par(0));
  return(1);	 
  
CheckContents:				
  // Eingehend/Ausgehend-Status zurücksetzen  
  if (Not(Contents())) 
    return(PrepareForOutgoing()); 
  // Inhalt an internes Ziel transferieren
  if (Local(0)&&Local(1)) 
    return( TransferToTarget() );
  // Inhalt an externes Ziel weiterleiten
  if (Local(2))
    return( TransferToExtTarget() );
  // Inhalt normal auswerfen  
  SetCommand(Contents(0),"Exit");
  SetCommand(Contents(1),"Exit");
  SetCommand(Contents(2),"Exit");
  SetCommand(Contents(3),"Exit");
  SetCommand(Contents(4),"Exit");
  SetCommand(Contents(5),"Exit");
  SetCommand(Contents(6),"Exit");
  SetCommand(Contents(7),"Exit");
  return(1);

PrepareForOutgoing:
  SetLocal(1,1);
  return(1);
  
TransferToTarget:
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
  
TransferToExtTarget:
  SetCommand(Contents(0),"Enter",Local(2));  
  SetCommand(Contents(1),"Enter",Local(2));  
  SetCommand(Contents(2),"Enter",Local(2));  
  SetCommand(Contents(3),"Enter",Local(2));  
  SetCommand(Contents(4),"Enter",Local(2));  
  SetCommand(Contents(5),"Enter",Local(2));  
  SetCommand(Contents(6),"Enter",Local(2));  
  SetCommand(Contents(7),"Enter",Local(2));  
  return(1);
  