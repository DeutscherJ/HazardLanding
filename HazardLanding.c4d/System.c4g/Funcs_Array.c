/*-- Weitere Funktionen zum besseren Arbeiten mit Arrays --*/

#strict

//Lösche eine Zeile einer Matrix
global func DeleteRow(oldAr,iLine)
{
	var newAr=[], j=0;
	for(var i=0;i<GetLength(oldAr);i++)
	{
		if(i!=iLine)
		{
			newAr[j]=oldAr[i];
			j++;
		}
	}
	return(newAr);
}
//Lösche eine Spalte einer Matrix
global func DeleteCol(oldAr,iCol)
{
	var newAr=[];
	for(var iRow=0;iRow<GetLength(oldAr);iRow++)//Zeilen durchgehen
	{
		var oldRow = oldAr[iRow];
		var newRow=[],j=0;
		
		for(var k=0;k<GetLength(oldRow);k++)//Spalten durchgehen
		{
			if(k!=iCol)//Spaltenelemente übernehmen solange sie nicht gelöscht werden sollen
			{
				newRow[j]=oldRow[k];
				j++;
			}
		}
		newAr[iRow]=newRow;
	}
	return(newAr);
}

/*- Erstelle ein Array und fülle es mit Objekten der angegebenen Kategorie und OCF -*/
// Beispiel FillArray(C4D_Object,["Collectible","Rebuy"],0,5) 
// Beispiel FillArray(C4D_Object,"Collectible",0,1) 
global func FillArray(wantedCategory, wantedOCF, wantedFunc, maxVal)
{
	var def;
	var arrayOut = [];
	var i = 0, j=0, def = 0;
	
	// loop through all definitions of wanted type
	while (def = GetDefinition(i++, wantedCategory))
	{
		var okOCF = 1;
		if(GetType(wantedOCF)==C4V_String)//Wird ein Array angegeben oder
		{
			if(!GetDefCoreVal(wantedOCF,"DefCore",def))
				okOCF=0;
		}	
		else
		{
			for(str in wantedOCF)
			{
				if(!GetDefCoreVal(str,"DefCore",def))
					okOCF=0;
			}
		}
		if(!okOCF) continue;
		
		// and wanted additional condition
		if(!maxVal || GetValue(,def)<=maxVal)
		{
			//Log("%d |d %d",GetValue(,def),maxVal);
			if (!wantedFunc)
			{
				arrayOut[j]=def;
				j++;
			}
			else
			{
				if(eval(Format(wantedFunc, def)))
				{
					arrayOut[j]=def;
					j++;
				}
			}
		}
	}
	return(arrayOut);
}

//Gibt den kleinsten Wert eines Arrays aus
global func MinArray(arrayP,boolArrayOut)
{
	var minVal = 1000000;
	var minIndex = -1337;
	var indexCounter = 0;
	for(var i in arrayP)
	{
		if(minVal>i)
		{
			minVal = i;
			minIndex = indexCounter;
		}
		indexCounter ++;
	}
	if(boolArrayOut) return([minVal,minIndex]);
	return(minVal);
}

//GIbt den größten Wert eines Arrays aus
global func MaxArray(arrayP,boolArrayOut)
{
	var maxVal = -1000000;
	var maxIndex = -1337;
	var indexCounter = 0;
	for(var i in arrayP)
	{
		if(maxVal<i)
		{
			maxVal = i;
			maxIndex = indexCounter;
		}
		indexCounter ++;
	}
	if(boolArrayOut) return([maxVal,maxIndex]);
	return(maxVal);
}

//Gibt ein Array mit Werten zwischen min und max aus
global func Linspace(min,max)
{
	var count = 0;
	var space = [];
	for(var i = Min(min,max); i<=Max(min,max); i++)
	{
		space[count] = i;
		count++;
	}
	return(space);
}

//Bewerte die Objekte in einem Array nache inem ebstimmten Kriterium und gebe das beste wieder
//PickFromObjectArray(FindObjects(Find_ID(RM01)),"%s->~Len()","Max")
//PickFromObjectArray(FindObjects(Find_ID(RM01)),"GetX(%s)","Min")
global func PickFromObjectArray(ar, func, minmax)
{
	if(!minmax) minmax = "Max";
	var bestValue = 0;
	var bestObj = ar[0];
	bestValue = eval(Format(func,Format("Object(%d)",ObjectNumber(ar[0]))));
	for(var pObj in ar)
	{
		var objValue = 0;
		objValue = eval(Format(func,Format("Object(%d)",ObjectNumber(pObj))));
		if(minmax eq "Max" && bestValue < objValue)
		{
			bestValue = objValue;
			bestObj = pObj;
		}
		if(minmax eq "Min" && bestValue > objValue)
		{
			bestValue = objValue;
			bestObj = pObj;
		}
	}
	return(bestObj);
}

/*Erzeugt Array mit zufälligen Indizes, die sich nicht wiederholen*/
global func RandomArray(len)
{
	var randInds = [];
	for(var i=0; i<len; i++)
	{
		var randInd = Random(len);
		randInds[i] = randInd;
		while(GetLength(FindInArray(randInds,randInd))>1) 
		{
			randInd = Random(len);
			randInds[i] = randInd;
		}
	}
	return(randInds);
}

/*Holt aus einem Array die ELemente mit den Indizes, welche in einem anderen gegebenen Array stehen*/
global func TakeElements(ar,inds)
{
	var outArray = [];
	for(var i=0; i<GetLength(inds); i++)
	{
		outArray[i] = ar[inds[i]];
	}
	return(outArray);
}

//Mischt das gegebene Array durch
global func MixArray(ar){return(TakeElements(ar,RandomArray(GetLength(ar))));}

//Suche bestimmte Werte in einem Array und gebe Indizes wieder
global func FindInArray(ar,val)
{
	var indsOut = [];
	var count = 0;
	for(var i=0; i<GetLength(ar); i++)
	{
		if(GetType(val)==C4V_String)
		{
			if(Substring(val,ar[i]))
			{
				indsOut[count]=i;
				count++;
			}
		}
		else
		{
			if(ar[i]==val)
			{
				indsOut[count]=i;
				count++;
			}
		}
	}
	if(count==0) return(0);
	return(indsOut);
}

global func PickRandomFromArray(ar){return(ar[Random(GetLength(ar))]);}

global func ArraySize(ar,dim)
{
	if(dim==1) return(GetLength(ar));
	if(dim==2) return(GetLength(ar[0]));
}

global func IsArray(ar)
{
	if(GetType(ar) == C4V_Array) return(1);
	return(0);
}

global func AddElement(ar,pElement)
{
	ar[GetLength(ar)]=pElement;
	return(ar);
}