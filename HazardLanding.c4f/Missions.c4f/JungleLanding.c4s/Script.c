/*-- Alien Invasion --*/

#strict

static alliedIndians, boolFunk, iStory;

//SetClrModulation(RGB(200,255,200))
func Initialize()
{
  //if(!FindObject(JUNS)){CreateObject(JUNS);CreateObject(JUNS);CreateObject(JUNS);}
  FindObject(BDST)->Initialize();
  FindObject(DTBG)->SetMissionAccess("JungleMist");
  
  RemoveAll(CICA);
  CreateObject(CICA);
  CreateObject(CICA);
  
  RemoveAll(JUNS);
  RemoveAll(OWL1);
  CreateObject(OWL1);
  
  RemoveAll(BRDS);
  CreateObject(BRDS);
  CreateObject(BRDS);
  
  //for(var rocks in FindObjects(Find_NoContainer()))
//	  SetPosition(GetX(rocks)+900,GetY(rocks),rocks);
  
  Local(1,FindObject(TIME))=5000;
  for(var rocks in FindObjects(Find_Or(Find_ID(ROCK),Find_ID(VINE))))
	  rocks->~Initialize();
	  
  for(var rocks in FindObjects(Find_ID(MF5B)))
  {
	rocks->CreateObject(MF5B,0,0,-1);
	RemoveObject(rocks);
  }
  ScriptGo(1);
  return(1);
}

func Script130()
{
    FindObject(DTBG)->SetMissionAccess("JungleMist");
	Log("Unterstützungskapsel eingetroffen");
	Sound("Bip3");
	var capsule = CreateObject(SCA2,1149+900,988,-1);
	CreateContents(MEDI,capsule);
	CreateContents(PGWP,capsule,3);
	CreateContents(STAP,capsule,3);
}

/*
func Script5()
{
	Log("<Kommandozentrale> Alder Jungs was ist da bei euch passiert?");
	Sound("Bip3");
	return(1);
}

func Script15()
{
	Log("<Kommandozentrale> Ich hab nur so ein Feuerball gesehen Junge und jetzt ist das Signal weg");
	Sound("Bip3");
	return(1);
}

func Script35()
{
	Log("<Kommandozentrale> Kommandozentrale an Landungseinheit, bekommt ihr diese Nachrichten?");
	Sound("Bip3");
	return(1);
}

func Script55()
{
	Log("<Kommandozentrale> Bekommt ihr diese Nachrichten, dann antwortet jetzt mit euren Geräten über /cmd \"Nachricht\".");
	Sound("Bip3");
	AddMsgBoardCmd("cmd","KommandoNachricht(%s)",true);
	iStory = 1;
	ScriptGo(0);
	return(1);
}
func Script70()
{
	Log("<Kommandozentrale> Wartet da wir holen euch raus! Bringt euch erstmal in Sicherheit.");
	Sound("Bip3");
}
func Script90()
{
	Log("<Kommandozentrale> Wäre nur ganz nice wenn ihr eine Kommunikationsantenne aufstellen könntet, damit wir euch finden können.");
	Sound("Bip3");
}
func Script110()
{
	Log("<Kommandozentrale> Ach und wenn ihr schon dabei seid, dann sucht dann gleich noch nach den Datenwürfeln, für die ihr ja eigentlich gekommen seid.");
	Sound("Bip3");
}
func Script130()
{
	Log("<Kommandozentrale> Wir versuchen euch mal mit ein Paar Sonden proviant zukommen zu lassen. Hoffentlich kommen die bei euch an!");
	Sound("Bip3");
	var capsule = CreateObject(SCA2,1149+900,988,-1);//Erste
	CreateContents(CNKT,capsule,3);
	var flag = CreateContents(FLAG,capsule);
	SetOwner(0,flag);
	CreateContents(MEDI,capsule);
	CreateContents(PGWP,capsule,3);
	CreateContents(STAP,capsule,3);
	CreateDataDisc(capsule,SDWU,SFDY,SLD1);
}

func Script132()
{
	Log("*Kommandozentrale schickt eine Raumsonde.*");
	Sound("Bip3");
}
func Script400()
{
	Log("<Kommandozentrale> Yorda Yorda, ich glaube ihr könntet noch ein Paar Mehr Baupläne gebrauchen oder?");
	Sound("Bip3");
}

func Script450()
{
	var capsule = CreateObject(SCA2,1149+900,354,-1);//692+900,354,-1);
	CreateDataDisc(capsule,SMFC,SPMP,SWEG);
	CreateDataDisc(capsule,SWEF,RADR,SCHM);
	CreateDataDisc(capsule,FLAK,PRCA);
	CreateDataDisc(capsule,AB5B,ERBK);
	
	//Munition
	CreateDataDisc(capsule,ENAP,STAP,GRAP);
	CreateDataDisc(capsule,GSAP,MIAP);
	
	//Waffen
	CreateDataDisc(capsule,BZWP,MEZL,ENWP);
	CreateDataDisc(capsule,FTWP,GLWP,MIWP);
	CreateDataDisc(capsule,GGWP,PIWP,PGWP);
	
	//Upgrades
	CreateDataDisc(capsule,KLAS,KSLM,KRFL);
	
	//Ausrüstung
	CreateDataDisc(capsule,MEDI);
	
	Log("*Kommandozentrale schickt eine Raumsonde.*");
	Sound("Bip3");
}

global func KommandoNachricht(s)
{
	Log("<Landungseinheit> a%af-s6fkahsf14%o");
	if(iStory==1)
	{
		iStory=2;
		Log("<Kommandozentrale> Kacki kack das Signal ist gestört. Hier kommt nur quatsch an.");
	Sound("Bip3");
	ScriptGo(1);
		goto(56);
	}
	return(1);
}
*/

func WantedObjectDelivered(iPlr,val,count)
{
	if(count==2)//Wurden schon 2 Objekte ausgeliefert, die sich der Chaosgott gewünscht hat, verbünden sich Indigene
	{
		Log("<Indigene> Oh wir sehen ihr huldigt auch dem Chaosgott? Dann lasst uns von nun an Yordas sein, Yorda?");
		SetHostility(1,iPlr);
		SetHostility(iPlr,1);
	}
	return(1);
}

func InitializePlayer(iPlr)
{
	var pClonk= GetCrew(iPlr);
	for(var i=0; GetCrew(iPlr,i);i++)
	{
		SetPlrViewRange(200,GetCrew(iPlr,i));
		//SetPosition(2720,1597,pClonk);
		//SetPosition(2579+RandomX(-20,-20)+900,1100,pClonk);
		/*-> Licht::GetX()
	 = 2977
	-> Licht::GetY()
	 = 1089*/
		SetPosition(2977+RandomX(-20,-20),1089-10,GetCrew(iPlr,i));
	}
	SetFoW(true,iPlr);
	
	if(!alliedIndians)
	{
		SetHostility(1,iPlr,1,1);
		SetHostility(iPlr,1,1,1);
	}
	else
	{
		SetHostility(1,iPlr,0,1);
		SetHostility(iPlr,1,0,1);
	}
	
	//if(ClassSelection()) FindObject(KSSL)->~ActivateSelection(pClonk);
	
	
	//var capsule = CreateObject(SCA2,1149,988,-1);//Erste
	//var capsule = CreateObject(SCA2,692+900,354,-1);//Zweite
	
	CreateContents(FCKL,pClonk,2);
	CreateContents(MLLT,pClonk,1);
	//CreateContents(FCKL,pClonk,2);
	
	if(iPlr==0)
		CreateContents(FLAG,pClonk);
	//CreateContents(NLGT,pClonk);
	
	CreateContents(CNKT,pClonk);
	
	/*
	var pClonk= CreateObject(JCLK,10,10,iPlr);
	MakeCrewMember (pClonk,iPlr);
	SetPlrViewRange(200,pClonk);
	//SetPosition(2579+RandomX(-10,-10),1100,pClonk);
	SetPosition(2720,1597,pClonk);
	
	CreateContents(BLTB,pClonk);
	CreateContents(SLNG,pClonk);
	CreateContents(SPR1,pClonk);
	CreateContents(ARP2,pClonk);
	CreateContents(ROCK,pClonk,3);
	*/
	return(1);
}