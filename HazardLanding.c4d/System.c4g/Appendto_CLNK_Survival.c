/*-- Wiederbelebung --*/

#strict

#appendto CLNK
#appendto HZCK

local deadCounter;

func IsBulletTarget(a,b,c,d,e,f)
{
	if(IsDying()) return(0);
	return(_inherited(a,b,c,d,e,f));
}

func Death(a,b,c,d,e,f,g)
{	
	if(RivivalAble() && deadCounter!=16 && GetPlayerType(GetOwner())!=C4PT_Script)
	{
		CreateMenu(RVIV, this(), this());
		// Menüeinträge erzeugen
		//AddMenuItem("Hilfe rufen", "CallHelp",ROCK, this(), 0, 0,"", 4, this())
		AddMenuItem("Hilfe rufen", "CallHelp",SPSH, this(), 0, 0, "Rufe verbündete Clonks nach hilfe um wiederbelebt zu werden.");
		AddMenuItem("Sterben", "WantedDeath",RVIV, this(), 0, 0, "Lasse den Clonk jetzt sofort sterben und warte nicht auf Hilfe.");
		fSpawnProtected=1;
		SetAlive(1);
		DoEnergy(GetEnergy()+10);
		MakeCrewMember(this(),GetOwner());
		SetCursor(GetOwner(),this());
		if(deadCounter==0)
		{
			deadCounter=255;
			Sound("Die");
			//Sound("Tinnitus",1,0,100,GetOwner()+1,1);
			var pObj = CreateObject(DED_,0,0,GetOwner());
			pObj->SetAction("Attach",this());
			ScheduleCall(this(),"DeadTimer",1,1);
		}
	}
	else
	{
		var body = FindObject2(Find_ActionTarget(this()),Find_ID(DED_));
		if(body)
			RemoveObject(body);
	}
	return(_inherited(a,b,c,d,e,f,g));
}
func IsDying(){return(GetAction() eq "Dead" &&(deadCounter!=16));}
func WantedDeath()
{
	deadCounter=16;
	Kill();
	return(1);
}
func ContextRivive()
{
	[Clonk Wiederbeleben|Condition=NearDeadClonk]
	var pClonk = FindNearDeadClonk();
	if(pClonk)
	{
		pClonk->~SetAction("FlatUp",0,0,1);
		DoEnergy(10,pClonk);
		Sound("Cough*");
		//Sound("Tinnitus",1,0,100,GetOwner(pClonk)+1,-1);
		deadCounter=0;
		LocalN("fSpawnProtected",pClonk)=0;
	}
	return(1);
}

func CallHelp()
{
	Sound("Scream");
	Message("Hilfe!",this());
	CreateMenu(RVIV, this(), this());
	// Menüeinträge erzeugen
	AddMenuItem("Hilfe rufen", "CallHelp",SPSH, this(), 0, 0, "Rufe verbündete Clonks nach hilfe um wiederbelebt zu werden.");
	AddMenuItem("Sterben", "WantedDeath",RVIV, this(), 0, 0, "Lasse den Clonk jetzt sofort sterben und warte nicht auf Hilfe.");
	return(1);
}

func FindNearDeadClonk(){return(FindObject2(Find_OCF(OCF_Alive),Find_Action("Dead"),Find_Distance(20)));}
func NearDeadClonk(){return(FindObject2(Find_OCF(OCF_Alive),Find_Action("Dead"),Find_Distance(20))&&GetAction()ne"Dead");}

func DeadTimer()
{
	if(deadCounter==0) return(0);
	if(GetAction() ne "Dead")
	{
		Message("",this());
		return(1);
	}
	if(deadCounter==16)
	{
		Kill(this());
		Message("",this());
		return(1);
	}
	if(GetAlive())
	{
		ScheduleCall(this(),"DeadTimer",2,1);
		deadCounter--;
		Message("<c ff%x%x>!</c>",this(),deadCounter,deadCounter);
	}
	return(1);
}