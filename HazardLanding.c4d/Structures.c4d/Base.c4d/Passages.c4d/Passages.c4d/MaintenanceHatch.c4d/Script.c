#strict
#include _CM1

func IsPassage(){return(1);}
func Passange()
{
	return(FindObject2(Find_ID(MF5B),Find_Distance(150)));
}

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
		SetGraphics("2");
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

func Open(){return(GetAction()eq"DoorDestroyed");}
func DoOpen(pObj)
{
	SetCommand(pObj,"MoveTo",this());
	if(!Local(5))
	{
		Sound("STCommand");
		Local(5)=FindObject2(Find_ID(MF5B),Find_Distance(150));
	}
	SetCommand(Local(5),"MoveTo",this());
	AppendCommand(this(),"Call",Local(5),0,0,this(),0,"Angriff");
	return();
}

protected Initialize:
    SetLocal(0,0); // Transfer-Zielobjekt
	SetLocal(1,1); // Status Eingang/Ausgang
	return(1);	
	
public SetTarget:
  SetLocal(0,Par(0));
  return(1);	 
  
private CheckContents:					
  //if (Not(ActIdle())) return(0);
  if (!Contents()) return(PrepareForOutgoing());  
  if (Local(0)&&Local(1)) return(TransferToTarget());  
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