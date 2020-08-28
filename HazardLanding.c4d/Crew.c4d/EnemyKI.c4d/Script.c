/*-- Ki-Steuerungsobjekt --*/

#strict
local pPuppet, routineArray, routineStep, iMood, targetPosition, maxDist, waitTimer;

static const Mood_Relaxed = 0;
static const Mood_Suspicious = 1;
static const Mood_Alarmed = 2;
static const Mood_Hunting = 3;

func Initialize()
{
	SetOwner(2);
	pPuppet = CreateObject(HZCK,0,0,GetOwner());
	SetColorDw(RGB(255,255,255),pPuppet);
	SetGraphics("Hydro",pPuppet,KSSL);
	SetVisibility(VIS_God());
	//Bewaffnen
	CreateContents(ENWP,pPuppet); 
	CreateContents(ENAP,pPuppet)->~Activate(pPuppet);
	maxDist = 1000;
	LocalN("pKIObject",pPuppet)=this();
	return(1);
}

func OnHit(iDmg,iType,pFrom)
{
	CheckMood(Mood_Hunting,pFrom);
	return(1);
}

func Timer()
{
	LocalN("pKIObject",pPuppet)=this();
	if(!pPuppet) return(RemoveObject()); 
	if(IsSleeping(pPuppet)) return(0);
	if(!GetAlive(pPuppet)) return(RemoveObject());
	SetPosition(GetX(pPuppet),GetY(pPuppet));
	pPuppet->CheckInventory();
    //pPuppet->SetAggroLevel(Aggro_Guard,100,GetX(),GetY());
	
	if(EnemyInViewport()) CheckMood(Mood_Hunting,EnemyInViewport());
	
	//Ist auf der Jagd eines anderen Clonks
	if(iMood == Mood_Hunting)
	{
		Message("<c ff0000>!</c>",pPuppet);
		pPuppet->SetAggroLevel(Aggro_Guard,100,GetX(),GetY());
		return(1);
	}
	//Ist alarmiert?
	if(iMood == Mood_Alarmed)
	{
		Message("<c ffff00>!</c>",pPuppet);
		if(!GetCommand(pPuppet))
		{
			waitTimer--;
			if(waitTimer<=0) ForceMood(Mood_Relaxed);
		}
		return(1);
	}
	//Ist misstrauisch?
	if(iMood == Mood_Suspicious)
	{
		Message("<c ffff00>?</c>",pPuppet);
		SetDir(NumToDir(GetX()-targetPosition[0]));//In die RIchtung der "Bedrohung" drehen
		//SetCommand(pPuppet,"MoveTo",0,targetPosition[0],targetPosition[1]);
		if(!GetCommand(pPuppet))
			ForceMood(Mood_Relaxed);
		return(1);
	}
	
	/*
	var routine = routineArray[routineStep];
	var condition = routine[0];
	var arguments = [];
	for(var i=0;i=9;i++)
	{
		if(GetLength(routine)+2>=i)
			if(!routine[i+2])
				arguments[i]=0;
		else
			arguments[i]=routine[i+2];
	}
	if(routine[1] eq "SetCommand")
		SetCommand(arguments[0],arguments[1],arguments[2],arguments[3],arguments[4],arguments[5],arguments[6],arguments[7],arguments[8],arguments[9]);
	if(routine[1] eq "AddCommand")
		AddCommand(arguments[0],arguments[1],arguments[2],arguments[3],arguments[4],arguments[5],arguments[6],arguments[7],arguments[8],arguments[9]);
	if(routine[1] eq "AppendCommand")
		AppendCommand(arguments[0],arguments[1],arguments[2],arguments[3],arguments[4],arguments[5],arguments[6],arguments[7],arguments[8],arguments[9]);*/
	return(1);
}

func EnemyInViewport()
{
	var dir=GetDir(pPuppet)*2-1;
	for(var pObj in FindObjects(Find_OCF(OCF_Alive),Find_NoContainer(),Find_InRect(-dir*15,-35,dir*300,70),Find_Hostile(GetOwner())))
	{
		if(SeeTarget(pObj)) return(pObj);
	}
	return(0);
}

func SeeTarget(pObj)
{
	if(ObjectDistance(this(),pObj)>maxDist) return(0);
	if(PathFree(GetX(),GetY(),GetX(pObj),GetY())) return(1);
	if(PathFree(GetX(),GetY(),GetX(pObj),GetY()+8)) return(1);
	if(PathFree(GetX(),GetY(),GetX(pObj),GetY()-8)) return(1);
	return(0);
}

func SoundSensitive(){return(1);}
func HearSound(szSound,pObj,iVol,fGlobal,iPlayer,iLoopCount,iKind)
{
	if(GetOwner(pObj)==GetOwner()) return(0);
	Log("%s %d",szSound,iKind);
	if(iKind&SOUND_Blast)
		CheckMood(Mood_Suspicious,pObj);
	if(iKind&SOUND_Attack)
		CheckMood(Mood_Alarmed,pObj);
	if(iKind&SOUND_Hit || iKind&SOUND_Movement)
		CheckMood(Mood_Suspicious,pObj);
	//SetCommand(pPuppet,"MoveTo",0,targetPosition[0],targetPosition[1]);
	//AddCommand(pPuppet,"Wait",0,0,0,0,36);
	return(1);
}

func CheckMood(mood,pObj)
{
	if(mood>iMood)
	{
		if(IsSleeping(pPuppet)==-1) WakeUp(pPuppet);
		targetPosition = [GetX(pObj),GetY(pObj)];
		iMood = mood;
		if(iMood>=Mood_Suspicious)
		{
			SetCommand(pPuppet,"MoveTo",0,targetPosition[0],targetPosition[1]);
			AddCommand(pPuppet,"Wait",0,0,0,0,36);
			routineStep = 0;
		}
		if(iMood>=Mood_Alarmed)
		{
			pPuppet->SetAggroLevel(Aggro_Guard,100,GetX(),GetY());
			routineStep = 0;
		}
		waitTimer=30;
	}
	return(1);
}

func ForceMood(mood)
{
	iMood = mood;
	return(1);
}