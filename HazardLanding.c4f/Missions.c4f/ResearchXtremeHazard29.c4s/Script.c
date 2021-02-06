/* -- Forschungsstation -- */

#strict

HazardLogs: return(1);

static firstInit, pShuttle;

func FirstInit()
{
	firstInit = 1;
	CreateObject(CHOS,0,0,-1);
	CreateObject(JT5B,0,0,-1);
	CreateObject(REAC,0,0,-1);

	RemoveAll(_DC1);
	RemoveAll(_DC2);
	RemoveAll(_DC3);
	CreateObject(DTBG,0,0,-1);
	
	/*CreateObject(NOFF,0,0,-1);
	CreateObject(KSSL,0,0,-1);
	CreateObject(BFGR,0,0,-1);*/
	
	CreateObject(DARK,0,0,-1);
	return(1);
}

func Initialize()
{
	//CreateObject(MELE);
	//CreateObject(GTDM);
	//for(var pObj in FindObjects(Find_ID(NR3V)))
	//	pObj->Initialize();
	var ObjArray = FindObjects(Find_Func("IsBactatank"));
	for(var pObj in ObjArray)
	{
		var light = pObj->Initialize();
	}
	ScriptGo(1);
	SetSkyParallax(0,25);
	/*var oldSpawn, newSpawn;
	for(oldSpawn in FindObjects(Find_ID(_SPW)))
	{
		newSpawn = oldSpawn->CreateObject(SPNP,0,0,-1);
		CreateContents(Local(0,oldSpawn),newSpawn);
		if(Local(1,oldSpawn)) RemoveObject(Local(1,oldSpawn));
		RemoveObject(oldSpawn);
	}*/
	PowerSupplyOff();
	goto(0);
	return(1);
}
/*
Script1:
  SetGlobal(0,0);
  SetGlobal(1,0);
  SetGlobal(2,0);
  SetGlobal(3,0);
  SetGlobal(4,0);
  SetGlobal(5,10000);
  SetGlobal(6,1);
  SetGlobal(7,0);
  SetGlobal(8,0);
  SetGlobal(9,0);
  SetGlobal(10,1);
  SetGlobal(11,1);
  SetGlobal(12,1);
  SetGlobal(13,1);
  SetGlobal(14,1);
  SetGlobal(15,0);
  SetGlobal(16,0);
  SetGlobal(17,1);
  CreateObject(MEN3,0,0,0);
  Loeschung();
  return(goto(2));

Script2:
  if (FindObject(MEN1)) goto(2);
  
  return(1);

*/
func InitializePlayer(iPlr)
{
  //if(iPlr!=0)CreateObject(MEN2,0,0,iPlr);
  if(!firstInit) FirstInit();
  if(!FindObject(CHOS)) DeployPlayer(iPlr);
  else
  {
	var tim = CreateObject(TIM2, 10, 10, -1);
	GetCrew(iPlr)->Enter(tim);
  }
  
  return(1);
}

func DeployPlayer(iPlr)
{
  // Sound
  Sound("PlayerJoin");

  // Luftabwurf des Clonks
  ForcePosition( GetCrew(iPlr), Random(LandscapeWidth()-40)+20, 10 );
  CreateObject(CFAL,0,0,iPlr)->UseOn(GetCrew(iPlr));
  if(AreRelaunchesActive()) PlayerMessage(iPlr,"Noch %d Relaunches.",GetCrew(iPlr),Global(10+iPlr)-1);

  if(IsDark()) CreateContents(FLSH,GetCrew(iPlr))->~Activate(GetCrew(iPlr));
  return(1);  
}

func LatePlayerInit(iPlr)
{
	if(!pShuttle && FindObject(DTBG))
	{
		var pCrew = GetCrew(iPlr);
		pShuttle = CreateObject(SHTL,RandomX(350,LandscapeWidth()-350),70,iPlr);
		Enter(pShuttle,pCrew);
		pShuttle->~ContainedUpDouble(pCrew);
		pShuttle->~ContainedDown(pCrew);
	}
	else DeployPlayer(iPlr);
	if(ClassSelection())
		ClassSelection()->~ActivateSelection(GetCrew(iPlr));
	return(1);
}

public func RelaunchPlayer(int iPlr, object pCrew, object pKiller, int iTeam)
{
  // Par(0) ist kein gültiger Spieler
  if (!GetPlayerName(iPlr)) return(0);
  if(!AreRelaunchesActive()) return(0);
  //if(!Global(14)) Global(10+Par(0))--;
  if(!GetRelaunchNumber(iPlr)) return(0);
  DoRelaunchNumber(iPlr,-1);
  // Neues Mannschaftsmitglied erschaffen
  var pClonk= CreateObject(HZCK,50,-50,Par(0));
  MakeCrewMember(pClonk,Par(0));
  if(pCrew)
    GrabObjectInfo(pCrew, pClonk);
  SetCursor(Par(0),GetCrew(Par(0)));
  // Meldung
  Log("%s hat noch %d Relaunches",GetPlayerName(Par(0)),GetRelaunchNumber(iPlr));
  /*Schlimme Lage?*/
  /*if(GetWealth(iPlr)>150)
  {
	if(GetWealth(iPlr)>150)CreateContents(PIWP,pClonk);
	if(GetWealth(iPlr)>250)CreateContents(PGWP,pClonk);
	CreateContents(STAP,pClonk)->Activate(pClonk);
	CreateContents(ENAP,pClonk)->Activate(pClonk);
	CreateContents(GRAP,pClonk)->Activate(pClonk);
	CreateContents(GSAP,pClonk)->Activate(pClonk);
  }*/
  if(ClassSelection())
	  ClassSelection()->~ActivateSelection(pClonk);
  // Neustarten
  DeployPlayer(Par(0));
  return(1);
}

global func DarknessTest()
{
	CreateObject(DARK);
	FindObject(_GEN)->SetAction("Work");
	GameCall("PowerSupplyOn");
	return(1);
}

func PowerSupplyOn()
{
	for(var pLights in FindObjects(Find_Func("IsLamp")))
	{
		pLights->~Initialize();
		pLights->~TurnOn();
	}
	return(1);
}

func PowerSupplyOff()
{
	for(var pLights in FindObjects(Find_Func("IsLamp")))
	{
		pLights->~TurnOff();
	}
	return(1);
}

MainEnergySupply:
  return(GetAction(FindObject(_GEN))eq"Work");

Rain:
  return(Global(0));

func Loeschung()
{
	/*
	MB5B Miffelbaum
	KG5B Königin
	ST5B Stippel
	MF5B Moff
	*/
	stippelArray=[];
	var StippelIDs = [MB5B,KG5B,ST5B,MF5B];
	for(var i=0; i<GetLength(StippelIDs);i++)
	{
		var k = 0;
		var positionArray = [];
		for(var stippel in FindObjects(Find_ID(StippelIDs[i])))
		{
			positionArray[k] = [GetX(stippel),GetY(stippel)];
			RemoveObject(stippel);
			k++;
		}
		stippelArray[i] = positionArray;
	}
	return(1);
}

func Neuerstellung()
{
	var StippelIDs = [MB5B,KG5B,ST5B,MF5B];
	var StippelNumMax = [1338,1,1337,1337];
	var deleteProb = [30,0,10,10];
	//Alle StippelIDs durchgehen
	for(var i=0; i<GetLength(stippelArray);i++)
	{
		var stippelID = StippelIDs[i];
		var stippelPosMatrix = stippelArray[i];
		stippelPosMatrix = MixArray(stippelPosMatrix);
		var maxLen = Min(GetLength(stippelPosMatrix),StippelNumMax[i]);//Wieviele Stippel einer Sorte sollen platziert werden?
		stippelPosMatrix = TakeElements(stippelPosMatrix,Linspace(0,maxLen-1));//Nur diese Anzahl abschneiden
		
		for(var k=0; k<GetLength(stippelPosMatrix);k++)//Alle Listen durchgehen
		{
			var propability = Random(100);
			if(propability>=deleteProb[i])
			{
				var stippel = CreateObject(StippelIDs[i],300,300,-1);
				var pos = stippelPosMatrix[k];
				SetPosition(pos[0],pos[1],stippel);
			}
		}
	}
	return(1);
}
func IsStationScenario(){return(1);}
//stippelArray=[[[12,10],[123,123]],[123,123]]