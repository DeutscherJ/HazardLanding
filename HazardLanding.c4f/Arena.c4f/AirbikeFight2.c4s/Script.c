/*-- AirbikeKampf v2 --*/

#strict

static iReady, iRelaunches, SPSeconds, SP;

func Initialize()
{
  SPSeconds=5;
  SetSkyParallax(0,0,0,0,-1);
  iRelaunches=5;
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
	var bike= CreateObject(AB5B,GetX(pClonk),GetY(pClonk),GetOwner(pClonk));
	Enter(bike,pClonk);
	bike-> ActivateEntrance(pClonk);
	Local(5,pClonk)=bike;
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

protected func InitializePlayer(int iPlr, int iX, int iY, object pBase, int iTeam)
{
  RelaunchPlayer(iPlr, GetCrew(iPlr), 0, iTeam);
}

public func RelaunchPlayer(int iPlr, object pCrew, object pKiller, int iTeam)
{  
  // Kein ordentlicher Spieler?
  if(GetOwner(pCrew) == NO_OWNER || iPlr == NO_OWNER)
    return();
  // Kein Team
  if(!iTeam) iTeam = GetPlayerTeam(iPlr);
  
  // Zufallsposition
  var iX=RelaunchPosition(iTeam,0);
  var iY=RelaunchPosition(iTeam,1);
  
  // Clonk tot?
  if(!GetAlive(pCrew))
  {
    pCrew = RelaunchClonk(iPlr, pCrew);
	var bike= CreateObject(AB5B,iX,iY,iPlr);
	Enter(bike,pCrew);
	bike-> ActivateEntrance(pCrew);
	Local(5,pCrew)=bike;
  }
	
  for(var i=0 ; pCrew = GetCrew(iPlr, i) ; i++)
    {
    // Lecker Waffen
    if(!FindObject(IGIB))
    {
      var wpn = CreateContents(PIWP, pCrew);
      wpn->DoAmmo(wpn->GetFMData(FM_AmmoID),wpn->GetFMData(FM_AmmoLoad));
      DoAmmo(STAM, 50, pCrew);
      DoAmmo(GRAM, 10, pCrew);
	}
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
}

func MainEnergySupply(){return(1);}

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
   /*Tische+Stühle*/
   CreateObject(TABL,348,727,-1);
   CreateObject(TABL,396,471,-1);
   
   CreateObject(CHAR,324,727,-1);
   SetDir(DIR_Right(),CreateObject(CHAR,375,727,-1));
   SetDir(DIR_Right(),CreateObject(CHAR,423,471,-1));
   CreateObject(CHAR,372,471,-1);
   
   /*Bodenklappen*/
   CreateObject(_HAC,401,628,-1);
   //CreateObject(_HAC,401,732,-1);
   CreateObject(_HAC,401,420,-1);
   CreateObject(_HAC,513,476,-1);
   CreateObject(_HAC,113,403,-1);
   CreateObject(_HAC,113,331,-1);
   CreateObject(_HAC,1024,324,-1);
   CreateObject(_HAC,1009,468,-1);
   
   /*Leiter*/
   CreateObject(LADR,1029,465,-1)-> Set(17);
   CreateObject(LADR,35,544,-1)-> Set(12);
   
   /*Kisten*/
   CreateObject(_CRT,340,623,-1);
   CreateObject(_CRT,364,623,-1);
   
   CreateObject(_CRT,104-10,543,-1);
   CreateObject(_CRT,129-11,543,-1);
   
   CreateObject(_CRT,938,463,-1);
   CreateObject(_CRT,964,463,-1);
   
   /*Türen*/
   CreateObject(STDR,491,624,-1);
   CreateObject(STDR,428,624,-1);
   CreateObject(STDR,21,544,-1);
   CreateObject(STDR,900,320,-1);
   CreateObject(STDR,925,840,-1);
   
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
   CreateObject(_SWT,50,393,-1);//Schalter
   
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
   
   var klappe4= CreateObject(_MH1,303,782,-1);
   var klappe5= CreateObject(_MH1,950,834,-1);
   Local(0,klappe4)= klappe5;
   Local(0,klappe5)= klappe4;
   
   
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
   CreateContents(A25B,CreateObject(SPNP,304,772,-1));//raketen
   CreateContents(A35B,CreateObject(SPNP,344,617,-1));//bomben
   CreateContents(ATB_,CreateObject(SPNP,410,906,-1));//atombomben
   CreateContents(A15B,CreateObject(SPNP,526,772,-1));//MP
   CreateContents(A35B,CreateObject(SPNP,837,312,-1));//Bomben
   CreateContents(A15B,CreateObject(SPNP,841,455,-1));//MP
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
   
   /*Bildschirme*/
   CreateObject(_DK8,23,392,-1);
}