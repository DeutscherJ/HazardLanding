#strict
 
local wanted_obj,	// gesuchtes Objekt
      wanted_ocf,	// gesuchtes OCF
      waiting_time,	// so lange wird schon auf das gesuchte Objekt gewartet
      x,		// altes X
      y;		// altes Y

static wantedObjectsCount;

// Altar wurde erzeugt
protected func Construction() {
  SetCategory(C4D_Vehicle());
  SetAction("Be");
}

// Timercall
protected func Check() {
  // x und y anpassen
  x = GetX();
  y = GetY();
  // Es kann nur einen geben!
  if (ObjectCount(_ATR) > 1) RemoveObject();

  // wenn wir kein Objekt wollen, wird jetzt ein neues rausgesucht
  if (!wanted_obj) {
      wanted_obj = PickRandomFromArray(FillArray(C4D_Object,"Collectible"));
      Log(GetString("want"), GetName(0, wanted_obj));
  }

  // und wieder warten wir etwas länger...
  waiting_time++;

  // vielleicht ist das Objekt zu hart zu kriegen
  if (!Random(2430*50/waiting_time)) {
    // beim nächsten Durchlauf ein neues ermitteln
    wanted_obj = 0;
    // wir warten von Neuem
    waiting_time = 0;
  }

  // Objekte, die auf dem Altar liegen, finden
  for (var obj in FindObjects(Find_InRect(-32, -78, 64, 75), Find_NoContainer(),Find_Or(Find_OCF(OCF_Collectible),Find_And(Find_OCF(OCF_Grab),Find_Category(C4D_Vehicle)))))
  {
    // keine besitzerlosen Objekte
    if (GetController(obj) != -1)
		if(!GetActionTarget(0,obj))
			//nur Objekte, die sich gerade (fast) nicht bewegen
			if(Abs(GetXDir(obj))<=7 && Abs(GetYDir(obj))<=7)
				{
					if(FindObject2(Find_ActionTarget(obj),Find_OCF(OCF_Alive)))
					{
						var tar = FindObject2(Find_ActionTarget(obj),Find_OCF(OCF_Alive));
						if(GetAction(tar)ne"Push" && GetAction(tar)ne"Ride" && GetAction(tar)ne"RideStill")
							continue;
					}
					// Rausfinden ob wir das Objekt überhaupt wollen
					var wanted = 0;
					// passt die ID zu gewollten Objekt?
					if (GetID(obj) == wanted_obj)
						// gewollt
						wanted = 1;

					// gewollt
					if (wanted) {
					  var plr = GetController(obj);
					  wantedObjectsCount++;
					  var value = GetValue(obj);
					  GameCall("WantedObjectDelivered",plr,value,wantedObjectsCount);
					  for(var i=0; Contents(i,obj);i++)
					  {
						  value+=GetValue(Contents(i,obj));
					  }
					  // wir warten nicht mehr
					  waiting_time = 0;
					  // weg frei machen für ein neues Ziel
					  wanted_obj = 0;
					  // Objekt konsumieren
					  RemoveObject(obj);
					  // Belohnung
					  Reward(plr, (value+50)*RandomX(2, 3));
					  // Sound
					  Sound("Energize");
					  // Punktebelohnung beim Spielzielobjekt
					  if(FindObject(_CGG)) ObjectCall(FindObject(_CGG), "Reward", plr);
					  // Bedanken
					  Log(GetString("thanks"), GetPlayerName(plr));
					  // Funken sprühen
					  CastObjects(SPRK, RandomX(14, 34), RandomX(50, 80), 0, -10);
					}
					// ungewollt
					if (!wanted)
					{
						var value = GetValue(obj);
						for(var i=0; Contents(i,obj);i++)
						{
							value+=GetValue(Contents(i,obj));
						}
						// kleine Belohnung
						Reward(GetController(obj), value/RandomX(2, 5));
						// Sound
						Sound("Energize");
						// Flammen schleudern
						//CastObjects(DFLM, RandomX(3, 5), 10, 0, -10);
						CastObjects(SPRK, RandomX(14, 34), RandomX(50, 80), 0, -10);
						// Objekt konsumieren
						RemoveObject(obj);
					}
			  }
  }
  // Soll immer frei in der Landschaft rumliegen
  Exit();
}

//Eine Belohnung raushauen. 
//PickFromObjectArray(FindObjects(Find_ID(RM01)),"GetX(%s)","Min")
	
	
func RewardType(iType,iVal,iPlr)
{
	var iValOut = iVal+1;
	var maxCounter = 0;
	while(iValOut>iVal && maxCounter<10)
	{
		//Objekt ins Inventar legen
		if(iType == 0)
		{
			var def = PickRandomFromArray(FillArray(C4D_Object,"Collectible",0,iVal));
			if(!def) continue;
			iValOut = GetValue(,def);
		}
		//Bauplan eines Objekts hinzufügen oder Kaufbar machen
		if (iType == 1)
		{
			var def = PickRandomFromArray(FillArray(1024,"Collectible",0,iVal*4));
			if(!def) continue;
			iValOut = GetValue(, def)/4;
		}
		//Guthaben hinzufügen
		if (iType == 2)
		{
			var def = Random(iVal/5);
			iValOut = def/RandomX(2, 4);
		}
		//Baupläne eines Gebäudes hinzufügen 
		if (iType == 3)
		{
			var def = PickRandomFromArray(FillArray(1024,"Construction",Format("!GetPlrKnowledge(%d,%s)",5,"%i"),iVal*20));
			if(!def) continue;
			iValOut = GetValue(, def)/RandomX(20, 30);
		}
		//Baupläne eines Fahrzeugs hinzufügen 
		if (iType == 4)
		{
			var def = PickRandomFromArray(FillArray(C4D_Vehicle|256,"Rebuy",Format("!GetPlrKnowledge(%d,%s)",5,"%i"),iVal*30));
			if(!def) continue;
			//if(GetPlrKnowledge(iPlr, def)) continue;
			iValOut = GetValue(, def)/RandomX(20, 30);
		}
		//Clonk hinzufügen
		if (iType == 5 && Random(3))
		{
			var def = PickRandomFromArray(FillArray(C4D_Living|2048,"CrewMember",0,iVal));
			if(!def) continue;
			iValOut = GetValue(, def)*RandomX(1, 3);
		}
		maxCounter++;
	}
	if(!def)
		return(0);
	Blar(iType,def,iPlr);
	if(!iValOut) iValOut=0;
	return([iValOut,def]);
}

func Blar(iType,def,iPlr)
{
	if(iType==0)
	{
		SetOwner(iPlr, CreateContents(def, GetCursor(iPlr)));
	}
	if(iType==1)
	{
		var knw = Random(2);
		if (!knw || GetPlrKnowledge(iPlr, def)) DoHomebaseMaterial(iPlr, def, RandomX(1, 2));
		if (knw) SetPlrKnowledge(iPlr, def);
	}
	if(iType==2)
	{
		DoWealth(iPlr, def);
		Sound("Cash");
	}
	if(iType==3 || iType==4)
	{
		SetPlrKnowledge(iPlr, def);
	}
	if(iType==5)
	{
		var clonk = CreateObject(def, 0, 0, iPlr);
		MakeCrewMember(clonk, iPlr);
		if (FindBase(iPlr))
		{
			Enter(FindBase(iPlr), clonk);
			return(1);
		}
		SetPosition(GetX(GetCursor(iPlr)), GetY(GetCursor(iPlr)), clonk);
	}
	return(1);
}

// Einen Spieler belohnen
protected func Reward(iPlr,value)
{
  var maxCounter = 0;
  while (value > 0 && maxCounter<30)
  {
    var rnd = Random(6);
	var reward = RewardType(rnd,value,iPlr);
	//Log("%d %d %d",value,maxCounter,rnd);
	if(!reward) continue;
    if (rnd == 0)//Objekt ins Inventar legen
		Log("$Action1$",GetName(0,reward[1]));
		//Log(Format("$Fire%d$",rnd+1))<c a82000>* Chaosgott schenkt %s</c>",GetName(0,reward[1]));
    if (rnd == 1)//Baupläne eines Objektes hinzufügen
		Log("$Action2$",GetName(0,reward[1]));
		//Log("<c a82000>*  Chaosgott schenkt Baupläne für %s</c>",GetName(0,reward[1]));
    if (rnd == 2)//Guthaben hinzufügen
		Log("$Action3$",reward[0]);
		//Log("<c a82000>* Chaosgott schenkt %d Guthaben</c>",reward[0]);
    if (rnd == 3)//Baupläne eines Gebäudes hinzufügen 
		Log("$Action4$",GetName(0,reward[1]));
	  //Log("<c a82000>* Chaosgott schenkt Baupläne für %s</c>",,GetName(0,reward[1]));
    if (rnd == 4)//Baupläne eines Fahrzeugs hinzufügen 
		Log("$Action5$",GetName(0,reward[1]));
	  //Log("<c a82000>* Chaosgott schenkt Baupläne für %s</c>",GetName(0,reward[1]));
    if (rnd == 5)//Clonk hinzufügen
		Log("$Action6$",GetName(0,reward[1]));
		//Log("<c a82000>* Chaosgott schenkt einen %s</c>",GetName(0,reward[1]));
	value -= reward[0];
	if(value<2) maxCounter+=4;//Wenn es sich nurnoch um kleckerbeträge handelt nicht zu lange versuchen eine Kombination zu finden
	maxCounter++;
  }
  return(1);
}

// can't be destructed
protected func Destruction() {
  if (ObjectCount(_ATR) > 0) return(0);
  if (x && y)
    CreateObject(_ATR, AbsX(x), AbsY(y+1), -1);
  return(1);
}