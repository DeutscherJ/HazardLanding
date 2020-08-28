/*-- HoA Weihnachten --*/

#strict

static iStoryCounter, fInit;
static pCamera, fPlay, iWaitTime, szScene, iSceneStep, iScene, iMidStep, zGoto, pOcin;//Für Interplays

func Initialize() {
   
  return(1);
}

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
func SIntro1{Say("Alda guck mal auf den Kaländer! WO ist denn der Tannenbaum alda?",pOcin);}
func SIntro2{Say("Alda wir haben keinen was ist da los?",pOcin);}
func SIntro3{EndFilm();}

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
 
 /*
 InitFilm(GetCursor(),0,"Drm",2);
 pDuble Clonk der Protagonist der Szene werden soll
 pHeft Objekt an dem die Kamera "geklebt" werden soll
 szName Name der Szene - dieser wird dann im Szenarioscript aufgerufen als S%szName%%i% wobei %i% der Schritt der Storycounter der Szene ist
 */
func InitFilm(pDuble,pHeft,szName,pGoto)
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

/*Funktionen für die Filme*/
func Say(szString, pObj, szPortrait, iExcludePlayer, fPermanent)
{
	return(ShoutMsg(szString,pObj, szPortrait, iExcludePlayer, fPermanent));
}

func Script2001()
{
	if(!GameCall(Format("S%s%d",szScene,iSceneStep))&&!iWaitTime)iSceneStep++;
	if(fPlay)goto(2000);
	return(1);
}

func EndFilm()
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