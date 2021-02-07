/*-- globale Funktionen --*/

#strict
static list;
static enemyObjectsArray;

global func IsArenaScenario()
{
	if(FindObject2(Find_Func("IsArenaGoal")))
		return(1);
	var pChoose = FindObject2(Find_ID(CHOS));
	if(pChoose)
	{
		for(var goalID in LocalN("aGoals",pChoose))
		{
			if(DefinitionCall(goalID,"IsArenaGoal")) return(1);
		}
	}
	return(0);
}

global func IsOpenScenario()
{
	return(!GameCall("IsStationScenario") && !FindObject2(Find_Func("IsArenaGoal")));
}

global func SetEnemyObject(pObj,iPlr)
{
	if(!enemyObjectsArray) enemyObjectsArray=[];
	if(!enemyObjectsArray[iPlr]) enemyObjectsArray[iPlr]=[];
	ControlEnemyObjectArrays(iPlr);
	enemyObjectsArray[iPlr]=AddElement(enemyObjectsArray[iPlr],pObj);
	return(1);
}

global func CheckEnemyObject(iPlr,pObj)
{
	if(!enemyObjectsArray) return(0);
	if(!enemyObjectsArray[iPlr+1]) return(0);
	if(!pObj) pObj = this();
	ControlEnemyObjectArrays(iPlr);
	if(!FindInArray(enemyObjectsArray[iPlr+1],pObj)) return(0);
	return(1);
}

global func ControlEnemyObjectArrays(iPlr)
{
	if(!enemyObjectsArray) return(0);
	if(!enemyObjectsArray[iPlr+1]) return(0);
	var array = enemyObjectsArray[iPlr+1];
	var indAlt = 0, indNeu = 0;
	var newArray = [];
	
	for(var intAlt; indAlt<GetLength(array); indAlt++)
	{
		if(array[indAlt])
		{
			newArray[indNeu]=array[indAlt];
			indNeu++;
		}
	}
	enemyObjectsArray[iPlr+1] = newArray;
	return(1);
}
	
//Die Wahrscheinlichkeit von a aus b, Wenn b nicht gegeben 100 nehmen also Prozent dann
global func BoolRand(a,b)
{
	if(!b) b = 100;
	var r = Random(b)-a;
	if(r<0) return(true);
	else return(false);
}

global func OwnerIsRealPlayer(){return(GetPlayerType(GetOwner(this()))==C4PT_User);}
global func FreePath(pObjFrom)
{
	if(PathFree(GetX(this()),GetY(this()),GetX(pObjFrom),GetY(pObjFrom)))
		return(1);
	return(0);
}

global func ShowTrajectory(xdir,ydir,x,y)
{
	if(!xdir) xdir=GetXDir();
	if(!ydir) ydir=GetYDir();
	if(!x) x=0;//GetX();
	if(!y) y=0;//GetY();
	
	for(var i=0; i<100; i++)
	{
		var posArray = EstimateTrajectory(xdir,ydir,i);
		CreateParticle("PSpark",x+posArray[0],y+posArray[1],0,0,50);
	}
	return(1);
}

global func EstimateTrajectory(xdir,ydir,step)
{
	var g = GetGravity();
	var x = xdir*step/10;
	var y = ydir*step/10+step*step*g/50/20;
	var yDir = ydir+step*g/50;
	return([x,y,xdir,yDir]);
}

global func LogPosSpeed(pObj,iRepeat)
{ 
	if(!pObj)
		pObj=this();
	if(!pObj) return(0);
	var x = GetX();
	var y = GetY();
	var xDir = GetXDir();
	var yDir = GetYDir();
	Log("%d;%d;%d;%d;%d",x,y,xDir,yDir,GetTime());
	if(iRepeat<=0) return(1);
	Schedule(Format("LogPosSpeed(Object(%d),%d)",ObjectNumber(),iRepeat-1),1,1,pObj);
	return(1);
}

/*Liefert ein Array mit allen angesteuerten Clonks*/
global func GetCursors(iPlr)
{
	var cursorArray = []; 
	for(var i = 0; GetCursor(iPlr,i); i++)
	{
		cursorArray[i] = GetCursor(iPlr,i);
	}
	return(cursorArray);
}

global func IsControlled(pObj)
{
	if(!pObj)
		pObj=this();
	return(GetCursor(GetOwner())==pObj);
}

global func InCrew(pObj,iPlr)
{
	if(!pObj)
		pObj=this();
	for(var i=0; GetCrew(iPlr,i);i++)
	{
		if(pObj==GetCrew(iPlr,i)) return(1);
	}
	return(0);
}

/*Vergleicht das Objekt mit dem angegebenen*/
global func IsObject(i)
{
	return(ObjectNumber(i)==ObjectNumber(this()));
}


/*Gibt zurück, ob an dem angegebenen Punkt ein Tunnel ist*/
global func GBackTunnel(int xOffset, int yOffset)
{
  return(FindObject2(Find_AtPoint(xOffset,yOffset),Find_Func("CastlePartRange"))||(GetMaterial(xOffset,yOffset)!=-1&&!GBackSemiSolid(xOffset,yOffset)));
}

global func NumToDir(int i)
{
	return((PosNeg(i)+1)/2);
}

/*Minimiert wert auf -1 und +1*/
global func PosNeg(int i)
{
	if(i>0) return(1);
	if(i<0) return(-1);
	return(0);
}

/*findet feste Bereiche wie z.B. Decken*/
global func FindSolidTop(pObj,offset,factor)
{
  if(!factor) factor = 1;
  if(!pObj) pObj=this();
  for(var y=-5+offset; !GBackSolid(0,y); y-=1*factor)
  {
   if(1>GetY(pObj)+y) break;
   if(LandscapeHeight()<GetY(pObj)+y) break;
  }
  return(y);//höchsten Punkt zurückgeben
}

/*ID des Objektes, welche Als ACtion Target verwendet wird vergleichen*/
global func HasActionTargetID(i)
{
	if(!GetActionTarget())return(0);
	return(GetID(GetActionTarget())==i);
}

/*Standposition*/
global func StandPosition(iX,iY,pClonk)
{
	if(Contained(pClonk)) Exit(pClonk);
	pClonk->SetAction("Walk");
	SetPhase(Random(7),pClonk);
	SetPosition(iX,iY,pClonk);
	return(pClonk);
}

/*Verändert nur den Alphakanal*/
global func SetObjAlpha(byAlpha, pObj)
  {
  var dwClrMod=GetClrModulation(pObj);
  if (!dwClrMod) dwClrMod = byAlpha<<24;
  else dwClrMod = dwClrMod & 16777215 | byAlpha<<24;
  return(SetClrModulation(dwClrMod, pObj));
  }
  

global func Empty(){return(0);}

/*DialogFenster*/
global func DialogBox(pClonk,szTxt,pS,szP)
{
	if(!pS) pS=pClonk;
	var szPortrait=GetDialogPortrait(pS,szP);
	
	CreateMenu(GetID(pS),pClonk,0,0,Format("<c %x>%s:</c>", GetColorDw(pS), GetName(pS)),0,C4MN_Style_Dialog);
	AddMenuItem(szPortrait,0,CNKT,pClonk,0,0,0,5);
	AddMenuItem(szTxt,0,NONE,pClonk);
	AddMenuItem("$TxtNext$","Empty", ARR_, pClonk, 0, pClonk, 0, 2, 0); 
}

global func GetDialogPortrait(pSpeaker,szPortrait)
{
  var id = GetID(pSpeaker);
  // Portrait
  if (!szPortrait) if (!(szPortrait = pSpeaker->~GetMsgPortrait())) szPortrait = "1";
  // Portrait ermitteln
  var c,i,p2="";
  if (GetChar(szPortrait) == GetChar("@"))
  {
    // @Portrait: Aus der Dialog Definition holen
    while (c=GetChar(szPortrait, ++i)) p2 = Format("%s%c", p2, c);
    szPortrait = Format("Portrait:%i::%x::%s", DG69, GetColorDw(pSpeaker), p2);
  }
  else
  {
    // Manche Clonks haben kein eignes Portrait und verwenden Standartportraits
    if(id==ACLK || id==_ACK) id = CLNK;
    if(id==WDSK) id = MAGE;
    // Ansonsten direkt vom Sprecher
    szPortrait = Format("Portrait:%i::%x::%s", id, GetColorDw(pSpeaker), szPortrait);
  }
  return(szPortrait);
}

/*ID des Objektes, welche Als ACtion Target verwendet wird vergleichen*/
global func HasActionTargetID(i)
{
	if(!GetActionTarget())return(0);
	return(GetID(GetActionTarget())==i);
}

/*Standposition*/
global func StandPosition(iX,iY,pClonk)
{
	if(Contained(pClonk)) Exit(pClonk);
	pClonk->SetAction("Walk");
	SetPhase(Random(7),pClonk);
	SetPosition(iX,iY,pClonk);
	return(pClonk);
}


/*Zufallsname*/
global func RandomName()
{
	var i= Random(19);
	if(i == 18) return("Florian");
	if(i == 17) return("Maximilian");
	if(i == 16) return("Oskar");
	if(i == 15) return("Fabian");
	if(i == 14) return("Torben");
	if(i == 13) return("Tobias");
	if(i == 12) return("Philip");
	if(i == 11) return("Manuel");
	if(i == 10) return("Dominik");
	if(i ==  9) return("Heinz");
	if(i ==  8) return("Lukas");
	if(i ==  7) return("Thomas");
	if(i ==  6) return("Nico");
	if(i ==  5) return("Timon");
	if(i ==  4) return("Christian");
	if(i ==  3) return("Sebastian");
	if(i ==  2) return("Helmut");
	if(i ==  1) return("Sven");
	if(i ==  0) return("Tim");
}

//Winkel, xOffset,yOffset, Objekt, Nummer, vergrößung, DrehpunkOffX, DrehpunktOffY
//SetDTRotation(40,-9,5,Ensfried #1019,5,1,0,-5)
global func SetDTRotation (int r, int x, int y, object obj, int i, int s, int xoff, int yoff) {
  var fsin=Sin(r, 1000), fcos=Cos(r, 1000);
  // set matrix values
  SetObjDrawTransform (
    +fcos*s, +fsin*s, (1000-fcos)+ x*1000*s - (fsin*yoff),//*(-(((s+1)/2)-1))
    -fsin, +fcos, (1000-fcos)+y*1000 + fsin*xoff,
    obj,i);
}

//SetGraphics (0,this(),SPER,5,GFXOV_MODE_Base); 
//SetDTRotation2(0,0,0,0,10,90)
	
global func SetDTRotation2(r,x,y,yoff,xoff,r2,s,obj,i)
{
	if(!obj) obj=this();
	if(!s)   s = 1;
	if(!i)   i = 5;
	if(i<0)  i++;
	var fsin2 = Sin(-r-r2, 1000), fcos2 = Cos(-r-r2, 1000);
	var fsin  = Sin( r-r2, 1000), fcos  = Cos( r-r2, 1000);
	// set matrix values
	SetObjDrawTransform (+fcos2*s, +fsin2*s, (-fsin*xoff + fcos*yoff + x*1000*s)*s,
						-fsin2   , +fcos2,     fsin*yoff + fcos*xoff + y*1000,
						obj  ,i);
}

global func IsHostile(iPlr)
{
	return(Hostile(iPlr,GetOwner()) || Hostile(GetOwner(),iPlr) || !FindObject(NOFF));
}

global func AC()
{
  if(Contained())
   if(GetAlive(Contained())) return(0);//lebender Container
  return(1);//toter Container
}

global func ArraySwitch(ar)
{
	var beg = ar[0];
	var bub = ar;
	for(var i=1; i<GetLength(ar); i++)
	{
		bub[i-1]=ar[i];
	}
	bub[GetLength(bub)-1]=beg;
	return(bub);
}

global func ON()
{
	Message("%d",this(),ObjectNumber());
}

global func MakeCondition()
{
	var pObj= CreateObject(CNDT,0,0,-1);
	pObj->~AddCondition(Par(0),Par(1),Par(2),Par(3),Par(4),Par(5),Par(6),Par(7),Par(8),Par(9));
	return(pObj);
}

global func PlusMinus(i)
{
	if(i>0) return(1);
	if(i<0) return(-1);
	return(0);
}

global func Error(str,pClonk)
{
	Sound("Error",1,0,0,GetOwner(pClonk)+1);
	PlayerMessage(GetOwner(pClonk),str,pClonk);
	return(1);
}




global func CastObjects2(Objid, iAmount, iS ,x,y,sHappen,pObj)
{
	for(var i= iAmount; i>0; i--)
	{
		var obj= CreateObject(Objid,x,y,-1);
		SetSpeed(RandomX(-iS,iS),RandomX(-iS,iS),obj);
		if(GetType(pObj)==C4V_String()) ObjectCall(obj,sHappen,this());
		else ObjectCall(pObj,sHappen,obj);
	}
	return(1);
}

global func SetObjAlpha(byAlpha, pObj)
  {
  var dwClrMod=GetClrModulation(pObj);
  if (!dwClrMod) dwClrMod = byAlpha<<24;
  else dwClrMod = dwClrMod & 16777215 | byAlpha<<24;
  return(SetClrModulation(dwClrMod, pObj));
  }

/*Quests*/

/*Nur für diese Szenariostruktur*/
/*Aufgabe setzen*/
global func AddQuest(szName,szMessage)
{
	if(!list) list=[];
	for(var i;list[i];i++)
	{
		list[i]->Point(szName,szMessage);
	}
	Log("Neue Notiz auf Aufgabenzettel");
	return(1);
}

global func GetQuest(szName)
{
	for(var i;list[i];i++)
	{
		if(GetName(list[i]) eq szName) return(LocalN("szMessage",list[i]));
	}
	return(0);
}

global func ChangeQuest(szName,szMessage)
{
	for(var i;list[i];i++)
	{
		list[i]->ChangePoint(szName,szMessage);
	}
	Log("Veränderung auf Aufgabenzettel");
	return(1);
}