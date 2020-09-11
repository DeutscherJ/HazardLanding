/*-- HoA Weihnachten --*/

#strict

static iStoryCounter, fInit;
static pCamera, fPlay, iWaitTime, szScene, iSceneStep, iScene, iMidStep, zGoto, pOcin;//Für Interplays

func Wait(int i)
{
	if(!i) i=7;
	if(!iWaitTime)
	{
		iWaitTime=i;
		return(true);
	}
	else iWaitTime--;
	
	if(iWaitTime==1) return(iWaitTime=0);
	return(false);
}
 
func ResetTimer(int i)
{
	iWaitTime=0;
	if(i) goto(i);
	return(1);
}
 
/*Funktionen für die Filme*/
global func Say(szString, pObj, szPortrait, iExcludePlayer, fPermanent)
{
	return(ShoutMsg(szString,pObj, szPortrait, iExcludePlayer, fPermanent));
}

global func ShoutMsg(sMessage, pSpeaker, szPortrait, iExcludePlayer, fPermanent)
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
  // Farbe ermitteln
  var dwClr = pSpeaker->~GetDlgMsgColor();
  if (!dwClr) dwClr = GetColorDw(pSpeaker);
  if (!dwClr) dwClr = 255;
  // Permanent @
  var szPermanent = "";
  if(fPermanent) szPermanent = "@";
  // Message ausgeben
  var obj = GetCursor(GetPlayerByIndex(0, C4PT_User));
  SetComDir(COMD_Stop, obj);
  CreateMenu(GetID(pSpeaker),obj,0,0,Format("<c %x>%s:</c>", dwClr, GetName(pSpeaker)),0,C4MN_Style_Dialog);
  AddMenuItem(szPortrait,0,CNKT,obj,0,0,0,5);
  var szMsg;
  if(GetType(sMessage)==C4V_String)
    AddMenuItem(sMessage,0,NONE,obj);
  else for(szMsg in sMessage) AddMenuItem(szMsg,0,NONE,obj);
  AddMenuItem("$TxtNext$", "ScriptGo(1)", ARR_, obj, 0, obj, 0, 2, 0); 

  ScriptGo(0);
  iExcludePlayer = GetPlayerByIndex(0, C4PT_User)+1;
  var sText = "";
  if(GetType(sMessage)==C4V_String)
    sText = sMessage;
  else for(szMsg in sMessage) sText = Format("%s|%s", sText, szMsg);
  if(iExcludePlayer)
  {
    i = GetPlayerCount(C4PT_User);
    while(i--)
      if(GetPlayerByIndex(i,C4PT_User)!=iExcludePlayer-1) CustomMessage(Format("%s<c %x>%s:</c> %s", szPermanent, dwClr, GetName(pSpeaker), sText), 0, GetPlayerByIndex(i,C4PT_User), 90,70, 0xffffff, MD69, szPortrait, 0);
  }
  else CustomMessage(Format("%s<c %x>%s:</c> %s", szPermanent, dwClr, GetName(pSpeaker), sText), 0, -1, 90,70, 0xffffff, MD69, szPortrait, 0);
}
 /*
 InitFilm(GetCursor(),0,"Drm",2);
 pDuble Clonk der Protagonist der Szene werden soll
 pHeft Objekt an dem die Kamera "geklebt" werden soll
 szName Name der Szene - dieser wird dann im Szenarioscript aufgerufen als S%szName%%i% wobei %i% der Schritt der Storycounter der Szene ist
 */
global func InitFilm(pDuble,pHeft,szName,pGoto)
{
	pOcin=CreateObject(GetID(pDuble),GetX(pDuble),GetY(pDuble)+10,GetOwner(pDuble));
	SetAction(GetAction(pDuble),pOcin);
	SetPhase(GetPhase(pDuble),pOcin);
	SetSpeed(GetXDir(pDuble),GetYDir(pDuble),pOcin);
	SetDir(GetDir(pDuble),pOcin);
	if(!pHeft) pHeft=pOcin;
	pCamera=CreateObject(HPAF,0,0,-1)->AttachTo(pHeft);
	SetVertexXY(0,0,0,pCamera);
	for(var i=0, j=0; GetPlayerCount()>j;i++)
	{
		if(GetPlayerName(i))
		{
			var clonk= GetCrew(i);
			Enter(pCamera,clonk);
			j++;
		}
	}
	szScene=szName;
	iSceneStep=0;
	fPlay=true;
	if(!pGoto) pGoto=28;
	zGoto=pGoto;
	//SetGraphics("",pOcin,CLNK);
	SetName(GetName(pDuble),pOcin);
	goto(2000);
}

global func EndFilm()
{
	if(pOcin)
	{
		for(var i=0, j=0; GetPlayerCount()>j;i++)
		{
			if(GetPlayerName(i)){
				var clonk= GetCrew(i);
				Exit(clonk);
				SetPosition(GetX(pOcin),GetY(pOcin),clonk);
				clonk->SetAction(GetAction(pOcin),GetActionTarget(0,pOcin));
				SetPhase(GetPhase(pOcin),clonk);
				SetSpeed(GetXDir(pOcin),GetYDir(pOcin),clonk);
				SetComDir(GetComDir(pOcin),clonk);
				SetDir(GetDir(pOcin),clonk);
				j++;
			}
		}
		SetCategory(1,pOcin);
		RemoveObject(pOcin);
	}
	if(pCamera) RemoveObject(pCamera);
	fPlay=false;
	ScriptGo(1);
	goto(zGoto);
	return(1);
}
func Script2001()
{
	if(!GameCall(Format("S%s%d",szScene,iSceneStep))&&!iWaitTime)iSceneStep++;
	if(fPlay)goto(2000);
	return(1);
}
/*

func InitializePlayer(iPlr)
{
	if(!fInit)
	{
		fInit=true;
		ScriptGo(1);
		//CreateObjects();
	}
	SetPosition(100,100,GetCursor(iPlr));
	return(1);
}

func Script1()
{
	InitFilm(GetCursor(),0,"Intro");
	return(1);
}

func Script2001()
{
	if(!GameCall(Format("S%s%d",szScene,iSceneStep))&&!iWaitTime)iSceneStep++;
	if(fPlay)goto(2000);
	return(1);
}