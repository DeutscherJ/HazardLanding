#strict

static relaunchNumber, relaunchArray;

func IsChooseable(){return(!FindObject2(Find_Func("IsRelaunchGoal")));}

func Initialize()
{
	relaunchNumber = 10;
	relaunchArray=[];
	for(var i=0; i<=70; i++)
	{
		relaunchArray[i]=relaunchNumber;
	}
	return(1);
}

protected func Activate(iPlr) {
  MessageWindow(GetDesc(),iPlr);
}

func HasChooseMenu(){return(1);}
func RuleCooseMenu(pClonk,selectionNum)
{
	var relaunchObject = FindObject(RLCH);
	if(!relaunchObject) 
		relaunchObject = CreateObject(RLCH,0,0,-1);
	CreateMenu(GetID(), pClonk, relaunchObject, 0, Format("%d Relaunches", relaunchNumber), 0, 1);
	// Spielregeln
	AddMenuItem("$More$", Format("DoSetRelaunchNumber(1,Object(%d),1)",ObjectNumber(pClonk)), CHOS, pClonk, 0,0, "",2,1);
	AddMenuItem("$Less$", Format("DoSetRelaunchNumber(-1,Object(%d),2)",ObjectNumber(pClonk)), CHOS, pClonk, 0,0, "",2,2);
	AddMenuItem("1337", Format("SetRelaunchNumber(1337,Object(%d),3)",ObjectNumber(pClonk)), CTFL, pClonk, 0,0, "");
	AddMenuItem("$None$", Format("SetRelaunchNumber(0,Object(%d),4)",ObjectNumber(pClonk)), CTFL, pClonk, 0,0, "");
	AddMenuItem("$Finished$", Format("Ready(Object(%d))",ObjectNumber(pClonk)), CHOS, pClonk, 0,0, "",2,3);
	if(selectionNum)
		SelectMenuItem(selectionNum-1,pClonk);
	return(1);
}

// Kann mittels des Spielzielauswählers ausgewählt werden
public func SetRelaunchNumber(iSet,pClonk,selectionNum)
{
	relaunchNumber=iSet;
	relaunchArray=[];
	RuleCooseMenu(pClonk,selectionNum);
	for(var i=0; i<=70; i++)
	{
		relaunchArray[i]=iSet;
	}
	return(1);
}
	
public func DoSetRelaunchNumber(iPlus,pClonk,selectionNum)
{
	relaunchNumber += iPlus;
	relaunchNumber = Max(0,relaunchNumber);
	SetRelaunchNumber(relaunchNumber,pClonk,selectionNum);
	return(1);
}

public func Ready(pClonk)
{
	FindObject(CHOS)->~OpenMenu();
	return(1);
}

global func GetRelaunchNumber(iPlr)
{
	return(relaunchArray[iPlr]);
}

global func DoRelaunchNumber(iPlr,iPlus)
{
	relaunchArray[iPlr]+=iPlus;
	return(1);
}

global func AreRelaunchesActive(){return(relaunchNumber>0);}