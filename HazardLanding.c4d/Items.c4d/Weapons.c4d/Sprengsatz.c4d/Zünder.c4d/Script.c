#strict

//Local(0) - Ziel zum Fernsteuern
//Local(1) - 1 wenn Modus Massenauswahl
//Local(2) - 1 wenn Modus Airbike
//Local(3) - Ziel für Radar

func Entrance(pClonk)
{
	if(GetAlive(pClonk))
		SetOwner(GetOwner(pClonk));
	return(1);
}

func ControlDig(pClonk)
{
  if(Local(1))      return(ControlDig2(pClonk));//Modus Massenauswahl?
  if(Local(2))      var selID = AB5B;//Modus Airbike?
  if(!Local(2)) 	var selID = BO5B;//Normaler Modus
  var obj;
  while(obj = FindObject(selID,0,0,-1,-1,0,0,0,0,obj)) //Suche ein Objekt was weiter weg ist, als das bisherige Ziel
    if(ObjectDistance(obj,0)>ObjectDistance(Local(0),0)) 
      if(!FindObject(0,0,0,0,0,0,"Biking",obj))
		if(GetOwner(obj)==GetOwner(pClonk))
			if(!Contained(obj))
				return(Auswahl(obj));
  
  SetLocal(0,0);
  
  while(obj = FindObject(selID,0,0,-1,-1,0,0,0,0,obj))
    if(!FindObject(0,0,0,0,0,0,"Biking",obj))
	  if(GetOwner(obj)==GetOwner(pClonk))
		if(!Contained(obj))
			return(Auswahl(obj));
	  
  PlayerMessage(GetOwner(Par(0)),"kein Ziel vorhanden",Par(0));
  return(Sound("Error"));
}

//Massenauswahl
func ControlDig2(pClonk)
{
	var obj;
	for(obj in FindObjects(BO5B)) 
		if(!Hostile(GetOwner(obj),GetOwner(pClonk)))
			ObjectCall(SetLocal(0,obj),"Auswahl");
	if(!Local(0)) And(PlayerMessage(GetOwner(pClonk),"kein Ziel vorhanden",pClonk),Sound("Error"));
	return(1);
}

func ControlDigSingle()
{
  return(1);
}

func ControlThrow(pClonk)
{
  if(Local(2))      return(0);
  if(!Local(0)) 	return(And(PlayerMessage(GetOwner(pClonk),"kein Ziel ausgewählt",pClonk),Sound("Error")));
  if(Local(1))      return(ControlThrow2());//Massenauswahl
  
  SetPlrView(GetOwner(pClonk),Local(0));
  ObjectCall(Local(0),"Damage");
  return(1);
}

ControlThrow2:
  while(SetVar(0,FindObject(BO5B,0,0,0,0,0,0,0,0,Var(0)))) 
    if(Not(Hostile(GetOwner(Var(0)),GetOwner()))) ObjectCall(Var(0),"Damage");
  return(1);

func Auswahl(pObj)
{
  if(Not(Equal(pObj,GetActionTarget()))) Departure();
  SetLocal(0,pObj);
  SetComDir(COMD_Stop(),Contained());
  SetPlrView(GetOwner(Contained()),Local(0));
  ObjectCall(Local(0),"Auswahl");
  return(1);
}

ControlLeft:
  if(Not(Local(0))) return(0);
  if(Not(Local(2))) return(0);
  
  SetPlrView(GetOwner(Par(0)),Local(0));
  if(Not(SEqual(GetAction(Local(0)),"Hyperfly"))) 
    ObjectCall(Local(0),"ActivateEntrance",this());
  ObjectCall(Local(0),"ControlLeft",this());
  return(1);

ControlRight:
  if(Not(Local(0))) return(0);
  if(Not(Local(2))) return(0);
  
  SetPlrView(GetOwner(Par(0)),Local(0));
  if(Not(SEqual(GetAction(Local(0)),"Hyperfly"))) 
    ObjectCall(Local(0),"ActivateEntrance",this());
  ObjectCall(Local(0),"ControlRight",this());
  return(1);

ControlLeftDouble:
  if(Not(Local(0))) return(0);
  if(Not(Local(2))) return(0);
  
  SetPlrView(GetOwner(Par(0)),Local(0));
  if(Not(SEqual(GetAction(Local(0)),"Hyperfly"))) 
    ObjectCall(Local(0),"ActivateEntrance",this());
  ObjectCall(Local(0),"ControlLeftDouble",this());
  return(1);

ControlRightDouble:
  if(Not(Local(0))) return(0);
  if(Not(Local(2))) return(0);
  
  SetPlrView(GetOwner(Par(0)),Local(0));
  if (Not(SEqual(GetAction(Local(0)),"Hyperfly"))) 
    ObjectCall(Local(0),"ActivateEntrance",this());
  ObjectCall(Local(0),"ControlRightDouble",this());
  return(1);

ControlUp:
  if(Not(Local(0))) return(0);
  if(Not(Local(2))) return(0);
  
  SetPlrView(GetOwner(Par(0)),Local(0));
  if (Not(SEqual(GetAction(Local(0)),"Hyperfly"))) 
    ObjectCall(Local(0),"ActivateEntrance",this());
  ObjectCall(Local(0),"ControlUp",this());
  return(1);

ControlDown:
  if(Not(Local(0))) return(0);
  if(Not(Local(2))) return(0);
  
  SetPlrView(GetOwner(Par(0)),Local(0));
  if (Not(SEqual(GetAction(Local(0)),"Hyperfly"))) 
    ObjectCall(Local(0),"ActivateEntrance",this());
  ObjectCall(Local(0),"ControlDown",this());
  return(1);

ControlSpecial2:
  CreateMenu(Z15B,Par(0),0,0,0,0,0,1);
  AddMenuItem("%s","Modus1",Z25B,Par(0)); //Einzelauswahl
  AddMenuItem("%s","Modus2",Z35B,Par(0)); //Massenauswahl
  AddMenuItem("%s","Modus3",Z45B,Par(0)); //Airbike
  AddMenuItem("%s","Modus4",Z55B,Par(0)); //Feind-Radar
  return(1);

Modus1:
  Local(0)=0;
  Local(1)=0;
  Local(2)=0;
  
  Departure();
  CloseMenu(Contained());
  return(Sound("Modus"));

Modus2:
  Local(0)=0;
  Local(1)=1;
  Local(2)=0;
  
  Departure();
  CloseMenu(Contained());
  return(Sound("Modus"));

Modus3:
  Local(0)=0;
  Local(1)=0;
  Local(2)=1;
  
  Departure();
  CloseMenu(Contained());
  return(Sound("Modus"));

Modus4:
  while(Var(0)=FindObject(0,0,0,-1,-1,0,0,0,0,Var(0))) 
    if((GetOCF(Var(0))&OCF_CrewMember()&&Hostile(GetOwner(Var(0)),GetOwner()))||
        GetID(Var(0))==SR5B||
        GetID(Var(0))==ST5B||
        GetID(Var(0))==SK5B||
        GetID(Var(0))==KG5B||
        GetID(Var(0))==MI5B||
        GetID(Var(0))==MF5B)
    if(ObjectDistance(Var(0))>ObjectDistance(Local(3))) return(Radar(Var(0)));

  Local(3)=0;
  
  while(Var(0)=FindObject(0,0,0,-1,-1,0,0,0,0,Var(0))) 
    if((GetOCF(Var(0))&OCF_CrewMember()&&Hostile(GetOwner(Var(0)),GetOwner()))||
        GetID(Var(0))==SR5B||
        GetID(Var(0))==ST5B||
        GetID(Var(0))==SK5B||
        GetID(Var(0))==KG5B||
        GetID(Var(0))==MI5B||
        GetID(Var(0))==MF5B)
    return(Radar(Var(0)));
  
  return(PlayerMessage(GetOwner(Contained()),"keine feindlichen Aktivitäten",Contained())&&Sound("Error"));

Radar:
  Local(3)=Par(0);
  
  Var(0)=Contained();
  Var(1)=GetName(Local(3));
  Var(2)=ObjectDistance(Var(0),Local(3))/10;
  Var(3)=Angle(GetX(),GetY(),GetX(Local(3)),GetY(Local(3)));
  Var(4)=(Var(3)*10)/225+1;
  
  ClearMenuItems(Var(0));

  AddMenuItem("%s","Modus1",Z25B,Var(0));
  AddMenuItem("%s","Modus2",Z35B,Var(0));
  AddMenuItem("%s","Modus3",Z45B,Var(0));
  AddMenuItem(Format("%s [%d m]",Var(1),Var(2)),"Modus4",Z55B,Var(0),0,0,0,2,Var(4));
  
  SelectMenuItem(3,Var(0));
  return(Sound("ABAuswahl"));

Departure:
  Local(0)=0;
  Var(0)=GetOwner(Contained());
  SetPlrView(Var(0),GetCursor(Var(0)));
  return(SetAction("Walk"));

Hit:
  return(Sound("MetalHit*"));