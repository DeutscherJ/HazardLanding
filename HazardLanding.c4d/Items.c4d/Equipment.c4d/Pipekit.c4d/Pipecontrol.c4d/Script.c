/*-- Pipecontrol --*/

#strict 2

//local pHouseArray, pControl;
local pHouseArray, pOriginalObjects, pCopiedObjects;

func Initialize()
{
	pHouseArray=[];
	pCopiedObjects=[[]];
	pOriginalObjects=[];
	SetVisibility(VIS_God); 
	return(1);
}

//Ein Objekt verlässt dieses Objekt
func EjectionCall(pObj,pFrom)
{
	if(FindInArray(pOriginalObjects,pObj))//Handelt es sich um ein Original?
	{
		var iObjNum = FindInArray(pOriginalObjects,pObj);
		iObjNum=iObjNum[0];
		//Log("Nehme Original %s: %d Originale, %d Kopien",GetName(pObj),GetLength(pOriginalObjects),GetLength(pCopiedObjects));
		DeleteCopies(iObjNum);//Dann lösche überall sonst die Kopien
		pOriginalObjects=DeleteRow(pOriginalObjects,iObjNum);//Lösche den Verweis aufs Originalobjekt
		//Log("Nach dem Löschen: %d Originale, %d Kopien",GetLength(pOriginalObjects),GetLength(pCopiedObjects));
	}
	else//Ansonsten muss es sich wohl um eine Kopie handeln
	{
		var iOriginalRow = SearchOriginalOfCopy(pObj);//Suche das entsprechende Original heraus
		//Log("Objekteintrag %d",iOriginalRow);
		if(iOriginalRow==-1) return(1);//Dieses Objekt wurde nie kopiert (z.B. Clonk oder Fahrzeug)
		var pOriginal = pOriginalObjects[iOriginalRow];
		if(!pOriginal)//Gibt es kein Original? Dann ist irgendwas schief gelaufen
		{
			Message("Gegenstand nicht auffindbar",pFrom);
			Sound("Error");
		}
		
		//Log("Nehme Kopie %s: %d Originale, %d Kopien",GetName(pObj),GetLength(pOriginalObjects),GetLength(pCopiedObjects));
		pOriginalObjects = DeleteRow(pOriginalObjects,iOriginalRow);//Lösche den Verweis aufs Originalobjekt
		//Log("Nach dem Löschen: %d Originale, %d Kopien",GetLength(pOriginalObjects),GetLength(pCopiedObjects));
		
		if(pOriginal)//Ansonsten wird das Kopie mit dem Original ersetzt
		{
			if(Contained(pObj))//Wurde diese Kopie in ein anderes Objekt versetzt?
				Enter(Contained(pObj),pOriginal);//Dann auch Original dorthin versetzen
			else//Ansonsten mit allen gelichen physikalischen Eigenschaften an die gleiche Stelle setzen
			{
				Exit(pOriginal);
				SetPosition(GetX(pObj),GetY(pObj),pOriginal);
				SetXDir(GetXDir(pObj),pOriginal);
				SetYDir(GetYDir(pObj),pOriginal);
				SetR(GetR(pObj),pOriginal);
				SetRDir(GetRDir(pObj),pOriginal);
			}
		}
		DeleteCopies(iOriginalRow);//Lösche alle Kopien
	}
	return(1);
}

/*Suche das Original zu einer Kopie*/
func SearchOriginalOfCopy(pCopy)
{
	for(var iRow = 0; iRow<GetLength(pCopiedObjects); iRow++)
	{
		for(var iCol = 0; iCol<GetLength(pCopiedObjects[iRow]); iCol++)
		{
			if(pCopiedObjects[iRow][iCol]==pCopy) return(iRow);
		}
	}
	return(-1);
}

func DeleteCopies(int iObjNum)
{
	/*Kopien löschen*/
	var backupRow = pCopiedObjects[iObjNum];// Die Einträge in der Matrix speichern
	pCopiedObjects = DeleteRow(pCopiedObjects,iObjNum);//Zeile aus der Matrix löschen
	for(var pCopy in backupRow)//Anschließend die Gegenstände löschen
	{
		if(pCopy)
			RemoveObject(pCopy,1);
	}
	return(1);
}
 
//Ein Objekt betritt dieses Objekt
func CollectionCall(pObj,pFrom)
{
	if(!(GetOCF(pObj)&OCF_Collectible))
		return(0);
	if(GetID(pObj)==GOLD || GetID(pObj)==FLAG)//Flaggen und Gold nehmen einen Sonderstatus ein, weil sie automatisch verkauft oder gehisst werden. Dies soll aber nicht passieren.
	{
		Message("%s wird nicht transportiert.",pFrom,GetName(pObj));
		return(0);
	}
	var i = SearchOriginalOfCopy(pObj);
	Log("Aufnahme %d",i);
	if(i==-1)
	{
		//Message("Objekt nicht aufgelistet",pFrom);
		CopyObject(pObj,pFrom);
		return(1);
	}
	//Message("Objekt schon aufgelistet",pFrom);
	return(0);//Ist schon aufgenommen
}

func CopyObject(pObj,pFrom)
{
	if(!(GetOCF(pObj)&OCF_Collectible))
		return(0);
	if(GetID(pObj)==GOLD || GetID(pObj)==FLAG)//Flaggen und Gold nehmen einen Sonderstatus ein, weil sie automatisch verkauft oder gehisst werden. Dies soll aber nicht passieren.
	{
		Message("%s wird nicht transportiert.",pFrom,GetName(pObj));
		return(0);
	}
	pOriginalObjects=AddElement(pOriginalObjects,pObj); 
	//Log("A%d | %d",GetLength(pOriginalObjects),GetLength(pHouseArray)); 
	var iHouseCount = GetLength(pHouseArray);
	var iCopiedNum = GetLength(pOriginalObjects); //Anzahl der bereits kopierten Objekte (mit diesem)
	for(var iHouse=0;iHouse<iHouseCount;iHouse++)
	{
		var pHouse = pHouseArray[iHouse];
		if(Contained(pObj)!=pHouse)//Ist nicht schon das Original im Haus X?
		{
			var pCopy = CreateContents(GetID(pObj),pHouse); //Dann erzeuge dort eine Kopie
			//Log("B%d | %d",iCopiedNum-1,iHouse);
			pCopiedObjects[iCopiedNum-1]=[];//Eine Zeile anhängen
			pCopiedObjects[iCopiedNum-1][iHouse]=pCopy;//Und speichere einen Eintrag dieser Kopie
		}
	}
	return(1);
}

func AddHouse(pHouse)
{
	pHouseArray=AddElement(pHouseArray,pHouse); //Haus der Liste anhängen
	
	//Alle Objekte in diesem Haus durchgehen und in die bisherigen Häuser kopieren
	for(var i=0; Contents(i,pHouse); i++)
		CopyObject(Contents(i,pHouse));
		
	var iHouse = GetLength(pHouseArray)-1; 
	//Und nochmal alle Originalgegenstände durchgehen und ggf. eine Kopie hier anfertigen
	for(var iCopy=0; iCopy<GetLength(pOriginalObjects);iCopy++)
	{
		var pOriginal = pOriginalObjects[iCopy];
		if(Contained(pOriginal)!=pHouse)//Ist nicht schon das Original im Haus X?
		{
			var pCopy = CreateContents(GetID(pOriginal),pHouse); //Dann erzeuge dort eine Kopie
			pCopiedObjects[iCopy][iHouse]=pCopy;//Und speichere einen Eintrag dieser Kopie
		}
	}
	LocalN("pObjectTransmitter",pHouse)=this();
	return(1);
}

func ObjectTransmitter2(pHouse)
{
	if(FindInArray(pHouseArray,pHouse))
		return(1);
	return(0);
}
/*

	CopyContents(pHouse);