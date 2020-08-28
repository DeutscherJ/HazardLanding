/*-- Forschungstürme Xtreme --*/

#strict

static relaunchPosX, relaunchPoxY, fFirstInit;

func Initialize()
{
	relaunchPosX = 789;
	relaunchPoxY = 10962;
	HideLight();
	//CreateRain();
	for(pObj in FindObjects(Find_Func("IsGate")))
	{
		pObj->~UpdateTransferZone();
	}
	return(1);
}

func CreateRain()
{
	for(var paralax in [80,100])
	{
		for(var x = 400; x<=LandscapeWidth(); x+=800)
		{
			for(var y = 300; y<=LandscapeHeight(); y+=600)
			{
				var rain = CreateObject(RNG4,x,y,-1);
				//SetClrModulation(RGB(180,180,255),rain);
				SetClrModulation(RGBa(255,255,255,10),rain);
				Local(0,rain)=paralax;
				Local(1,rain)=paralax;
			}
		}
	}
	RainColor(RGBa(150,150,255,10),RGBa(200,200,255,100));
	return(1);
}

global func HideLight()
{
	for(var pObj in FindObjects(Find_Or(Find_ID(LIGH),Find_ID(LGHC))))
	{
		SetPosition(10,10,pObj);
	}
	return(1);
}

func InitializePlayer(iPlr)
{
	var pClonk = GetCrew(iPlr);
	CreateContents(PKG4,pClonk);
	SetPosition(relaunchPosX,relaunchPoxY,pClonk);
	SetHostility(iPlr,2,1,1);
	SetHostility(2,iPlr,1,1);
	if(!fFirstInit)
	{
		CreateRain();
		fFirstInit=1;
	}
	if(ClassSelection()) ClassSelection()->~ActivateSelection(pClonk);
	return(1);
}

func PowerSupplyOn()
{
	return(1);
}
func PowerSupplyOff()
{
	return(1);
}

func MainEnergySupply()
{
	var generator = FindObject(_GEN);
	if(generator)
		if(GetAction(generator) eq "Work")
			return(1);
	return(0);
}

/*
	deko= CreateObject(CLNK,371,419,-1);
	SetDir(DIR_Left,deko);
	SetName("Nerox",deko);
	x= CreateObject(TLKR,0,0,-2)->Set(deko,2);
	Local(0,x)=["Hallo alda",-1];
	Local(1,x)=["Moin!",0,"2"];
	Local(2,x)=["Was machst du hier?",-1];
	Local(3,x)=["Ich habe gerade den Typen da unten mit Scheiße beworfen, aber jetzt ist meine scheiße leider Alle",0,"2"];
	Local(4,x)=["Was ist das denn für einer und wieso bewirfst du ihn mit Scheiße?",-1];
	Local(5,x)=[Format("Der Typ heißt %s und er findet Computerspiele moralisch verwerflich, in denen man sieht wie jemand einen geblasen bekommt",GetName(pWichser)),0,"2"];
	Local(6,x)=["Was für ein Lutscher",-1];
	Local(7,x)=["Ja Man sag ich doch! Bist du dabei ihn mit Scheiße zu bewerfen?",0,"2","FragDabei"];
	Local(8,x)=["Ne hab ich gerade nicht so Lust zu... ein anders mal vielleicht",-1,];
	Local(11,x)=["Ja man! Wie kann man so einen Lutscher nur nicht mit Scheiße bewerfen?!",-1];
	Local(12,x)=["Hier hast du scheiße! Leg los!",0,"2"];
	
func Script1()
{
	if(fDream)
	{
		InitFilm(GetCursor(),0,"Drm",2);
		CreateObject(FLYR)->Set(PDBR);
	}
}

func Script3(){if(GetAction(GetCrew(0))eq"Dead") goto(2);}
func Script4()
{
	DialogBox(GetCrew(0),"Scheiße Man!|Ich habe voll den Kater!Und diese Scheiß Blagen vom Sportplatz haben mich geweckt! Das werden sie bereuen!|Und ich hab nur noch ein Bier? Kacki Kack! Ich muss neues besorgen!");
	AddQuest("Bier","-Bier besorgen");
	AddQuest("Kinder","-Kinder töten");
	goto(26);
}

func Script30()
{
	var clonk;
	if(clonk= Contents(0,FindObject2(Find_ID(DIXI),Find_InRect(650-20,410-20,650+40,410+40))))
	{
		iWait--;
		if(iWait=-15)
		{
			Exit(clonk,650-4,410+50);
			Message("Scheiße!!!",clonk);
			Schedule("Message(\"Wie ist das jetzt passiert?\",this())",100,0,clonk);
			Schedule("Message(\"Naja wollte immer schon mal wissen wies hier unten aussieht.\",this())",150,0,clonk);
			clonk->SetAction("Tumble");
			iWait=0;
		}
	}
	if(!iScene)
	{
		if(clonk= FindObject2(Find_InRect(795,310+50,100,130-50),Find_ID(FIGR)))
		{
			InitFilm(clonk,pKahlet,"Beg");
			iScene=1;
			iMidStep=0;
		}
	}
	if(iScene==1)
	{
		if(iMidStep==10)Message("Kommen wir zurück zu dem Bimbo gerade...",pKahlet);
		if(iMidStep==14)Message("Was soll das immer?",pKahlet);
		if(iMidStep==16)Message("Was?",pJoerg);
		if(iMidStep==18)Message("Dass du mich immer beleidigst!",pKahlet);
		if(iMidStep==21)Message("Ich kann Bimbos halt nicht leiden",pJoerg);
		if(iMidStep==23)Message("Tut mir leid",pJoerg);
		if(iMidStep==26)Message("Und ich kann Nazis nicht leiden",pKahlet);
		if(iMidStep==28)Message("Pech für dich",pJoerg);
		if(iMidStep==30)Message("Ne Pech für dich!",pKahlet);
		if(iMidStep==32){Message("Ne Pech für dich!",pJoerg);iMidStep=29;}
	}
	if(!fPad)
	{
		if(clonk= FindObject2(Find_InRect(3128,790,3347-3128,880-790),Find_OCF(OCF_Alive)))
		{
			InitFilm(clonk,pBrauer,"PFab");
			Message("Alda! Das ist die Paderborner Fabrik!",pOcin);
			SetCommand(pOcin,"MoveTo",0,GetX(pOcin)+20,GetY(pBrauer)+10);
			fPad=true;
		}
	}
	if(!ObjectCount2(Find_ID(SCR_))&&!fKidsKilled)
	{
		fKidsKilled=true;
		ChangeQuest("Kinder","-Kinder töten<c ff0000>X");
	}
	var pObj;
	if(pObj=FindObject2(Find_Func("HasActionTargetID",KSTN))&&!fGotBeer)
	{
		ChangeQuest("Bier","-Bier besorgen<c ff0000>X");
		Sound("Trumpet",1);
		fGotBeer=1;
	}
	if(fGarfQ==1)
	{
		if(ObjectCount2(Find_InRect(3330-200,320,3410-3330+200,379-320),Find_Func("ImArsch"))==2)
		{
			InitFilm(FindObject2(Find_InRect(3330-200,320,3410-3330+200,379-320),Find_OCF(OCF_Alive)),pGarfield,"2LSD");
			fGarfQ=2;
		}
	}
	iMidStep++;
	if(fTookLSD && !pSkyChanger)return(StartLSDWelt());
	if(fTookLSD)				TimerLSDWelt();
	if(pSkyChanger && !fTookLSD)return(StopLSDWelt());
	if(!fPlay)goto(28);
}
func Talker(pClonk,pObj)
{
	if(pObj==pGarfield)
	{
		if(fGarfQ==2)
		{
			Message("Ein Ameisenhaufen als Stuhl",pGarfield);
			Schedule(Format("Message(\"Meine Eltern finden keinen Sinn\",Object(%d))",ObjectNumber(pGarfield)),50+Random(20),1);
			return(1);
		}
		if(fGarfQ==1) return(0);
		fGarfQ = 1;
		InitFilm(pClonk,pGarfield,"1LSD");
	}
}
