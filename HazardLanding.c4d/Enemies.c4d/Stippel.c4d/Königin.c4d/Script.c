//Königin
#strict
func IsAlien(){return(1);}
func CheckEnemy(){return(true);}
func IsBulletTarget(){return(1);}
public func IsThreat() { return(true); }
func IsStippel(){return(true);}
func Intelligence(){return(60);}
func MaxIntelligence(iLvl){return(Intelligence()<=iLvl);}
func Schlagable(){return(1);}

func CatchBlow()
{
	if(!Random(4)) AlienBlood(RandomX(20,40));
	return(1);
}
func Initialize()
{
	SetOwner(-1);
	return(1);
}

func Zyklus()
{
  var Clonk;
  
  Clonk=FindObject(0,0,0,-1,-1,OCF_CrewMember());  
 
  if(GetAction()eq"Halten")
  {
    if(!Inside(GetX(),50,LandscapeWidth()-50)) return(SetAction("Zu"));
    if(ObjectDistance(Clonk)>250)              return(SetAction("Zu"));
    else                                       return(0);
  }
  if(GetCon()<100) return(0);
  
  Produktion();
  Angriff(); 
  Verdauung();
  return(1);
}

func Produktion()
{
  var Inhalt=Contents();
  
  if(Inhalt)
	if(Inhalt->~IsStippel()||(GetID(Inhalt)==FLNT))
	{
		SetAction("Auf",Inhalt);
		return(1);
	}
  if(!Random(ObjectCount(MF5B)*10))
  {
    if(!FindObject(MF5B,-25,-25,50,50))
    {
      CreateContents(MF5B);
      if(GetAction()eq"Lauern") SetAction("Abbruch");
    }
  }
  if(!Random(ObjectCount2(Find_ID(ST5B),Find_Distance(800))*3))
  {
    if(!FindObject(ST5B,-25,-25,50,50))
    {
      CreateContents(ST5B);
      if(GetAction()eq"Lauern") SetAction("Abbruch");
    }
  }
  else if(Local(0,FindObject(MI5B,-10,-10,20,20))==this())
  {
    CreateContents(FLNT);
    if(GetAction()eq"Lauern") SetAction("Abbruch");
  }
  return(1);
}

Angriff:
  var Clonk=FindObject(0,-150,-500,300,550,OCF_CrewMember(),0,0,NoContainer());
  
  if(Contents()) return(0);

  if(!Clonk)
  {
    if(GetAction()eq"Lauern") return(SetAction("Abbruch"));
    else                      return(0);
  }
  if(GetAction()ne"Lauern") return(SetAction("Lauern",Clonk));

  if(!PathFree(GetX(),GetY(),GetX(Clonk),GetY(Clonk))) return(0);
  if(ObjectDistance(Clonk)>20)                         return(0);
  
  SetAction("Fressen");
  Enter(this(),Clonk);
  ObjectSetAction(Clonk,"Idle");
  Sound("KGFressen");
  return(1);

Verdauung:
	var Inhalt=Contents();
	var i;

	if(!Inhalt) return(0);
	
	if(GetEnergy(Inhalt)==1)
	{
		for(i=1; i<Random(25); i++) CreateContents(BONE);    
		while(Contents(0,Inhalt)) Enter(this(),Contents(0,Inhalt));
	}
	if(GetAlive(Inhalt))
	{
		DoEnergy(-1,Inhalt);
		DoEnergy(+2);
		return(1);
	}
	SetAction("Auf",Inhalt);
	return(1);

Auswurf:
  var Inhalt=GetActionTarget();
  
  if(Inhalt->~IsStippel()||(GetID(Inhalt)==FLNT))
  {
    Exit(Inhalt,0,5);
    Sound("KGGeburt*");
    return(1);
  }
  Exit(Inhalt,0,5,0,RandomX(-5,5),-1*Random(5),RandomX(-50,50));
  Sound("KGRulps*");
  return(1);

Incineration:
  Extinguish();
  return(1);

CatchBlow:
  Damage();
  return(1);

Damage:
  CastObjects(FZ5B,10,50);
  
  if(Random(ObjectCount(MF5B,-100,-25,200,50))) return(0);
 
  if(!FindObject(MF5B,-25,-25,50,50))
  {
    CreateContents(MF5B);
    if(GetAction()eq"Lauern") SetAction("Abbruch");
  }
  Sound("KGSchrei*");
  return(1);

Death:
  var Clonk;
  
  Clonk=FindObject(0,0,0,1,1,OCF_CrewMember());
  
  SetComDir(COMD_Stop(),Clonk);
  SetDir(Random(2),Clonk);
  ObjectSetAction(Clonk,"FlatUp");
  
  SetAction("Ende");
  CastObjects(FZ5B,25,50);
  CastPXS("Acid",25,50,RandomX(-10,10),RandomX(-10,10));
  CastPXS("Acid",25,50,RandomX(-10,10),RandomX(-10,10));
  CastPXS("Acid",25,50,RandomX(-10,10),RandomX(-10,10));
  Sound("KGTot");
  return(1);

Ende:
  RemoveObject();
  return(1);