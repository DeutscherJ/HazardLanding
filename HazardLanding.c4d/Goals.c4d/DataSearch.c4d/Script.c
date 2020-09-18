/*-- Datenbergung --*/

#strict
#include GOAL

func PossibleOptionalGoal(){return(1);}
local isOptional;
static dataCubeArray, iDataCubeCollectionType;

func Destruction()
{
	RemoveAll(_DC1);
	RemoveAll(_DC2);
	RemoveAll(_DC3);
	return(1);
}

protected func Initialize()
{
	SetPosition();
	if(!dataCubeArray)
		dataCubeArray=[5,5,5];
  // Keine Datenwürfel Da?
  if(IsFulfilled())
	CreateDataCubes();
  return(inherited());  
}

func GoalWithLateInit(){return(1);}
	
func LateInit()
{
	RemoveAll(_DC1);
	RemoveAll(_DC2);
	RemoveAll(_DC3);
	CreateDataCubes();
	return(1);
}

/*Konfigurationsmenü*/
func ConfigurableInChooserMenu(){return(1);}
func CooseMenu(pClonk,pChooser)
{
	CreateMenu(GetID(), pClonk, 0, 0, "Anzahl platzierter Stippel", 0, 1);
	var dataCube = [_DC1,_DC2,_DC3];
	for(var i = 0; i<=2; i++ )
	{
		AddMenuItem(Format("%d Mehr %s",dataCubeArray[i],GetName(0,dataCube[i])),    Format("ChangeDatacubeNumber(%d, 1,Object(%d))",i,ObjectNumber(pClonk)), CHOS, pClonk, 0,0, GetDesc(0,dataCube[i]),2,1);
		AddMenuItem(Format("%d Weniger %s",dataCubeArray[i],GetName(0,dataCube[i])), Format("ChangeDatacubeNumber(%d,-1,Object(%d))",i,ObjectNumber(pClonk)), CHOS, pClonk, 0,0, GetDesc(0,dataCube[i]),2,2);
	}
	if(iDataCubeCollectionType==0)
	{
		AddMenuItem("Datenwürfel bergen (aktiv)", Format("ChooseCollectionType(0,Object(%d))",ObjectNumber(pClonk)), SYAC, pClonk, 0,0, "Datenwürfel müssen verkauft oder in Raumschiff gebracht werden.");
		AddMenuItem("Datenwürfel finden (aktivieren) ", Format("ChooseCollectionType(1,Object(%d))",ObjectNumber(pClonk)), SYCC, pClonk, 0,0, "Datenwürfel müssen nur aufgenommen werden.");
	}
	if(iDataCubeCollectionType==1)
	{
		AddMenuItem("Datenwürfel bergen (aktivieren)", Format("ChooseCollectionType(0,Object(%d))",ObjectNumber(pClonk)), SYCC, pClonk, 0,0, "Datenwürfel müssen verkauft oder in Raumschiff gebracht werden.");
		AddMenuItem("Datenwürfel finden (aktiv) ", Format("ChooseCollectionType(1,Object(%d))",ObjectNumber(pClonk)), SYAC, pClonk, 0,0, "Datenwürfel müssen nur aufgenommen werden.");
	}
	AddMenuItem("$Finished$", Format("Ready(Object(%d))",ObjectNumber(pClonk)), CHOS, pClonk, 0,0, "",2,3);
	return(1);
}

func ChooseCollectionType(iType,pClonk)
{
	iDataCubeCollectionType = iType;
	CooseMenu(pClonk);
	SelectMenuItem(6+iType,pClonk);
	return(1);
}

func ChangeDatacubeNumber(iCubeNum,iPlus,pClonk)
{
	dataCubeArray[iCubeNum]+=iPlus;
	CooseMenu(pClonk);
	var menuPos = 1;
	if(iPlus==1) menuPos = 0;
	SelectMenuItem(iCubeNum*2+menuPos,pClonk);
	return(1);
}

func Ready(pClonk)
{
	FindObject(CHOS)->~OpenMenu();
	return(1);
}

public func CreateDataCubes()
{
	var stripeNum = dataCubeArray[0];
	var yStripe = LandscapeHeight() / stripeNum ;
	  
	for(var k=stripeNum;k;k--)
	{
	    var yMax = yStripe * k;
	    var yMin = yStripe * (k-1);
		
		//Weiße Würfel auf der Erde platzieren
		var cube = CreateObject(_DC1,0,0,-1);
		var maxIteration = 100;
		var problemBla = 0;
		while((GetY(cube)>yMax || GetY(cube)<yMin)||problemBla&& maxIteration>0)
		{
			maxIteration--;
			
			SetPosition(RandomX(200,LandscapeWidth()-200),RandomX(yMin,yMax),cube);
			if(GetMaterial(GetX(cube),GetY(cube)) == Material("Wall"))
				PlaceHard(cube,1);
			if(GetMaterial(GetX(cube),GetY(cube)) != Material("Wall"))
				problemBla=1;
			else
				problemBla=0;
		}
	}
	
	/*Wurden Rote oder Grüne Datenwürfel platziert?*/
	if(dataCubeArray[1]+dataCubeArray[2]>=1)
	{
		/*Diese Vornehmlich in Gegenständen verstecken*/
		var containerObjects = FindObjects(Find_OCF(OCF_Container),Find_Not(Find_Func("CheckContents")));
		containerObjects = MixArray(containerObjects);
		containerObjects = TakeElements(containerObjects,Linspace(0,dataCubeArray[1]+dataCubeArray[2]-1));
		
		//Log("%d Objektl",GetLength(containerObjects));
		
		var missingGreens = dataCubeArray[1];
		var missingReds = dataCubeArray[2];
		//Log("%d Würfel",missingGreens+missingReds);
		
		/*Zuerst grüne Datenwürfel in Gegenständen verstecken*/
		while((missingReds+missingGreens)>0 && GetLength(containerObjects)>=1)
		{
			if(missingGreens>0)
			{
				var cube = CreateObject(_DC2,0,0,-1);
				missingGreens--;
			}
			else
			{
				var cube = CreateObject(_DC3,0,0,-1);
				missingReds--;
			}
			Enter(containerObjects[0],cube);
			//Log("%s, C:%s %d",GetName(cube),GetName(containerObjects[0]),ObjectNumber(containerObjects[0]));
			containerObjects = DeleteRow(containerObjects,0);
		}
		//Log("%d Würfel 2",missingGreens+missingReds);
		
		/*Falls dann noch Datenwürfel versteckt werden müssen, diese im freien Platzieren*/
		while((missingReds+missingGreens)>0) 
		{
			if(missingGreens>0)
			{
				var cube = CreateObject(_DC2,0,0,-1);
				missingGreens--;
			}
			else
			{
				var cube = CreateObject(_DC3,0,0,-1);
				missingReds--;
			}
			
			var maxIteration = 100;
			var problemBla = 1;
			var yMin = 30;
			var yMax = LandscapeHeight()-20;
			while((GetY(cube)>yMax || GetY(cube)<yMin)||problemBla&& maxIteration>0)
			{
				maxIteration--;
				
				SetPosition(RandomX(200,LandscapeWidth()-200),RandomX(yMin,yMax),cube);
				if(GetMaterial(GetX(cube),GetY(cube)) == Material("Wall"))
					PlaceHard(cube,1);
				if(GetMaterial(GetX(cube),GetY(cube)) != Material("Wall"))
					problemBla=1;
				else
					problemBla=0;
			}
		}
	}
	
	return(1);
}



public func IsFulfilled()
{
  if(!ObjectCount2(Find_Func("DataCube"))||isOptional) return(1);
  return(0);
}

protected func Activate(iPlayer)
{
  // Erfüllungsstatus ermitteln
  var iMonsters = ObjectCount2(Find_Func("IsStippel")); 
  // Nachricht nach Erfüllung ausgeben
  var positionString = "";
  for(var greenCube in FindObjects(Find_ID(_DC2)))
  {
	  if(Contained(greenCube))
		  positionString = Format("%s, Würfel %d befindet sich in %s",positionString,ObjectNumber(greenCube),GetName(Contained(greenCube)));
	  else
		  positionString = Format("%s, Würfel %d befindet sich im freien.",positionString,ObjectNumber(greenCube));
  }
  if(isOptional)
	var optionalString = "Optionales Ziel. ";
  else
	var optionalString = "";
  return(MessageWindow(Format("%sNoch %d weiße, %d rote und %d grüne Datenwürfel übrig. Die Ortung der grünen Würfel hat ergeben: %s",optionalString,ObjectCount(_DC1),ObjectCount(_DC3),ObjectCount(_DC2),positionString), iPlayer));
}