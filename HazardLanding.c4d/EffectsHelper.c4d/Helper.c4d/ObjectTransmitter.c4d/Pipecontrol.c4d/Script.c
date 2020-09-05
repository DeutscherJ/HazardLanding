/*-- Pipecontrol --*/

#strict 2

//local pHouseArray, pControl;
local pHouseArray, pOriginalObjects, pCopiedObjects, pLastHouseIDs;
static fDebugRohrpost;

func Initialize()
{
	pHouseArray		=  [];
	pCopiedObjects	= [[]];
	pOriginalObjects=  [];
	pLastHouseIDs	=  [];
	SetVisibility(VIS_God);
	//fDebugRohrpost = 1;
	return(1);
}

//Ein Objekt verlässt dieses Objekt
func EjectionCall(iObjNum,pFrom)
{
	var pObj = Object(iObjNum);
	CheckHouses();
	if(pObj)
		if(pFrom)
			if(Contained(pObj)==pFrom) return(0);//Anscheinend hat das Objekt die Hütte doch nicht verlassen
	if(!pObj)//Wurde das Objekt verkauft oder zerstört?
	{
		if(fDebugRohrpost) Log("Gegenstand %d verkauft",iObjNum);
	}
		
	if(FindInArray(pOriginalObjects,iObjNum))//Handelt es sich um ein Original?
	{
		var iOriginalNum = FindInArray(pOriginalObjects,iObjNum);
		iOriginalNum = iOriginalNum[0];
		if(fDebugRohrpost) Log("Nehme Original %s: %d Originale, %d Kopien",GetName(pObj),GetLength(pOriginalObjects),GetLength(pCopiedObjects));
		DeleteCopies(iOriginalNum);//Dann lösche überall sonst die Kopien
		pOriginalObjects = DeleteRow(pOriginalObjects,iOriginalNum);//Lösche den Verweis aufs Originalobjekt
		if(fDebugRohrpost) Log("Nach dem Löschen: %d Originale, %d Kopien",GetLength(pOriginalObjects),GetLength(pCopiedObjects));
	}
	else//Ansonsten muss es sich wohl um eine Kopie handeln
	{
		var iOriginalRow = SearchOriginalOfCopy(iObjNum);//Suche das entsprechende Original heraus
		//Log("Objekteintrag %d",iOriginalRow);
		if(iOriginalRow==-1) return(1);//Dieses Objekt wurde nie kopiert (z.B. Clonk oder Fahrzeug)
		var iOriginalNum = pOriginalObjects[iOriginalRow];
		var pOriginal = Object(iOriginalNum);
		if(!pOriginal)//Gibt es kein Original? Dann ist irgendwas schief gelaufen
		{
			Message("Gegenstand nicht auffindbar",pFrom);
			Sound("Error");
		}
		
		if(fDebugRohrpost) Log("Nehme Kopie %s: %d Originale, %d Kopien",GetName(pObj),GetLength(pOriginalObjects),GetLength(pCopiedObjects));
		pOriginalObjects = DeleteRow(pOriginalObjects,iOriginalRow);//Lösche den Verweis aufs Originalobjekt
		if(fDebugRohrpost) Log("Nach dem Löschen: %d Originale, %d Kopien",GetLength(pOriginalObjects),GetLength(pCopiedObjects));
		
		Log("Kopie %s , Original %s",GetName(pObj),GetName(pOriginal));
		
		if(pOriginal && pObj)//Ansonsten wird die Kopie mit dem Original ersetzt
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
		if(!pObj && pOriginal)
		{
			Log("Kopie wurde verkauft, lösche originales %s",GetName(pOriginal));
			RemoveObject(pOriginal);
		}
		DeleteCopies(iOriginalRow);//Lösche alle Kopien
	}
	return(1);
}

/*Suche das Original zu einer Kopie*/
func SearchOriginalOfCopy(iCopyNum)
{
	for(var iRow = 0; iRow<GetLength(pCopiedObjects); iRow++)
	{
		for(var iCol = 0; iCol<GetLength(pCopiedObjects[iRow]); iCol++)
		{
			if(pCopiedObjects[iRow][iCol]==iCopyNum) return(iRow);
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
		if(Object(pCopy))
			RemoveObject(Object(pCopy),1);
	}
	return(1);
}
 
//Ein Objekt betritt dieses Objekt
func CollectionCall(iObjNum,pFrom)
{
	var pObj = Object(iObjNum);
	if(Contained(pObj)!=pFrom) return(0);//Anscheinend wurde das Objekt doch nicht aufgenommen
	if(!(GetOCF(pObj)&OCF_Collectible))
		return(0);
	if(GetID(pObj)==GOLD || GetID(pObj)==FLAG)//Flaggen und Gold nehmen einen Sonderstatus ein, weil sie automatisch verkauft oder gehisst werden. Dies soll aber nicht passieren.
	{
		Message("%s wird nicht transportiert.",pFrom,GetName(pObj));
		return(0);
	}
	var i = SearchOriginalOfCopy(iObjNum);
	if(fDebugRohrpost) Log("Aufnahme %d",i);
	if(i==-1)
	{
		//Message("Objekt nicht aufgelistet",pFrom);
		CopyObject(pObj,pFrom);
		if(fDebugRohrpost) Log("%s Aufgenommen in %s",GetName(pObj),GetName(pFrom));
		return(1);
	}
	//Message("Objekt schon aufgelistet",pFrom);
	return(0);//Ist schon aufgenommen
}

func CopyObject(pObj,pFrom)
{
	CheckHouses();
	if(!(GetOCF(pObj)&OCF_Collectible))
		return(0);
	if(GetID(pObj)==GOLD || GetID(pObj)==FLAG)//Flaggen und Gold nehmen einen Sonderstatus ein, weil sie automatisch verkauft oder gehisst werden. Dies soll aber nicht passieren.
	{
		Message("%s wird nicht transportiert.",pFrom,GetName(pObj));
		return(0);
	}
	if(fDebugRohrpost) Log("%s Kopiert in %s",GetName(pObj),GetName(pFrom));
	pOriginalObjects = AddElement(pOriginalObjects,ObjectNumber(pObj)); 
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
			if(!IsArray(pCopiedObjects[iCopiedNum-1]))
				pCopiedObjects[iCopiedNum-1]=[];//Eine Zeile anhängen
			pCopiedObjects[iCopiedNum-1][iHouse]=ObjectNumber(pCopy);//Und speichere einen Eintrag dieser Kopie
		}
	}
	return(1);
}

func AddHouse(pHouse)
{
	pHouseArray=AddElement(pHouseArray,pHouse); //Haus der Liste anhängen
	
	//Alle Objekte in diesem Haus durchgehen und in die bisherigen Häuser kopieren
	for(var i=0; Contents(i,pHouse); i++)
		CopyObject(Contents(i,pHouse),pHouse);
		
	var iHouse = GetLength(pHouseArray)-1; 
	//Und nochmal alle Originalgegenstände durchgehen und ggf. eine Kopie hier anfertigen
	for(var iCopy=0; iCopy<GetLength(pOriginalObjects);iCopy++)
	{
		var pOriginal = Object(pOriginalObjects[iCopy]);
		if(Contained(pOriginal)!=pHouse)//Ist nicht schon das Original im Haus X?
		{
			var pCopy = CreateContents(GetID(pOriginal),pHouse); //Dann erzeuge dort eine Kopie
			if(!IsArray(pCopiedObjects[iCopy]))//Eine Zeile anhängen
				pCopiedObjects[iCopy]=[];
			pCopiedObjects[iCopy][iHouse]=ObjectNumber(pCopy);//Und speichere einen Eintrag dieser Kopie
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

func CheckHouses()
{
	/*Alle Häuser durchgehen und Prüfen ob Sie noch im Normalen Zustand sind*/
	var i=0;
	if(GetLength(pHouseArray)<2) return(0); 
	for(var pHouse in pHouseArray)
	{
		if(!pHouse) return(HouseDeleted(i));//Objekt verschwunden
		if(!pLastHouseIDs[i]) pLastHouseIDs[i]=GetID(pHouse);//ID noch nicht eingespeichert?
		else if(GetID(pHouse)!=pLastHouseIDs[i])return(HouseDeleted(i));//ID gewechselt? / abgebrannt
		i++;
	}
	return(1);
}

func HouseDeleted(int iHouseNum)
{
	if(fDebugRohrpost) Log("Haus %d gelöscht",iHouseNum);
	if(GetLength(pHouseArray)==2) return(Delete());//ist nurnoch ein Haus da?, dann ist es eigentlich kein Rohrpost-Netzwerk mehr, sondern nurnoch ein Haufen Scheiße!
	pHouseArray= DeleteRow(pHouseArray,iHouseNum);//Haus aus dem Array löschen
	pLastHouseIDs= DeleteRow(pLastHouseIDs,iHouseNum);
	var pHouse = pHouseArray[iHouseNum];
	/*Alle Kopien der Originalen löschen, die im Freien, in pHouse oder kaputt sind*/
	var i=-1;
	for(var pObj in pOriginalObjects)
	{
		i++;
		if(!pObj){DeleteCopies(i); continue;}
		else if(!Contained(pObj)){EjectionCall(pObj); continue;}
		else if(Contained(pObj)==pHouse){EjectionCall(pObj);}
	}
	
	/*Alle Kopien löschen die in dem entfernten Haus waren/sind*/
	for(var iCopyRows = 0; iCopyRows<GetLength(pCopiedObjects); iCopyRows++)
	{
		var row = pCopiedObjects[iCopyRows];// Die Einträge in der Matrix speichern
		var backupRow=row;
		row[iHouseNum]=0;
		pCopiedObjects[iCopyRows]=row;//Element löschen
		if(backupRow[iHouseNum])
			RemoveObject(backupRow[iHouseNum],1);
	}
	pCopiedObjects = DeleteCol(pCopiedObjects,iHouseNum);//Spalte aus der Matrix löschen
	
	return(1);
}

//Sämtliche Kopien löschen!
func Delete()
{
	if(fDebugRohrpost) Log("----------Lösche Rohrpost----------");
	for(var iCopyRows = 0; iCopyRows<GetLength(pCopiedObjects); iCopyRows++)
	{
		var row = pCopiedObjects[iCopyRows];
		
		for(var i=0; i<GetLength(row);i++)
		{
			var pObj = row[i];
			//row[i]=0;
			pCopiedObjects[iCopyRows][i]=0;
			if(pObj) RemoveObject(pObj);
		}
	}
	RemoveObject();
	if(fDebugRohrpost) Log("----------Rohrpost gelöscht----------");
	return(1);
}