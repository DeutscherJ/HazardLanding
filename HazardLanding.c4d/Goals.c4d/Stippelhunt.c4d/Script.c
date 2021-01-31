/*-- Stippeljagd --*/

#strict
#include GOAL

local isOptional;
func SetOptional(){return(isOptional=1);}
func PossibleOptionalGoal(){return(1);}

static stippelArray, stippelNumArray, deletedStippel;

/*
MB5B Miffelbaum
KG5B Königin
ST5B Stippel
MF5B Moff
SK5B Kokon
AS5B Alphastippel
*/
//stippelArray=[];
//var StippelIDs = [MB5B,KG5B,ST5B,MF5B,SK5B,AS5B];//SK5B
func ConfigurableInChooserMenu(){return(1);}
	
func CooseMenu(pClonk,pChooser)
{
	CreateMenu(GetID(), pClonk, 0, 0, "Anzahl platzierter Stippel", 0, 1);
	var StippelIDs = [MB5B,KG5B,ST5B,MF5B,SK5B,AS5B];
	for(var i = 0; i<=5; i++ )
	{
		AddMenuItem(Format("%d Mehr %s",stippelNumArray[i],GetName(0,StippelIDs[i])),    Format("ChangeStippelNumber(%d, 1,Object(%d))",i,ObjectNumber(pClonk)), CHOS, pClonk, 0,0, "Erhöhe platzierte Anzahl",2,1);
		AddMenuItem(Format("%d Weniger %s",stippelNumArray[i],GetName(0,StippelIDs[i])), Format("ChangeStippelNumber(%d,-1,Object(%d))",i,ObjectNumber(pClonk)), CHOS, pClonk, 0,0, "Senke platzierte Anzahl",2,2);
	}
	AddMenuItem("$Finished$", Format("Ready(Object(%d))",ObjectNumber(pClonk)), CHOS, pClonk, 0,0, "",2,3);
	return(1);
}

func ChangeStippelNumber(iStippelNum,iPlus,pClonk)
{
	stippelNumArray[iStippelNum]+=iPlus;
	CooseMenu(pClonk);
	var menuPos = 1;
	if(iPlus==1) menuPos = 0;
	SelectMenuItem(iStippelNum*2+menuPos,pClonk);
	return(1);
}

func Ready(pClonk)
{
	FindObject(CHOS)->~OpenMenu();
	return(1);
}

public func Initialize()
{
	stippelNumArray = [1,1,15,3,5,1];
	if(FindObject(CHOS))
	{
		if(FindObject2(Find_Func("IsStippel")))
		{
			deletedStippel = 1;
			Loeschung();
		}
	}
	else
	{
		if(!FindObject2(Find_Func("IsStippel")))
			PlaceStippel();
	}
	return(1);
}

func LateInit()
{
	//if(!deletedStippel)
	//	Neuerstellung();
	//else
		PlaceStippel();
	return(1);
}

func PlaceStippel()
{
	var StippelIDs = [MB5B,KG5B,ST5B,MF5B,SK5B,AS5B];
	for(var i=0; i<GetLength(StippelIDs);i++)
	{
		for(var j = stippelNumArray[i]; j ;j--)
		{
			var gutePos = 0;
			var stippel = CreateObject(StippelIDs[i],100,100,-1);
			while(!gutePos)
			{
				var x = RandomX(100,LandscapeWidth()-100);
				var y = RandomX(100,LandscapeHeight()-100);
				SetPosition(x,y,stippel);
				PlaceHard(stippel);
				gutePos = 1;
				if(GameCall("IsStationScenario"))//Ist es eine Station?
				{
					for(var iVertex = GetVertexNum(stippel); iVertex; iVertex--)//Alle Vertices in Wall?
					{
						if(stippel->GetMaterial(GetVertex(iVertex-1),GetVertex(iVertex-1,1)) != Material("Wall"))
						{
							gutePos = 0;
							break;
						}
					}
					var pos = FindSolidInAngle(GetX(stippel),GetY(stippel));
					if(GetMaterial(AbsX(pos[0]),AbsY(pos[1])+2) != Material("Wall"))//Gibt es eine Decke?
						gutePos = 0;
				}
				if(Stuck(stippel))
					gutePos = 0;
				if(stippel->GBackSemiSolid(0,-8))
					gutePos = 0;
			}
		}
	}
	return(1);
}

public func IsFulfilled()
{
  if((!ObjectCount2(Find_Func("IsStippel"))||isOptional) && !FindObject(CHOS)) return(1);
  return(0);
}

protected func Activate(iPlayer)
{
  // Erfüllungsstatus ermitteln
  var iMonsters = ObjectCount2(Find_Func("IsStippel"));
	// Nachricht nach Erfüllung ausgeben
	if(isOptional)
		return(MessageWindow(Format("Optionales Ziel. Noch %d Stippel übrig.",iMonsters), iPlayer));
	else
		return(MessageWindow(Format("Noch %d Stippel übrig.",iMonsters), iPlayer));
}


func Loeschung()
{
	/*
	MB5B Miffelbaum
	KG5B Königin
	ST5B Stippel
	MF5B Moff
	*/
	stippelArray = [];
	var StippelIDs = [MB5B,KG5B,ST5B,MF5B,SK5B,AS5B];
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

func GoalWithLateInit(){return(1);}