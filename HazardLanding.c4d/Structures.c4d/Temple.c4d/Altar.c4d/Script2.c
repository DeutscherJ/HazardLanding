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
    // var rnd = Random(100);
    // eine bestimmte Definition verlangen
    // if (rnd > 0) {
      wanted_obj = ObjectCall(item_list, "GetRandom");
      Log(GetString("want"), GetName(0, wanted_obj));
    // }
    /* if (rnd <= 0) {
      wanted_obj = _OCF;
      wanted_ocf = GetRandomOCF();
      Log(GetString("want"), 0, wanted_ocf);
    } */
  }

  // und wieder warten wir etwas länger...
  waiting_time++;

  // langsam werden wir etwas ungeduldig
  /*if (!Random(1620*50/waiting_time)) {
    // Zaubern!
      SetDir(Random(2));
      ObjectCall(CreateObject(RMMG, 0, -20, -1), "Activate", this());
    // Wieder zum Altar werden (manche Zauber ChangeDef()en)
      ChangeDef(_ATR);
  }*/

  // vielleicht ist das Objekt zu hart zu kriegen
  if (!Random(2430*50/waiting_time)) {
    // beim nächsten Durchlauf ein neues ermitteln
    wanted_obj = 0;
    // wir warten von Neuem
    waiting_time = 0;
  }

  // Ab und zu ziehen wir Blitze aus der Luft an
  /*if (!Random(120)) {
    var off_x = AbsX(Random(LandscapeWidth()));
    var y_dir = RandomX(5, 25);
    LaunchLightning(GetX()-off_x, 0, (off_x/(GetY()/y_dir)), 0, y_dir, 0); 
  }*/

  // Objekte, die auf dem Altar liegen, finden
  for (var obj in FindObjects(Find_InRect(-32, -78, 64, 75), Find_NoContainer(),Find_Or(Find_OCF(OCF_Collectible),Find_And(Find_OCF(OCF_Grab),Find_Category(C4D_Vehicle)))))//Find_Category(C4D_Rule | C4D_Goal))
  {
    // keine besitzerlosen Objekte
    if (GetController(obj) != -1)
		if(!GetActionTarget(0,obj))
	//nur Objekte, die sich gerade (fast) nicht bewegen
	if(Abs(GetXDir(obj))<=7 && Abs(GetYDir(obj))<=7)
	  if(!FindObject2(Find_ActionTarget(obj),Find_OCF(OCF_Alive)))//Und an denen gerade keine Aktion ausgeführt wird
		{
			Log("%s wurde geopfert",GetName(obj));
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
          RemoveObject(obj, 1);
          // Belohnung
          Reward(plr, (value+50)*RandomX(1, 3));
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
			RemoveObject(obj, 1);
        }
      }
  }
  // Soll immer frei in der Landschaft rumliegen
  Exit();
}

// Einen Spieler belohnen
protected func Reward(iPlr,value)
{
  while (value > 0)
  {
    var rnd = Random(7);
    if (rnd == 0) {//Objekte verschleudern
      var def = ObjectCall(item_list, "GetRandom");
      CastObjects(def, Min(8, RandomX(10, 20)/GetValue(0, def)), RandomX(30, 200), 0, -20);
      value -= GetValue(0, def)/RandomX(3, 6);
	  Log("<c a82000>* Chaosgott schenkt %s</c>",GetName(0,def));
    }
    if (rnd == 1) {//Bauplan eines Objekts hinzufügen oder Kaufbar machen
      var def = ObjectCall(item_list, "GetRandom");
      var knw = Random(2);
      if (knw) SetPlrKnowledge(iPlr, def);
      if (!knw) DoHomebaseMaterial(iPlr, def, RandomX(1, 2));
      value -= GetValue(0, def)/RandomX(10, 17);
	  Log("<c a82000>* Chaosgott schenkt Baupläne für %s</c>",GetName(0,def));
    }
    if (rnd == 2) {//Objekt ins Inventar legen
      var def = ObjectCall(item_list, "GetRandom");
      SetOwner(iPlr, CreateContents(def, GetCursor(iPlr)));
      value -= GetValue(0, def)/RandomX(5, 10);
	  Log("<c a82000>* Chaosgott schenkt %s</c>",GetName(0,def));
    }
    /*if (rnd == 3) {//Eine Baustelle erzeugen?
      var def = ObjectCall(struct_list, "GetRandom");
      // Altars are _illegal_
      if (def == _ATR) return(0);
      if (FindBase(iPlr)) {
        Var(0) = GetX(FindBase(iPlr));
        Var(1) = GetY(FindBase(iPlr));
        if (FindConstructionSite(def, 0, 1)) {
          CreateConstruction(def, AbsX(Var(0)), AbsY(Var(1)), iPlr, 100, 1);
          value -= GetValue(0, def)/RandomX(5, 10);
        }
      }
    }*/
    /*if (rnd == 4) {//Zufallszauber
      SetDir(Random(2));
      ObjectCall(CreateObject(RMMG, AbsX(GetX(GetCursor(iPlr))), AbsY(GetY(GetCursor(iPlr))), -1), "Activate", GetCursor(iPlr));
      value -= RandomX(10, 30);
    }*/
    if (rnd == 3) {//Guthaben hinzufügen
      var change = Random(value/5);
      DoWealth(iPlr, change);
      Sound("Cash");
      value -= change/RandomX(5, 10);
	  Log("<c a82000>* Chaosgott schenkt %d Guthaben</c>",change);
    }
    if (rnd == 4) {//Baupläne eines Gebäudes hinzufügen 
      var def = ObjectCall(struct_list, "GetRandom");
      // Altars are _illegal_
      if (def != _ATR) {
        SetPlrKnowledge(iPlr, def);
        value -= GetValue(0, def)/RandomX(20, 30);
      }
	  Log("<c a82000>* Chaosgott schenkt Baupläne für %s</c>",GetName(0,def));
    }
    if (rnd == 5) {//Baupläne eines Fahrzeugs hinzufügen 
      var def = ObjectCall(vec_list, "GetRandom");
      SetPlrKnowledge(iPlr, def);
      value -= GetValue(0, def)/RandomX(20, 30);
	  Log("<c a82000>* Chaosgott schenkt Baupläne für %s</c>",GetName(0,def));
    }
    if (rnd == 6) {//Clonk hinzufügen
      if (!Random(3)) {
        var def = ObjectCall(clonk_list, "GetRandom");
        var clonk = CreateObject(def, 0, 0, iPlr);
        MakeCrewMember(clonk, iPlr);
        value -= GetValue(0, def)*RandomX(1, 3);
        if (FindBase(iPlr)) {
          Enter(FindBase(iPlr), clonk);
          return(1);
        }
        SetPosition(GetX(GetCursor(iPlr)), GetY(GetCursor(iPlr)), clonk);
		Log("<c a82000>* Chaosgott schenkt einen %s</c>",GetName(0,def));
      }
    }
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