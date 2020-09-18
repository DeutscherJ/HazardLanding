//Moff
#strict

func IsAlien(){return(1);}
func CheckEnemy(){return(true);}
func IsBulletTarget(){return(1);}
public func IsThreat() { return(true); }
func IsStippel(){return(true);}
func Intelligence(){return(15);}
func MaxIntelligence(iLvl){return(Intelligence()<=iLvl);}
func Schlagable(){return(1);} 

func Hammered(pObj,iStrength)
{
	DoEnergy(-iStrength,this());
	OnHit(iStrength,DMG_Melee,pObj);
	return(1);
}

func OnHit(int iDamage, int iType, object pFrom)
{
	return(CatchBlow(iDamage,pFrom));
}

func CatchBlow(iLvl,pObj)
{
	if(!Random(4)||iLvl>10) AlienBlood(RandomX(20,40));
	Damage();
	if(GetAlive(pObj))
	{
		for(var stippel in FindObjects(Find_Func("IsAlien",this()),Find_Owner(GetOwner()),Find_Distance(350)))
			stippel->~AngegriffenVon(pObj,this());
		AngegriffenVon(pObj);
		SetEnemyObject(pObj,GetOwner());
	}
	return(1);
}

func AngegriffenVon(pObj,pStippelOpfer){return(1);}

Initialize:
	SetOwner(-1);
  SetAction("Walk");
  return(1);

Departure:
  SetAction("Start");
  return(1);

Zyklus:
  Suche();
  Angriff();
  Graben();
  if(!Random(19)) Graben(1);
  Verteilen();
  return(1);

/*Suche einen Gegner und verfolge diesen*/
func Suche()
{
	var Clonk = FindStippelTargetDistance(300,this());
	//if(GetOwner()==-1)
	//	var Clonk=FindObject2(Find_Distance(300),Find_Or(Find_OCF(OCF_CrewMember()),Find_Func("IsMachine"),Find_Func("CheckEnemyObject",GetOwner())),Find_NoContainer());//FindObject(0,0,0,-1,-1,OCF_CrewMember(),0,0,NoContainer());
	//else
	//	var Clonk=FindObject2(Find_Distance(300),Find_Or(Find_And(Find_Or(Find_Owner(-1),Find_Hostile(GetOwner())),Find_Or(Find_OCF(OCF_Alive),Find_Func("IsMachine"))),Find_Func("CheckEnemyObject",GetOwner())),Find_NoContainer());
  var Queen=FindObject(KG5B,0,0,0,0,0,"Halten",this());

  if(Queen)
  {
    SetCommand(this(),"None");

    if(GetX()<GetX(Clonk)) return(SetComDir(COMD_Left()));
    else                   return(SetComDir(COMD_Right()));
  }
  if(!Clonk)                                           return(Stop());
  if(Stuck())                                          return(Stop());
  if((GetAction()ne"Walk")&&(GetAction()ne"Swim"))     return(Stop());
  if(!PathFree(GetX(),GetY(),GetX(Clonk),GetY(Clonk))) return(Stop());

  SetCommand(this(),"Follow",Clonk);
  return(1);
}

/*Greife einen Gegner an*/
func Angriff()
{
	var Clonk = FindStippelTargetDistance(25,this());
	//if(GetOwner()==-1)
	//	var Clonk=FindObject2(Find_InRect(-25,-25,50,50),Find_Or(Find_OCF(OCF_CrewMember()),Find_Func("IsDrone"),Find_Func("CheckEnemyObject",GetOwner())),Find_NoContainer());//FindObject(0,-25,-25,50,50,OCF_CrewMember(),0,0,NoContainer());
	//else
	//	var Clonk=FindObject2(Find_InRect(-25,-25,50,50),
	//	Find_Or(Find_And(Find_Or(Find_Owner(-1),Find_Hostile(GetOwner())),Find_Or(Find_OCF(OCF_Alive),Find_Func("IsDrone"))),Find_Func("CheckEnemyObject",GetOwner())),
	//	Find_NoContainer());//FindObject(0,-25,-25,50,50,OCF_CrewMember(),0,0,NoContainer());
  var Queen=FindObject(KG5B,0,0,0,0,0,"Lauern",Clonk);
  var Abstand;

  if(!Clonk)                                           return(0);
  if(Stuck())                                          return(0);
  if((GetAction()ne"Walk")&&(GetAction()ne"Swim"))     return(0);
  if(!PathFree(GetX(),GetY(),GetX(Clonk),GetY(Clonk))) return(0);

  //Opfer zu einer Königin hinwerfen
  if(Queen) 
  {
    SetAction("Werfen",Clonk,Queen);
    Abstand=(GetX(Queen)-GetX(Clonk));
  }
  else
  {
    SetAction("Hacken",Clonk);
    Abstand=(GetX(Clonk)-GetX());
  }
  //Zu Opfer hindrehen
  if(Abstand>0) SetDir(DIR_Right());
  else SetDir(DIR_Left());
  return(1);
}

/*Schadenverteiler*/
func Hacken()
{
  var Clonk=GetActionTarget();
  
  if(Clonk==this())
  {
    //DigFree(GetX()-10,GetY()+1,11);
    //DigFree(GetX()+10,GetY()+1,11);
	
    DigFreeRect(GetX()-10,GetY()-10,20,22);
	DigFree(GetX()-10,GetY()+1,10);
	DigFree(GetX()+10,GetY()+1,10);
	for (var x=0;x<=8;x++)
	{
		if(PathFree(GetX(),GetY(),GetX()-10-x*2+2,GetY()+1-x))
			DigFree(GetX()-10-x*2,GetY()+1-x,10-x);
		if(PathFree(GetX(),GetY(),GetX()+10+x*2-2,GetY()+1-x))
			DigFree(GetX()+10+x*2,GetY()+1-x,10-x);
	}
	
    //DigFreeRect(GetX()+(21*GetDir()-21),GetY(),21,12);
    
    Sound("MFHacken3");
    return(1);
  }
  if(!GetAlive(Clonk))                      return(Sound("MFHacken1"));
  if(Contained(Clonk))                      return(Sound("MFHacken1"));
  if(!Inside(ObjectDistance(Clonk,0),0,25)) return(Sound("MFHacken1"));
  
  if(GetAlive())
  {
    DoDmg(25*GetCon()/100, DMG_Melee, Clonk);
	//DoEnergy(-25,Clonk);
	Fling(Clonk,2*GetDir()-1,1);
  }
  else
	DoDamage(25,Clonk);
  Sound("MFHacken2");
  return(1);
}

func Werfen()
{
  var Clonk=GetActionTarget(0);
  var Queen=GetActionTarget(1);
  var Power=(GetX(Queen)-GetX(Clonk))/25;

  if(!GetAlive(Clonk))                      return(Sound("MFHacken1"));
  if(Contained(Clonk))                      return(Sound("MFHacken1"));
  if(!Inside(ObjectDistance(Clonk,0),0,25)) return(Sound("MFHacken1"));
  
  if(!Power) Power=2*GetDir()-1;

  Fling(Clonk,Power,-3);
  Sound("MFHacken4");
  return(1);
}

/*Grabe den Weg frei und bewege dich zufällig*/
func Graben(fCondition)
{
  if(fCondition||(GetMaterial(2*GetDir()-1,8)==Material("Earth"))||
     (GetMaterial(2*GetDir()-1,8)==Material("Sand"))||
     (GetMaterial(2*GetDir()-1,8)==Material("FlySand"))||
     (GetMaterial(2*GetDir()-1,8)==Material("Snow"))||
     (GetMaterial(2*GetDir()-1,8)==Material("Ice"))||
     (GetMaterial(2*GetDir()-1,8)==Material("Coal"))||
     (GetMaterial(2*GetDir()-1,8)==Material("Sulphur"))||
     (GetMaterial(2*GetDir()-1,8)==Material("Ashes"))||
     (GetMaterial(2*GetDir()-1,8)==Material("FlyAshes")))
  SetAction("Hacken",this());

  if(FindObject(KG5B,0,0,0,0,0,"Halten",this())) return(0);
  if(GetCommand())                               return(0);
  if(Random(5))                                  return(0);
    
  if(Random(2)) SetComDir(COMD_Left());
  else          SetComDir(COMD_Right());
  return(1);
}

/*Bewegen*/
func Verteilen()
{
  if(FindObject(KG5B,0,0,0,0,0,"Halten",this())) return(0);

  if(FindObject(MF5B,-25,-25,50,50))
  {   
    SetCommand(this(),"None");

    if(Random(2)) SetComDir(COMD_Left());
    else          SetComDir(COMD_Right());
  }
  
  //Von den Landschaftsrändern wegbewegen
  if(!Inside(GetX(),50,LandscapeWidth()-50))
  {
    SetCommand(this(),"None");
    
    if(GetX()<50) SetComDir(COMD_Right());
    else          SetComDir(COMD_Left());
  }
  return(1);
}

Halten:
  var Queen;
  
  Queen=FindObject(KG5B,-5,-5,10,10);

  if(!Queen)                      return(0);
  if(Random(GetEnergy(Queen)/50)) return(0);

  ObjectSetAction(Queen,"Halten",this());
  return(1);

Stop:
  SetCommand(this(),"None");
  SetComDir(COMD_Stop());
  return(1);

//Incineration:
//  Extinguish();
//  return(1);

Damage:
  SetCommand(this(),"None"); 
  
  if(Par(0)>0) SetComDir(COMD_Right());
  if(Par(0)<0) SetComDir(COMD_Left());
  
  Sound("MFSchaden*");
  return(1);

Ende:
  CreateObject(SK5B,-11*GetDir()+5,12,-1);
  if(!Random(7)) CastObjects(MLG4,1,15); //Ein Bein verlieren?
  RemoveObject();
  return(1);