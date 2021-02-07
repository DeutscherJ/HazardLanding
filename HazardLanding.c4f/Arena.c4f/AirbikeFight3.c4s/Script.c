/*-- AirbikeKampf v3 --*/

#strict

static iReady, SP, idThrowObject, crane;

global func CO(){return(Log("CreateObject(%i,%d,%d,-1);",GetID(),GetX(),GetY()+GetDefCoreVal("Height")/2));}
func NoStippels(){return(1);}
func Initialize()
{
  SetSkyParallax(0,0,0,0,-1);
  //iRelaunches=5;
  Objects();
  idThrowObject=ROCK;
  return(1);
}

/* Regelwähler */

public func ChooserFinished(iDarkness)
{
  iReady=1;
  CreateContents(idThrowObject,SP);
  
  if(!iDarkness) RemoveAll(DARK);
  
  for(var pClonk in FindObjects (Find_ID(HZCK)))
  {
	//Log(Format("Team %d Spieler %d Nummer %d",GetTeam(GetOwner(pClonk)),GetOwner(pClonk),ObjectNumber(pClonk)));
	if(GetPlayerTeam(GetOwner(pClonk))==3)
	{
		var robot= CreateObject(BLBT,GetX(pClonk),GetY(pClonk),GetOwner(pClonk));
		MakeCrewMember(robot,GetOwner(pClonk));
		RemoveObject(pClonk);
		pClonk=robot;
	}
	else
	{
		var bike= CreateObject(AB5B,GetX(pClonk),GetY(pClonk),GetOwner(pClonk));
		Enter(bike,pClonk);
		bike-> ActivateEntrance(pClonk);
		Local(5,pClonk)=bike;
	}
	pClonk->~LaterInit();
  }
  
  // Bei InstaGIB werden alle Spawnpunkte entfernt und die Waffen aus den Spielern entfernt
  if(FindObject(IGIB))
  {
    for(var spwn in FindObjects(Find_ID(SPNP)))
      RemoveObject(spwn);
    for(var clonk in FindObjects(Find_OCF(OCF_CrewMember)))
      while(Contents(0, clonk))
        RemoveObject(Contents(0, clonk));
  }
  // Bei Keine-Munition werden Munispawns entfernt
  if(FindObject(NOAM))
  {
    for(var spwn in FindObjects(Find_ID(SPNP)))
      if(Contents(0, spwn)->~IsAmmoPacket())
        RemoveObject(spwn);
  }
  // Bei Waffenwahl werden alle Nicht-Munispawns entfernt
  var wp = FindObject(WPCH);
  if(wp)
  {
    for(var spwn in FindObjects(Find_ID(SPNP)))
      if(!(Contents(0, spwn)->~IsAmmoPacket()))
        RemoveObject(spwn);
        
    // und begrenzte Waren...
    wp->RemoveWare();
    wp->AddWare(PIWP);  // Pistole
    wp->AddWare(GLWP);  // Granatenwerfer
    wp->AddWare(MIWP);  // Minigun
    wp->AddWare(BZWP);  // Bazooka
    wp->AddWare(KLAS);  // Laser
    wp->AddWare(KRFL);  // Waffenteile
    wp->AddWare(FLSH);  // Taschenlampe
    wp->AddWare(JTPK);  // Jetpack
    wp->AddWare(HARM);  // Rüstung
    wp->AddWare(HSHD);  // Schild
    wp->AddWare(DRSU);  // Drone
    wp->AddWare(MINE);  // Mine
    //wp->SortWare();
  }

}

/* Relaunch */
/*

CreateObject(_MH1,296,782,-1);
CreateObject(_MH1,313,782,-1);
	
*/
protected func InitializePlayer(int iPlr, int iX, int iY, object pBase, int iTeam)
{
  RelaunchPlayer(iPlr, GetCrew(iPlr), 0, iTeam);
}

func LatePlayerInit(iPlr)
{
	RelaunchPlayer(iPlr, GetCrew(iPlr), 0, GetPlayerTeam(iPlr),0,1);
	return(1);
}

public func RelaunchPlayer(int iPlr, object pCrew, object pKiller, int iTeam,aidstest,bool lateInitPar)
{  
  // Kein ordentlicher Spieler?
  if(GetOwner(pCrew) == NO_OWNER || iPlr == NO_OWNER)
    return();
  // Kein Team
  if(!iTeam) iTeam = GetPlayerTeam(iPlr);
  
  // Zufallsposition
  var iX=RelaunchPosition(iTeam,0);
  var iY=RelaunchPosition(iTeam,1);
  
  //Log("%v",lateInitPar);
	// Clonk tot?
	if(!GetAlive(pCrew) || lateInitPar)
	{
		if(!GetAlive(pCrew)) pCrew = RelaunchClonk(iPlr, pCrew);
		if(iTeam!=3)
		{
			var bike= CreateObject(AB5B,iX,iY,iPlr);
			Enter(bike,pCrew);
			bike-> ActivateEntrance(pCrew);
			Local(5,pCrew)=bike;
		}
		else
		{
			var minigun=CreateContents(MIWP,pCrew);
			DoAmmo(STAM, 100, pCrew);
			minigun->Reloaded(pCrew);
			//LocalN("FM_AmmoLoad",minigun)=100;//Geladene Mingun
			DoAmmo(ENAP, 75, pCrew);
		}
		// Lecker Waffen
		if(!FindObject(IGIB))
		{
		  var wpn = CreateContents(PIWP, pCrew);
		  wpn->DoAmmo(wpn->GetFMData(FM_AmmoID),wpn->GetFMData(FM_AmmoLoad));
		  DoAmmo(STAM, 50, pCrew);
		  DoAmmo(GRAM, 10, pCrew);
		}
	}

  for(var i=0 ; pCrew = GetCrew(iPlr, i) ; i++)
    {
    if(Contained(pCrew))
      SetPosition(iX, iY, Contained(pCrew));
    else
      SetPosition(iX, iY, pCrew);
    }
  return(1);
  //Log("%d X %d Y %d Team",iX,iY,iTeam);
  // Fertig gerelauncht
}

public func RelaunchClonk(int iPlr, object pCursor)
{
  var pClonk = CreateObject(HZCK, 100, 100, iPlr);
  if(pCursor)
    GrabObjectInfo(pCursor, pClonk);
  else
    MakeCrewMember(pClonk, iPlr);

  DoEnergy(+150, pClonk);
  SetCursor(iPlr, pClonk);
  SetPlrView(iPlr, pClonk);

  // Geldspritze
  if(FindObject(WPCH))
    DoWealth(iPlr, +25);

  // Wegstecken
  var tim = CreateObject(TIM2, 10, 10, -1);
  pClonk->Enter(tim);
  PlayerMessage(iPlr, Format("@%s", GetName(pClonk)), tim);

  return(pClonk);
}

public func RelaunchPosition(int iTeam,bool fY)
{
  // Anzahl Zufallpositionen, iTeam verwendet für spezielle Teamstartpositionen
  if(iTeam==1)
    {
		if(!fY) return(64);
		return(532);
	}
  if(iTeam==2)
    {
		if(!fY) return(994);
		return(444);
	}
  if(iTeam==3)
    {
		if(Random(2))
		{
			if(!fY) return(423);
			return(464);
		}
		else
		{
			if(!fY) return(470);
			return(715);
		}
	}
}

func MainEnergySupply(){return(1);}
func IsStationScenario(){return(1);}

//global func GetPosition(){return(Format("%d, %d,%d",GetID(),GetX(),GetY()));}
global func OP(pObj)
{
  if(!pObj) pObj=this();
  var x= GetX(pObj);
  var y= GetY(pObj) - GetDefCoreVal("Offset", "DefCore", GetID(pObj),1);
  return(Format("CreateObject(%i,%d,%d,-1);",GetID(pObj),x,y));
}

/*Objekte*/
func Objects()
{
	CreateObject(LADR,5,783,-1)->Set(33);
	CreateObject(ESGN,313,705,-1);//Feuerlöscherschild
	/*Tische+Stühle*/
	CreateObject(TABL,348,727,-1);
	CreateObject(TABL,396,471,-1);
   
	CreateObject(CHAR,324,727,-1);
	SetDir(DIR_Right(),CreateObject(CHAR,375,727,-1));
	SetDir(DIR_Right(),CreateObject(CHAR,423,471,-1));
   
	/*Bodenklappen*/
	CreateObject(HA4K,401,626,-1);
	//CreateObject(_HAC,401,732,-1);
	CreateObject(HA4K,401,418,-1);
	CreateObject(HA4K,513,474,-1);
	CreateObject(HA4K,113,401,-1);
	CreateObject(HA4K,113,231,-1);
	CreateObject(HA4K,1024,322,-1);
	CreateObject(HA4K,1009,466,-1);
   
	/*Leiter*/
	CreateObject(LADR,1029,465,-1)-> Set(17);
	CreateObject(LADR,35,544,-1)-> Set(12);
   
	/*Kisten*/
	CreateObject(_CRT,340,623,-1);
	CreateContents(KRFL,CreateObject(_CRT,364,623,-1));
   
	CreateContents(KRFL,CreateObject(_CRT,104-10,543,-1));
	CreateObject(_CRT,129-11,543,-1);
   
	CreateObject(_CRT,938,463,-1);
	CreateContents(KRFL,CreateObject(_CRT,964,463,-1));
   
	/*Türen*/
	CreateObject(STDR,491,624,-1);
	CreateObject(STDR,428,624,-1);
	CreateObject(STDR,21,544,-1);
	CreateObject(STDR,900,320,-1);
	CreateObject(STDR,925,840,-1);
	CreateObject(SLDR,293,727,-1);
   
	/*Automaten*/
	CreateObject(CLVM,498,728,-1);
	CreateObject(CLVM,984,320,-1);

	/*Schwebeplatte*/
	var lift= CreateObject(_LFP,456,730,-1);
	Local(1,lift)=1;
	Local(2,lift)=1;
	Local(3,lift)=470;
	Local(4,lift)=422;
	Local(5,lift)=717;
	CreateObject(_SWT,50,393,-1);//Schalter links
	CreateObject(_SWT,955,311,-1);//Schalter rechts
   
   
	/*Ventilatoren*/
	SetCon(40,CreateObject(VENT,352,737-40,-1));
	SetCon(40,CreateObject(VENT,64,567-40,-1));
	SetCon(40,CreateObject(VENT,966,465-40,-1));
	SetCon(40,CreateObject(VENT,479,737-40,-1));
   
	/*Alarmlichter*/
	CreateObject(WALE,124,478,-1);
	CreateObject(WALE,507,433,-1);
	CreateObject(WALE,1005,357,-1);
   
	/*Lüftungsklappen*/
	var klappe1= CreateObject(_MH1,420,722,-1);//Frühstückshalle
	var klappe2= CreateObject(_MH1,528,782,-1);//Stütze
	Local(0,klappe1)= klappe2;
	Local(0,klappe2)= klappe1;
   
	var klappe3= CreateObject(_MH1,131,394,-1);//Ganz links
	var klappe4= CreateObject(_MH1,926,313,-1);//Ganz rechts
	Local(0,klappe3)= klappe4;
	Local(0,klappe4)= klappe3;
   
	var klappe4= CreateObject(_MH1,313,782,-1);
	var klappe5= CreateObject(_MH1,950,834,-1);
	Local(0,klappe4)= klappe5;
	Local(0,klappe5)= klappe4;
   
   
	var klappe6= CreateObject(_MH1,21,779,-1);
	var klappe7= CreateObject(_MH1,297,782,-1);
	Local(0,klappe6)= klappe7;
	Local(0,klappe7)= klappe6;
	
	/*Sichtfenster*/
	CreateObject(_TWW,544,477,-1);
	CreateObject(_TWW,561,732,-1);
	CreateObject(_TWW,161,398,-1);
	SetGraphics("2",CreateObject(_TWW,344,477,-1));
   
	CreateObject(_TW2,912,281,-1);
	CreateObject(_TW2,944,256,-1);
   
	/*Spawnpunkte*/
	CreateContents(A25B,CreateObject(SPNP,57,321,-1));//Raketen
	CreateContents(A15B,CreateObject(SPNP,199,533,-1));//MP
	CreateContents(A25B,CreateObject(SPNP,290,772,-1));//raketen
	CreateContents(A35B,CreateObject(SPNP,344,617,-1));//bomben
	CreateContents(ATB_,CreateObject(SPNP,410,906,-1));//atombomben
	CreateContents(A15B,CreateObject(SPNP,526,772,-1));//MP
	CreateContents(A35B,CreateObject(SPNP,837,312,-1));//Bomben
	CreateContents(A15B,CreateObject(SPNP,841,455,-1));//MP
   
	CreateContents(BZWP,CreateObject(SPNP,946,895,-1));//UntenRechts
	CreateContents(KLAS,CreateObject(SPNP,522,722,-1));//Cafeteria
	CreateContents(JTPK,CreateObject(SPNP,509,616,-1));//Mitte
	CreateContents(ENWP,CreateObject(SPNP,396,457,-1));//Oben
	CreateContents(PGWP,CreateObject(SPNP,83,390,-1));//Links
	CreateContents(PGWP,CreateObject(SPNP,956,315,-1));//Rechts
	
   
	SP= CreateObject(SPNP,448,405,-1);//Stein ... als Wurfwaffe
	CreateContents(GRAP,CreateObject(SPNP,397,721,-1));//Granaten
	
	//zusätzliche
	CreateContents(A25B,CreateObject(SPNP,956,777));
	CreateContents(ENAP,CreateObject(SPNP,459,446));
	CreateContents(A15B,CreateObject(SPNP,1005,221));
   
	/*Geländer*/
	CreateObject(_RL1,309,624,-1);
	CreateObject(_RL1,297,624,-1);
	CreateObject(_RL1,526,624,-1);
	CreateObject(_RL1,538,624,-1);
	CreateObject(_RL1,781,320,-1);
	CreateObject(_RL1,769,320,-1);
	CreateObject(_RL1,126,448,-1);
	CreateObject(_RL1,138,448,-1);
   
	CreateObject(LBGH,353,634,-1);
	CreateObject(LBGH,424,634,-1);
   
	var l=CreateObject(FLGH,68,784,-1);
	l->SetRotation(45);
	//l->Off();
	l=CreateObject(FLGH,889,841,-1);
	l->SetRotation(-45);
	//l->Off();
	l=CreateObject(FLGH,532,625,-1);
	l->SetRotation(30);
	//l->Off();
	CreateObject(BLGH,455,457,-1);
	CreateObject(CLGH,82,339,-1);
	CreateObject(CLGH,8,515,-1);
	CreateObject(BLGH,950,276,-1);
	CreateObject(BLGH,1012,276,-1);
	CreateObject(MONI,77,389,-1)->On();
	CreateObject(PLNT,1002,319,-1);
	CreateObject(CGLO,926,320,-1);
	
	/*Setry Gun
	CreateObject(SEGU,377,516,-1);
	CreateObject(SEGU,414,772,-1);
	CreateObject(SEGU,778,388,-1);
	CreateObject(SEGU,123,596,-1);*/
	
	CreateObject(JMPD,973,792,-1)->Set(130,-45,0);
	CreateObject(JMPD,40,743,-1)->Set(105,45,90);
	//Toilette
	CreateObject(WSHB,936,840,-1);
	CreateObject(TOIC,955,840,-1);
	
	/*Bildschirme*/
	CreateObject(_DK8,23,392,-1);
   
    /*Musikbox*/
	CreateObject(MSBX,407,727,-1);
	
	CreateObject(RADR,974,232,-1);//Radar

	CreateObject(PLT2,522,729,-1);//Pflanze
	CreateObject(CHAR,64,399,-1);//Stuhl
	CreateObject(TABL,86,399,-1);//Tisch
	CreateObject(FIEX,76,538,-1);//Feuerlöscher
	CreateObject(FIEX,307,727,-1);//Feuerlöscher
	CreateObject(FIEX,972,819,-1);//Feuerlöscher
	//CreateObject(FLAK,79,328,-1);//Flak links
	CreateObject(FLAK,486,416,-1);//Flak mitte
	//CreateObject(FLAK,805,320,-1);//Flak rechts
	CreateObject(LCKR,503,472,-1);//Spint
	CreateObject(LCKR,487,472,-1);//Spint
	
	CreateObject(LBGH,950,353,-1)->Set(60);
	CreateObject(LBGH,107,473,-1)->Set(30);
	
	//Jawoll ein Kran gibts denn sowas? :-O
	crane = CreateObject(CRN1,285,560,-1);
	crane->Set(20);
	
	var konsole=CreateObject(CONS,371,463,-1);
	LocalN("target",konsole)=crane;
}