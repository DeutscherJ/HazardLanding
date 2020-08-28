/*-- Sounds können Reaktionen hervorrufen --*/

#strict

static const SOUND_Hit = 1;
static const SOUND_Blast = 2;
static const SOUND_Attack = 4;
static const SOUND_Work = 8;
static const SOUND_Movement = 16;
static const SOUND_Animal = 32;
static const SOUND_Machine = 64;
static const SOUND_Magic = 128;

/*

*/

global func Sound(string szSound, bool fGlobal, object pSoundObj, int iVolume, int iPlayer, int iLoopCount, int iRange)
{
	if(!pSoundObj) pSoundObj=this();
	var iKind = 0;
	if(Substring("Hit",szSound)||"bump" eq szSound)
		iKind = SOUND_Hit;
	if(Substring("Blast",szSound))
		iKind = SOUND_Blast | SOUND_Attack;
	if(Substring("Build",szSound) || Substring("Chop",szSound) || Substring("Dig",szSound) || Substring("Build",szSound))
		iKind = SOUND_Work;
	if(Substring("door",szSound) || Substring("Door",szSound) || Substring("Airlock",szSound))
		iKind = SOUND_Movement;
	if("AssaultRifle" eq szSound || "MiniGun" eq szSound || "Rocket" eq szSound || "EnergyRifle" eq szSound || "Pistol" eq szSound || Substring("Shot",szSound) || Substring("Fire",szSound) || Substring("Flamer",szSound))
		iKind = SOUND_Attack;
	if(Substring("Angriff",szSound))
		iKind = SOUND_Animal|SOUND_Movement|SOUND_Attack;
	if(Substring("Load",szSound))
		iKind = SOUND_Movement;
	if("Click" eq szSound)
		iKind = SOUND_Machine;
	if("Die" eq szSound)
		iKind = SOUND_Movement;
	if(Substring("Magic",szSound))
		iKind = SOUND_Magic;
	
	if(!iRange) iRange = DefaultSoundRange(iKind);
	if(!iVolume) iVolume=100;
	for(var pObj in FindObjects(Find_Func("SoundSensitive",iKind),Find_Distance(iRange)))
	{
		pObj->~HearSound(szSound,pSoundObj,iVolume,fGlobal,iPlayer,iLoopCount,iKind,iRange);
	}
	for(var pObj in FindObjects(Find_Func("SpecialListener",iKind)))
	{
		pObj->~DetectSound(szSound,pSoundObj,iVolume,fGlobal,iPlayer,iLoopCount,iKind,iRange);
	}
	return(_inherited(szSound,fGlobal,pSoundObj,iVolume,iPlayer,iLoopCount));
}

global func DefaultSoundRange(iKind)
{
	var range = 30;
	if(iKind&SOUND_Hit)
		range = Max(range,60);
	if(iKind&SOUND_Blast)
		range = Max(range,400);
	if(iKind&SOUND_Attack)
		range = Max(range,280);
	if(iKind&SOUND_Movement)
		range = Max(range,80);
	if(iKind&SOUND_Work)
		range = Max(range,150);
	if(iKind&SOUND_Animal)
		range = Max(range,120);
	if(iKind&SOUND_Magic)
		range = Max(range,170);
	if(iKind&SOUND_Machine)
		range = Max(range,100);
	return(range);
}

global func SoundTypeName(iKind)
{
	var string = "";
	if(iKind&SOUND_Hit)
		string = Format("%s ","Hit");
	if(iKind&SOUND_Blast)
		string = Format("%s ","Blast");
	if(iKind&SOUND_Attack)
		string = Format("%s ","Attack");
	if(iKind&SOUND_Movement)
		string = Format("%s ","Move");
	if(iKind&SOUND_Work)
		string = Format("%s ","Work");
	if(iKind&SOUND_Animal)
		string = Format("%s ","Animal");
	if(iKind&SOUND_Magic)
		string = Format("%s ","Magic");
	if(iKind&SOUND_Machine)
		string = Format("%s ","Machine");
	return(string);
}