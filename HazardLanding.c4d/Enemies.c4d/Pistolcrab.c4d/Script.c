/*-- Krabbe --*/

#strict

local timer, damage;
local x, y, count;
local victim;

func CatchBlow(iLvl,pObj)
{
	if(GetAlive(pObj))
	{
		for(var stippel in FindObjects(Find_Func("IsAlien",this()),Find_Owner(GetOwner()),Find_Distance(350)))
			stippel->~AngegriffenVon(pObj,this());
		SetEnemyObject(pObj,GetOwner());
	}
	return(1);
}

func ControlDigDouble()
{
	if(GetAction() eq "Dead")
	{
		AlienBlood(40);
		RemoveObject();
	}
	return(1);
}

func Initialize()
{
  SetAction("Walk");
  SetObjDrawTransform(-1000,0,0,0,1000,0);
  return(1);
}

func Activity()
{
	if(!victim) FeindFindung();
	else Angriff();
	
	Schadensregulierung();
	Bewegung();
	
	x= GetX();
	y= GetY();
	return(1);
}

func FeindFindung()
{
	//if(GetOwner()==-1) victim = FindObject2(Find_Or(Find_OCF(OCF_Prey()),Find_Func("IsDrone"),Find_Func("CheckEnemyObject",GetOwner())),Find_Distance(200));
	//else victim = FindObject2(Find_Or(Find_OCF(OCF_Prey()),Find_Func("IsDrone"),Find_Func("CheckEnemyObject",GetOwner())),Find_Distance(200),Find_Hostile(GetOwner()));
	FindStippelTargetDistance(200,this());
}

func Angriff()
{
	if(!GetAlive(victim)) victim = 0;
	if(ObjectDistance(victim,this())>300) victim=0;
	
	if(GetAction() ne "Walk") return(0);
	SetCommand(this(),"MoveTo",victim);
	if(timer>0)//Ladevorgang
	{
		timer--;
		SetCommand(this(),"Wait",0,0,0,0,2);
		return(0);
	}
	if(ObjectDistance(this(),victim)<150)//Nahe genug dran?
		if(PathFree(GetX(),GetY(),GetX(victim),GetY(victim)) && !Contained(victim))//Freie Bahn?
		{
			if(GetX(victim)>GetX()) SetDir(DIR_Right);
			else SetDir(DIR_Left);
			SetAction("Schiess");//Schiessen!
			timer=5;//Warten
		}
	return(1);
}

func Schuss()
{
	var angle=Angle(GetX(),GetY(),GetX(victim),GetY(victim));
	var dir= GetDir()*2-1;
	
	MuzzleFlash(70,this(),15*dir,-2,angle,RGBa(96,64,255,0));
	var ammo=CreateObject(SHT2,18*dir,-4,GetOwner());
	ammo->Launch(angle+RandomX(-1,1),300,600,6,100,12);
	Sound("EnergyRifle",0,ammo);
	return(1);
}

func Bewegung()
{
	if(GetAction() ne "Walk") return(count=0);
	if(x==GetX() && y==GetY())//Kommt vorran?
	{
		count++;
		if(count>5) Jump();//Wenn nicht, dann springen
	}
	else count=0;
	return(1);
}

/*Schadensregulierung*/
func IsBulletTarget(){return(true);}
func Schlagable(){return(1);}

func Hammered(pObj,iStrength)
{
	if(!(GetAction()eq"Tumble" || GetAction()eq"Zappel1" || GetAction()eq"Zappel2" || GetAction()eq"Zappel3" ))
		Punch(this(),iStrength);
	else
	{
		DoEnergy(-iStrength,this());
		OnHit(iStrength,DMG_Melee);
	}
	return(1);
}



func Tumbled()
{
	timer=0;
	return(1);
}

/*Die Zappelaction darf nicht abgebrochen werden*/
func Zappel1Abort(){if(GetAction()eq"Tumble")return(SetAction("Zappel1"));}
func Zappel2Abort(){if(GetAction()eq"Tumble")return(SetAction("Zappel2"));}
func Zappel3Abort(){if(GetAction()eq"Tumble")return(SetAction("Zappel3"));}

func Schadensregulierung()
{
	if(GetAction()eq"Zappel1")
	{
		timer++;
		if(timer>20)
		{
			timer=0;
			SetAction("Zappel3");
		}
	}
	if(GetAction()eq"Zappel3")
	{
		timer++;
		if(timer>10)
		{
			timer=0;
			SetAction("Aufricht");
			damage=0;
		}
	}
}

public func OnDmg(int iDmg, int iType)
{
	if(iType == DMG_Energy)		return(70);
	if(iType == DMG_Bio)		return(100);
	if(iType == DMG_Melee)		return(0);
	if(iType == DMG_Fire)		return(50);
	if(iType == DMG_Explosion)	return(-10);
	
	return(50);
}

public func OnHit(int iDmg, int iType,pFrom)
{
	damage+=iDmg;
	if(!IsVulnerable() && damage>50)
	{
		SetAction("Tumble");
		damage=0;
	}
	if(IsVulnerable()) AlienBlood(RandomX(10,30));
	if((IsVulnerable() && damage>15) || damage>=100)
	{
		AlienBlood(40);
		if(!Random(4)) SetSpeed(RandomX(-5,5),RandomX(-5,5),CreateObject(CPG4,0,0,-1));
		Kill();
	}
	return(CatchBlow(iDmg,pFrom));
}

public func IgnoreFriendlyFire() { return(1); }
public func IsThreat() { return(true); }
func IsVulnerable(){return(GetAction()eq"Zappel1" || GetAction()eq"Zappel2" || GetAction()eq"Zappel3"  || GetAction()eq"Tumble");}
func IsAlien(){return(1);}