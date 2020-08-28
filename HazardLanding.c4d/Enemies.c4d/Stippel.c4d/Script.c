//Stippel
#strict

local Beisszeit;
local Schwanger;
local pTarget;
static SchwangerMaxTime, iKokonNaehe, iLegeNaehe, iMaxStippel;

//func IsBulletTarget(){return(1);}
public func IsThreat() { return(true); }
func IsAlien(){return(1);}
func IsStippel(){return(true);}
func CheckEnemy(){return(true);}
func Intelligence(){return(10);}
func MaxIntelligence(iLvl){return(Intelligence()<=iLvl);}
func Schlagable(){return(1);}

func OnHit(int iDamage, int iType, object pFrom)
{
	return(CatchBlow(iDamage,pFrom));
}

func CatchBlow(iLvl,pObj)
{
	if(!Random(4)||iLvl>10) AlienBlood(RandomX(20,40));
	if(GetAlive(pObj))
	{
		for(var stippel in FindObjects(Find_Func("IsAlien",this()),Find_Owner(GetOwner()),Find_Distance(350)))
			stippel->~AngegriffenVon(pObj,this());
		AngegriffenVon(pObj);
		SetEnemyObject(pObj,GetOwner());
	}
	return(1);
}

func AngegriffenVon(pObj,pStippelOpfer)
{
	if(pObj->~IsStippel() && GetOwner(pObj)==GetOwner()) return(0); 
	if(ObjectDistance(pTarget,this())<250)
	{
		if(!pTarget) pTarget=pObj;
		else
			if(ObjectDistance(pObj,this())<ObjectDistance(pTarget,this()))
				pTarget=pObj;
	}
	return(1);
}

func Initialize()
{
  SetOwner(-1);
  SetAction("Walk");
  SchwangerMaxTime = 100;
  
  if(ObjectCount(KG5B))                                return(0);
  if(!Inside(GetX(),50,LandscapeWidth()-50))           return(0);
  if(Random(BoundBy(100-ObjectCount(ST5B),1,50)))      return(0);
  if(FindObject(0,-100,-100,200,200,OCF_CrewMember())) return(0);
  
  CreateConstruction(KG5B,0,6,-1,50);
  RemoveObject();
  return(1);
}

func Zyklus()
{
  Kokon();
  Verteilen();
  Suche();//Opfer suchen
  Angriff();//Opfer angreifen
  return(1);
}
func ChangeOwner(iNewOwner,iOldOwner)
{
	pTarget=0;
	return(1);
}
func Suche()
{
  if(pTarget)
	  if(!GetAlive(pTarget)||ObjectDistance(this(),pTarget)>300)
		  pTarget = 0;
	
  //var Clonk = FindObject(0,0,0,-1,-1,OCF_CrewMember());
  if(GetOwner()>=0) //Kein Besitzer?
	var Clonk = FindObject2(Find_Distance(150),
	Find_Or(Find_OCF(OCF_Alive()),Find_Func("IsDrone")),
	Find_NoContainer(),
	Find_Or(Find_Owner(-1),Find_Hostile(GetOwner())),
	Find_Not(Find_Func("IsDying")));//FindObject(0,-50,-50,100,100,OCF_CrewMember(),0,0,NoContainer());
  else
	var Clonk = FindObject2(Find_Distance(150), Find_Or(Find_OCF(OCF_CrewMember()),Find_Func("IsDrone")),Find_NoContainer(),Find_Not(Find_Func("IsDying")));//FindObject(0,-50,-50,100,100,OCF_CrewMember(),0,0,NoContainer());
  
  //var Clonk = FindObject2(Find_Distance(150), Find_Or(Find_OCF(OCF_Alive()),Find_Func("IsDrone")),Find_NoContainer(),Find_Not(Find_Owner(GetOwner())));
  var Queen = FindObject2(Find_ID(KG5B),Find_Distance(300));
   
  if(GetAction()eq"Scale") 			  return(0);
  if(Queen) if(GetEnergy(Queen)<100)  return(SetCommand(this(),"MoveTo",Queen));
  if(Schwanger>SchwangerMaxTime)      return(0);
  if(Clonk)
  {
	if(!pTarget) pTarget = Clonk;//Opfer speichern
	else if(pTarget != Clonk)//Ist das neue Opfer etwas näher dran?
		if(ObjectDistance(pTarget,this())-50>ObjectDistance(Clonk,this())) pTarget = Clonk;
  }
  
  if(!pTarget) return(0);
  SetCommand(this(),"MoveTo",pTarget);
  return(1);
}

func Angriff()
{
  //var Clonk=FindObject(0,-50,-50,100,100,OCF_CrewMember(),0,0,NoContainer());
  if(GetOwner()>=0)
	var Clonk = FindObject2(Find_InRect(-50,-50,100,100),
	Find_Or(Find_OCF(OCF_Alive()),Find_Func("IsDrone")),
	Find_NoContainer(),
	Find_Or(Find_Owner(-1),Find_Hostile(GetOwner())),
	Find_Not(Find_Func("IsDying")));//FindObject(0,-50,-50,100,100,OCF_CrewMember(),0,0,NoContainer());
  else
	var Clonk = FindObject2(Find_InRect(-50,-50,100,100), Find_Or(Find_OCF(OCF_Alive()),Find_Func("IsDrone")),Find_Not(Find_Owner(-1)),Find_NoContainer(),Find_Not(Find_Func("IsDying")));//FindObject(0,-50,-50,100,100,OCF_CrewMember(),0,0,NoContainer());
  
  if(ObjectDistance(pTarget,this())<50)
	var Clonk = pTarget;
  
  var Abstand;

  if(!Clonk)                                           return(0);
  if(GBackSemiSolid())                                 return(0);
  if(GetAction()eq"Beissen")                           return(0);
  if(!PathFree(GetX(),GetY(),GetX(Clonk),GetY(Clonk))) return(0);
    
  SetXDir(Abstand=(GetX(Clonk)-GetX())); 
  SetYDir(GetY(Clonk)-GetY()-10);
  
  SetAction("Beissen",Clonk);
  Beisszeit=0;
  
  if(Abstand>0) SetDir(DIR_Right());
  else SetDir(DIR_Left());
  Sound("STAngriff*");
  return(1);
}

func Beissen()
{
  var Clonk=GetActionTarget();

  Beisszeit++;
  
  if(Beisszeit>10)            return(0);
  //if(!GetAlive(Clonk))        return(0);
  if(Contained(Clonk))        Clonk=Contained(Clonk);//Behälter des Opfers angreifen
  if(ObjectDistance(Clonk)>5) return(0);
  
  SetXDir(0);
  SetYDir(0);
  
  if(Clonk)
	  if(Clonk!=this())
		{
			if(GetAlive(Clonk))
			{
				DoEnergy(-5,Clonk);//Clonk beschädigen
				Fling(Clonk,4*GetDir()-2,-1);
			}
			else
				DoDamage(5,Clonk);
		}
  return(1);
}

func Kokon()
{
  if(!SchwangerMaxTime) 	SchwangerMaxTime = 80;
  if(!iKokonNaehe) 			iKokonNaehe = 150;
  if(!iLegeNaehe) 			iLegeNaehe  = 300;
  if(!iMaxStippel) 			iMaxStippel = 50;
  
  var Kokon = FindObject2(Find_ID(SK5B),Find_Distance(iKokonNaehe),Find_NoContainer());
  
  if(Par(0)) Schwanger=SchwangerMaxTime;
  else Schwanger++;
  
  if(ObjectCount2(Find_Func("IsStippel"),Find_Distance(iLegeNaehe))>iMaxStippel) 	return(0);//Zu Viele Stippel?
  if(FindObject(0,-100,-100,200,200,OCF_CrewMember())) 								return(0);//Nicht in Anwesenheit von anderen Clonks legen?
  if(Schwanger<SchwangerMaxTime) 	return(0);
  if(GetAction()eq"Scale") 			return(0);
  if(GBackSemiSolid())    			return(0);
  
  if(Kokon)//Einen Kokon neben den anderen legen?
	{
		SetCommand(this(),"MoveTo",Kokon);
		if(!Inside(ObjectDistance(Kokon),5,10)) return(0);
	}
  CreateObject(SK5B,0,6,-1);
  Sound("STGeburt*");
  Schwanger = 0;
  return(1);
}

func Verteilen()
{
  if(GetAction()eq"Swim") SetComDir(COMD_Up());
  if(FindObject(ST5B,-5,-5,10,10))
  {   
    SetCommand(this(),"None");

    if(GetAction()eq"Scale")
    {
      if(Random(2)) SetComDir(COMD_Up());
      else          SetComDir(COMD_Down());
    }
    else
    {
      if(Random(2)) SetComDir(COMD_Left());
      else          SetComDir(COMD_Right());
    }
  }
  if(FindObject(SK5B,-5,-5,10,10))
  {
    SetCommand(this(),"None");    

    if(GetDir()==DIR_Left())  SetComDir(COMD_Left());
    if(GetDir()==DIR_Right()) SetComDir(COMD_Right());
  }
  if(!Inside(GetX(),50,LandscapeWidth()-50))
  {
    SetCommand(this(),"None");
    
    if(GetX()<50) SetComDir(COMD_Right());
    else          SetComDir(COMD_Left());
  }
  return(1);
}

func Laufen()
{
  if(GetDir()==DIR_Left())  {SetVertex(3,0,0,0); SetVertex(2,0,-4,0);}
  if(GetDir()==DIR_Right()) {SetVertex(2,0,0,0); SetVertex(3,0,3,0);}
  
  SetVertex(1,1,5,0);
  return(1);
}

func Klettern()
{
  if(GetComDir()==COMD_Down()) return(SetVertex(1,1,5,0));

  SetVertex(1,1,0,0);
  SetCommand(this(),"None");
  return(1);
}

func ContactLeft()
{
  if(GetAction()eq"Beissen") if(GetPhase()==17) SetAction("Scale");
  return(1);
}
  
func ContactRight()
{
  if(GetAction()eq"Beissen") if(GetPhase()==17) SetAction("Scale");
  return(1);
}

func ContactBottom()
{
  if(GetAction()eq"Beissen") if(GetPhase()==17) SetAction("Walk");
  return(1);
}

func Incineration(){return(Death());}

//Sterben
func Death()
{
  CastObjects(FZ5B,10,50);
  AlienBlood(40);
  Sound("STTot*");
  RemoveObject();
  return(1);
}