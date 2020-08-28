/*-- Datenbergung --*/

#strict
#include GOAL

func PossibleOptionalGoal(){return(1);}
local isOptional;

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
  // Keine Datenwürfel Da?
  if(IsFulfilled())
	CreateDataCubes();
  return(inherited());  
}

public func CreateDataCubes()
{
	var stripeNum = 5;
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
	
	stripeNum = 5;
	yStripe = LandscapeHeight() / stripeNum ;
	for(var k=stripeNum;k;k--)
	{
		var yMax = yStripe * k;
		var yMin = yStripe * (k-1);
		var cube = CreateObject(_DC2,0,0,-1);
		var containerObjects = FindObjects(Find_OCF(OCF_Container),Find_InRect(AbsX(0),AbsY(yMin),LandscapeWidth(),yStripe),Find_Not(Find_Func("CheckContents")));
		Enter(PickRandomFromArray(containerObjects),cube);
	}
	
	stripeNum = 3;
	yStripe = LandscapeHeight() / stripeNum ;
	for(var k=stripeNum;k;k--)
	{
		var yMax = yStripe * k;
		var yMin = yStripe * (k-1);
		var cube = CreateObject(_DC3,0,0,-1);
		var containerObjects = FindObjects(Find_OCF(OCF_Container),Find_InRect(AbsX(0),AbsY(yMin),LandscapeWidth(),yStripe),Find_Not(Find_Func("CheckContents")));
		Enter(PickRandomFromArray(containerObjects),cube);
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