#strict

public func IsChemicalProduct() { return(1); }
Activate:
  if(Local(0)) return(Sound("Error")); 
  if(SEqual(GetAction(),"Test")) return(Sound("Error")); 
  if(Hostile(GetOwner(),GetOwner(Par(0)))) 
    return(And(PlayerMessage(GetOwner(Par(0)),"kein Zugriff",Par(0)),Sound("Error")));
  if(SEqual(GetAction(),"Zeit")) return(Stop());
  return(SetAction("Zeit"));

Zeit:
  if(Not(SEqual(GetAction(),"Zeit"))) return(0);
  SetLocal(2,Sum(Local(2),1));
  if(GreaterThan(Local(2),10)) return(Damage());
  return(Message("@%d",this(),Mul(Sub(Local(2),11),-1)));

Stop:
  SetAction("Auswahl");
  return(Message("Stop",this()));

Auswahl:
  if(SEqual(GetAction(),"Zeit")) Message("Stop",this());
  SetAction("Auswahl");
  return(Sound("BOAuswahl"));

func ContextAids(pObj)
{
	[Modus|Image=B15B]
	ControlSpecial2(pObj);
	return(1);
}

ControlSpecial2:
  if(Hostile(GetOwner(),GetOwner(Par(0)))) 
    return(And(PlayerMessage(GetOwner(Par(0)),"kein Zugriff",Par(0)),Sound("Error")));
  CreateMenu(B15B,Par(0));
  AddMenuItem("%s","Modus1",B25B,Par(0));
  AddMenuItem("%s","Modus2",B35B,Par(0));
  AddMenuItem("%s","Modus3",B45B,Par(0));
  if(Equal(Local(1),0)) AddMenuItem("%s einschalten","Modus4",B55B,Par(0));
  if(Equal(Local(1),1)) AddMenuItem("%s ausschalten","Modus4",B55B,Par(0));
  return(1);

Modus1:
  SetLocal(0);
  if(SEqual(GetAction(),"Test")) SetAction("Auswahl");
  return(Sound("Modus"));

Modus2:
  SetLocal(0,1);
  SetLocal(1,0);
  if(SEqual(GetAction(),"Zeit")) Stop();
  if(SEqual(GetAction(),"Test")) SetAction("Auswahl");
  return(Sound("Modus"));

Modus3:
  SetLocal(0);
  if(SEqual(GetAction(),"Zeit")) Stop();
  SetAction("Test");
  return(Sound("Modus"));

Modus4:
  if(Local(0))          return(Sound("Error"));
  if(Equal(Local(1),0)) return(And(SetLocal(1,1),Sound("Modus")));
  if(Equal(Local(1),1)) return(And(SetLocal(1,0),Sound("Modus")));
  return(1);

Test:
  while(SetVar(0,FindObject(0,-10,-10,20,20,OCF_Alive(),0,0,0,Var(0)))) 
    if(PathFree(GetX(),GetY(),GetX(Var(0)),GetY(Var(0))))
      if(Not(BitAnd(GetOCF(Var(0)),OCF_CrewMember())))  
        if(Not(Equal(GetID(Var(0)),ZAP1)))  
          if(Containertest(Var(0))) return(Damage());
  while(SetVar(0,FindObject(0,-10,-10,20,20,OCF_CrewMember(),0,0,0,Var(0)))) 
    if(Hostile(GetOwner(),GetOwner(Var(0))))
      if(Containertest(Var(0))) return(Damage());
  return(1);

Containertest:
  if(Contained(Contained()))                             return(0);
  if(Not(Contained()))                                   return(1);
  if(BitAnd(GetOCF(Contained()),OCF_Living()))           return(1);
  if(Equal(Contained(),Contained(Par(0))))               return(1); 
  if(Equal(GetController(Contained()),GetOwner(Par(0)))) return(1);
  if(Equal(Contained(),GetActionTarget(0,Par(0))))	 return(1);
  return(0);

func Entrance(pClonk)
{
	if(GetAlive(pClonk)) SetOwner(GetOwner(pClonk));
	if(!Local(1)) return(0);
	SetCategory(2576);
	while(Not(Equal(Contents(0,Par(0)),this()))) ShiftContents(Par(0));
	return(1);
}

Hit:
  if(Contained()) return(0);
  if(Local(0)) return(Damage());
  if(Local(1)) SetCategory(1);
  return(Sound("MetalHit*"));

Damage:
  if(BitAnd(GetOCF(Contained()),OCF_Living())) DoEnergy(-100,Contained());
  return(Explode(50));