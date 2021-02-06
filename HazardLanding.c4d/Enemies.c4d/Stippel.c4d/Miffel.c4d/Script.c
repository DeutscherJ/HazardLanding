//Miffel

//Local(0) - Opfer
//Local(1) - XDir
//Local(2) - YDir
//Local(3) - Fluggeschwindigkeit
//Local(4) - Fluggwinkel

#strict

/*Spieler KOntrolle*/
func ControlRight()
{
	if(Contained()) return(0);
	if(GetComDir()==COMD_DownLeft) SetComDir(COMD_Down);
	else if(GetComDir()==COMD_Down) SetComDir(COMD_DownRight);
	else if(GetComDir()==COMD_Left) SetComDir(COMD_Stop);
	else if(GetComDir()==COMD_UpLeft) SetComDir(COMD_Up);
	else if(GetComDir()==COMD_Up) SetComDir(COMD_UpRight);
	else if(GetComDir()==COMD_None) SetComDir(COMD_Right);
	SetSpeed();
	return(1);
}
func ControlLeft()
{
	if(Contained()) return(0);
	if(GetComDir()==COMD_DownRight) SetComDir(COMD_Down);
	else if(GetComDir()==COMD_Down) SetComDir(COMD_DownLeft);
	else if(GetComDir()==COMD_Right) SetComDir(COMD_Stop);
	else if(GetComDir()==COMD_UpRight) SetComDir(COMD_Up);
	else if(GetComDir()==COMD_Up) SetComDir(COMD_UpLeft);
	else if(GetComDir()==COMD_None) SetComDir(COMD_Left);
	SetSpeed();
	return(1);
}
func ControlUp()
{
	if(Contained()) return(0);
	if(GetComDir()==COMD_DownLeft) SetComDir(COMD_Left);
	else if(GetComDir()==COMD_Down) SetComDir(COMD_Stop);
	else if(GetComDir()==COMD_DownRight) SetComDir(COMD_Right);
	else if(GetComDir()==COMD_Right) SetComDir(COMD_UpRight);
	else if(GetComDir()==COMD_Left) SetComDir(COMD_UpLeft);
	else if(GetComDir()==COMD_None) SetComDir(COMD_Up);
	SetSpeed();
	return(1);
}
func ControlDown()
{
	if(Contained()) return(0);
	if(GetComDir()==COMD_UpLeft) SetComDir(COMD_Left);
	else if(GetComDir()==COMD_Up) SetComDir(COMD_Stop);
	else if(GetComDir()==COMD_UpRight) SetComDir(COMD_Right);
	else if(GetComDir()==COMD_Right) SetComDir(COMD_DownRight);
	else if(GetComDir()==COMD_Left) SetComDir(COMD_DownLeft);
	else if(GetComDir()==COMD_None) SetComDir(COMD_Down);
	SetSpeed();
	return(1);
}

func ControlThrow()
{
	if(Contained()) return(0);
	if(GetActionTarget()) return(SetActionTargets());
	var pObj = FindObject2(Find_OCF(OCF_Collectible),Find_Distance(20));
	SetActionTargets(pObj);
	return(1);
}

func ControlDig()
{
	if(Contained()) return(0);
	Stechen();
	return(1);
}

func SetSpeed()
{
	if(!IsControlled()) return(1);
	if(GetComDir()==COMD_None||GetComDir()==COMD_Left||GetComDir()==COMD_Right) SetYDir(0);
	if(GetComDir()==COMD_None||GetComDir()==COMD_Up||GetComDir()==COMD_Down) 	SetXDir(0);
	return(1);
}


func IsAlien(){return(1);}
func CheckEnemy(){return(true);}
func IsBulletTarget(){return(1);}
public func IsThreat() { return(true); }
func IsStippel(){return(true);}
func Intelligence(){return(15);}
func MaxIntelligence(iLvl){return(Intelligence()<=iLvl);}
func Schlagable(){return(1);}

func CatchBlow()
{
	if(!Random(4)) AlienBlood(RandomX(20,40));
	return(1);
}
Construction:
  SetAction("Kokon");
  ScheduleCall(this(),"LateInit",1);
  return(SetDir(Random(2)));

func LateInit()
{
  if(!InCrew(GetOwner()))
	SetOwner(-1);
	return(1);
}

Kokon:
  if(!FindObject(MB5B,0,1)&&GetCon()!=100)       return(EndeKokon());
  if(Random(ObjectCount(MI5B)*2)) return(0);
  if(GetCon()!=100)         	  return(DoCon(1));
  
  SetAction("Geburt");
  CastObjects(FZ5B,10,50);
  return(Sound("MIKokon"));

func ContactLeft()
{
	if(!Local(0))
		Local(4)=Local(4)+180+90*RandomX(-1,1);//In die andere Richtung drehen
	return(1);
}

func ContactRight()
{
	if(!Local(0))
		Local(4)=Local(4)+180+90*RandomX(-1,1);//In die andere Richtung drehen
	return(1);
}

func ContactTop()
{
	if(!Local(0))
		Local(4)=Local(4)+180+90*RandomX(-1,1);//In die andere Richtung drehen
	return(1);
}

func ContactBottom()
{
	if(!Local(0))
		Local(4)=Local(4)+180+90*RandomX(-1,1);//In die andere Richtung drehen
	return(1);
}

func FluegelSchlag()
{	
	if(GetActionTarget())
	{
	  var x = 2*GetDir()-2;
	  var y = 9+GetDefCoreVal("Height","DefCore",GetID(GetActionTarget()))/2;

	  SetPosition(GetX()-x,GetY()+y,GetActionTarget());

	  SetXDir(0,GetActionTarget());
	  SetYDir(0,GetActionTarget());
	}
	
	
	return(1);
}

func Fliegen()
{
  if(Stuck()) return(SetAction("Wasser"));  

	if(GetXDir()>0) if(!PathFree(GetX(),GetY(),GetX()+9,GetY()))  {ContactRight();SetXDir(0);}
	if(GetXDir()<0) if(!PathFree(GetX(),GetY(),GetX()-10,GetY())) {ContactLeft();SetXDir(0);}
	if(GetYDir()>0) if(!PathFree(GetX(),GetY(),GetX(),GetY()+10)) {ContactBottom();SetYDir(0);}
	if(GetYDir()<0) if(!PathFree(GetX(),GetY(),GetX(),GetY()-10)) {ContactTop();SetYDir(0);}
  if(GetXDir()<0) SetDir(DIR_Left);
  if(GetXDir()>0) SetDir(DIR_Right);
  
  if(IsControlled())return(0);
  if(!GetActionTarget()) 	Suche();
  else                   	Paket();
  
  /*Opfer verfolgen*/
  if(Local(0)&&!Contained(Local(0))&&PathFree(GetX(),GetY(),GetX(Local(0)),GetY(Local(0))))
  {
	if(ObjectDistance(this(),Local(0))>400) Local(0)=0;
    if(Inside(Distance(GetX(),GetY()+10,GetX(Local(0)),GetY(Local(0))),0,10)) return(Stechen());
    
    Local(4)=Angle(GetX(),GetY(),GetX(Local(0)),GetY(Local(0)));
    Var(1)=GetX(Local(0))-GetX();
    
    if(Var(1)<0) SetDir(DIR_Left());
    if(Var(1)>0) SetDir(DIR_Right());
  }
  /*Kein Opfer da?*/
  else
  {
    /*if(!FindObject(SK5B,-250,-250,500,500,OCF_InFree()))//Kein Kokon in nähe?
      if(!FindObject(0,-250,-250,500,500,OCF_CrewMember()))//Kein Gegner in der nähe?
        if(GBackSolid(0,20)) CreateObject(SK5B,0,5,-1)&&Sound("MIGeburt");//WEnn er knapp über dem Boden schwebt eier legen
    */
    /*if((GetID(GetActionTarget())==FLNT)&&
       (ObjectDistance(FindObject(KG5B))<100)) Var(0)=RandomX(-90,90);
    else                                       Var(0)=Random(359);*/
    
	Local(4)+=RandomX(-3,3);
	if(Local(4)>360) Local(4)-=360;
	if(Local(4)<-360) Local(4)+=360;
  }
  //Fluggeschwindigkeit zufällig ändern
  if(Random(2)) Local(3)=BoundBy(Local(3)+1,0,25);
  else          Local(3)=BoundBy(Local(3)-1,0,25);
  
  if(!IsControlled())
  {
	  //Fluggeschwindigkeit zufällig ändern
	  Local(1)=BoundBy(Local(1)+Sin(Local(4),5),-Local(3),Local(3));
	  Local(2)=BoundBy(Local(2)-Cos(Local(4),7),-Local(3),Local(3));
	  
	  SetXDir(Local(1));
	  SetYDir(Local(2));
			
		if(GetXDir()<-10) SetDir(DIR_Left());
		if(GetXDir()>+10) SetDir(DIR_Right());
		
		if(GBackLiquid(0,15))                                         SetYDir();
  }
  
  return(1);
}

func Suche()
{
  Local(0)=FindStippelTargetDistance(350,this());
  
  /* Flagge klauen ist auskommentiert. Das war irgendwie zu Evil
  Var(0)=FindObject(FLAG,0,0,-1,-1,0,0,0,NoContainer());

  if(Var(0) && FindObject(FGRV))//Flagge gefunden und abnehmbar?
	if(!FindObject(MI5B,0,0,0,0,0,"Fliegen",Var(0)))//Wurde diese noch nicht geklaut?
		if(!Random(ObjectDistance(Var(0)))) Local(0)=Var(0);//dann klau diese
 */
 
  //Var(0)=FindObject(KG5B);
  //
  //if(Var(0)) if(Random(ObjectDistance(Var(0)))<10) Local(0)=Var(0);
  return(1);
}

Paket:
  if(Contained(GetActionTarget())) return(SetActionTargets());
  
  if(GetID(GetActionTarget())==FLNT)
    if(FindObject(0,-5,0,10,LandscapeHeight(),OCF_Container())||
      FindObject(0,-5,0,10,LandscapeHeight(),OCF_CrewMember(),0,0,NoContainer()))
        return((SetXDir(0,GetActionTarget()))&&(SetActionTargets()));
  
  if(!GetAlive(GetActionTarget())) if(Local(0)) return(SetActionTargets());
  /*
  if(GetID(GetActionTarget())==FLAG) {Var(0)=2*GetDir()-2; Var(1)=12;}
  if(GetID(GetActionTarget())==FLNT) {Var(0)=4*GetDir()-2; Var(1)=10;}

  SetPosition(GetX()-Var(0),GetY()+Var(1),GetActionTarget());

  SetXDir(GetXDir(),GetActionTarget());
  SetYDir(GetYDir(),GetActionTarget());*/
  return(1);

func Stechen()
{
	if(!Local(0))
		Suche();
  if(GetID(Local(0))==FLAG && FindObject(FGRV))//Flagge abnehmen
  {
    ObjectSetAction(Local(0),"Idle");
    SetActionTargets(Local(0));
    Local(0)=0;
    return(1);
  }
  /*
  if(GetID(Local(0))==KG5B)//Flint bei Königin abholen
  {
    if(!(Var(0)=FindObject(FLNT,-25,-25,50,50,0,0,0,NoContainer()))) return(0);
    if(FindObject(MI5B,0,0,0,0,0,"Fliegen",Var(0)))                  return(0);
    SetActionTargets(Var(0));
    Local(0)=0;
    Local(3)=0;
    SetXDir();
    SetYDir();
    return(1);
  }*/
  //Clonks stechen
  if(GetAction()eq"Stechen") return(SetXDir()&&SetYDir());
  SetAction("Stechen");
  Sound("MIStechen");
  
  
  if(!Local(0)) return(0);
  if(!GetAlive(Local(0)))
	return(DoEnergy(-Random(10),Local(0)));
  DoDmg(Random(10*GetCon()/100), DMG_Melee, Local(0));
  return(1);
}

Incineration:
  if(GetAction()eq"Kokon") return(EndeKokon());
  ObjectSetAction(this(),"Feuer",0,0,1);
  return(1);

Feuer:
  SetXDir();
  SetYDir();
  return(DoCon(-10));

Wasser:
  if(GBackSemiSolid(0,-1)) return(0);
  SetPosition(GetX(),GetY()-1);  
  SetAction("Fliegen");
  return(1);

Damage:
  if(!OnFire()) return(Death());
  return(1);

Death:
  if(GetAction()eq"Kokon") return(EndeKokon());
  if(GetAction()eq"Ende")  return(0);
  SetAction("Ende");
  SetXDir(Par(0)*100);
  CreateObject(FG5B,0,0,-1);
  CreateObject(FG5B,0,0,-1);
  return(1);

EndeKokon:
  CastObjects(FZ5B,10,50);
  Sound("MIKokon");
  return(RemoveObject());

Ende:
  SetYDir();
  return(DoCon(-10));