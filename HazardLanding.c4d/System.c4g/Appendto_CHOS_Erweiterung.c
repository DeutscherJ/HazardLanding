/*-- Regelwahlen --*/

#strict
#appendto CHOS

local addGoalArray;

/*Es soll sichergesteltl werden, dass ein Menü nicht ausvershen geschlossen wird*/
func Initialize()
{
	ScheduleCall(this(),"UpdateChoice",15);
	return(_inherited());
}

func UpdateChoice()
{
	ScheduleCall(this(),"UpdateChoice",15);
	var pClonk = GetCursor(iChoosingPlr);
	if(!GetMenu(pClonk))
		OpenMenu();
	return(1);
}

protected func OpenMenu()
{
  if(GetLength(aGoals)) return(OpenGoalChooseMenu());

  var pClonk = GetCursor(iChoosingPlr);
  if(!pClonk) return(ScheduleCall(this(), "OpenMenu", 1));

  if(GetMenu(pClonk))
    CloseMenu(pClonk);

  Message("", pClonk);

  CreateMenu(GetID(), pClonk, 0, 0, 0, 0, 1);
  // Spielregeln
  if(!GameCall("OpenScenario"))
	AddMenuItem("$CreateRules$", "OpenRuleMenu", CTFL, pClonk, 0,0, "$RuleInfo$");
  else
	AddMenuItem("$CreateRules$", "OpenOpenRuleMenu", CTFL, pClonk, 0,0, "$RuleInfo$");
  // Dunkelheit
  if(IsDark())
    AddMenuItem("%s", "OpenDarknessMenu", DARK, pClonk,0,0,"$DarknessChose$");
  // Spielziel
  if(GoalIsCompatible()) AddMenuItem("%s", "OpenGoalMenu", GetID(pGoal), pClonk,0,0,"$GoalChose$");
  // KI
  if(ObjectCount(WAYP) && !GetLeague()) AddMenuItem("$AIMenu$", "OpenAIMenu", HZCK, pClonk, 0,0, "$AIInfo$");
  // Aliens
  if(ObjectCount(ALAR)) AddMenuItem("$AlienMenu$", "OpenAlienMenu", ALAR, pClonk, 0,0, "$AlienInfo$");
 
  // Andere Einstellbare Objekte, wie z.B. Spielziele
  for(var obj in FindObjects(Find_Func("ConfigurableInChooserMenu",this())))  
		AddMenuItem("%s", Format("Object(%d)->~CooseMenu(Object(%d),Object(%d))",ObjectNumber(obj),ObjectNumber(pClonk),ObjectNumber(this())), GetID(obj), pClonk,0,0,GetDesc(0,GetID(obj)));

  // Regel Optionen hinzufügen
  var i = 0;
  for(var check in aRules)
  {
    if(check)
    {
      //CreateObject(GetDefinition(i, Chooser_Cat), 10, 10, -1);
	  var idBla = GetDefinition(i, Chooser_Cat);
	  if(DefinitionCall(idBla,"HasChooseMenu"))
		AddMenuItem("%s", Format("DefinitionCall(%v,\"RuleCooseMenu\",Object(%d))",idBla,ObjectNumber(pClonk)), idBla, pClonk,0,0,GetDesc(0,idBla));
    }
    i++;
  }
 
  
  // Fertig
  AddMenuItem("$Finished$", "ConfigurationFinished", CHOS, pClonk,0,0,"$Finished$",2,3);
}

func ConfigurationFinished2()
{
	for(var goal in FindObjects(Find_Category(C4D_Goal)))
	{
		if(goal->~GoalWithLateInit())
			goal->~LateInit();
	}
	
	
  Death = true;
  // Regeln erzeugen
  var i = 0, j, pCrew, tmp, log = "$Rules$", cnt = 0, comma = "";
  for(var check in aRules)
  {
    if(check)
    {
      if(cnt) comma = ", ";
	  if(!FindObject(GetDefinition(i, Chooser_Cat)))//Regel erzeugen wenn nicht schon vorhanden
		CreateObject(GetDefinition(i, Chooser_Cat), 10, 10, -1);
      log = Format("%s%s%s", log, comma, GetName(0, GetDefinition(i, Chooser_Cat)));
      cnt++;
    }
	else//Falls nicht ausgewählt, soll die Regel gelöscht werden
	{
		if(!FindObject(GetDefinition(i, Chooser_Cat)))
			RemoveAll(GetDefinition(i, Chooser_Cat));
	}
    i++;
  }
  // Dunkelheit erzeugen
  log = Format("%s%s%s x%d", log, comma, GetName(0, DARK), iDarkCount);
  Log(log);
  // ein schneller GameCall für Einstellungen
  GameCallEx("ChooserFinished");

  // Spieler freilassen
  for(i = 0 ; i < GetPlayerCount() ; i++)
  {
    for(j = 0 ; pCrew = GetCrew(GetPlayerByIndex(i), j) ; j++)
    {
      tmp = Contained(pCrew);
      RemoveObject(tmp, 1);
      
      pCrew->~Recruitment(pCrew->GetOwner());
    }
    for(var rule in FindObjects(Find_Category(Chooser_Cat), Find_Exclude(this())))
      rule->~InitializePlayer(GetPlayerByIndex(i));
	GameCall("LatePlayerInit",GetPlayerByIndex(i)); 
	
  }

  // Überschüssiges TIM1-Objekte entfernen (falls Spieler ziwschenzeitlich geflogen sind)
  for(tmp in FindObjects(Find_ID(TIM1)))
    if(!(tmp->Contents()))
      RemoveObject(tmp, 1);
  // Selber entfernen
  RemoveObject();
	
	return(1);
}



/*Ziele können optional eingestellt werden oder inaktiv*/

protected func OpenGoalChooseMenu()
{
  var pClonk = GetCursor(iChoosingPlr);
  if(!pClonk) return(ScheduleCall(this(), "OpenMenu", 1));
  if(!GetLength(aGoals)) return(ScheduleCall(this(), "OpenMenu", 1));

  CloseMenu(pClonk);

  if(GetLength(aGoals) == 1) {
    return(CreateGoal(aGoals[0], aTempGoalSave[0]));
  }

  CreateMenu(GetID(), pClonk, 0, 0, 0, 0, 1);

	var i;
	if(!addGoalArray)
	{
		addGoalArray = [];
		for(var goal in aGoals)
		{
			addGoalArray[i]=0;
			i++;
		}
	}
	i=0;
  
  var optionalGoalCount = 0;
  for(var goal in aGoals)
  {
    //AddMenuItem("%s", "CreateGoal", goal, pClonk, 0, aTempGoalSave[i]);
	if(DefinitionCall(goal,"PossibleOptionalGoal")) optionalGoalCount++;
	if(addGoalArray[i] == 0)
		AddMenuItem("%s (aus): hinzufügen", Format("SetGoalStatus(%d,%d)",1,i), goal, pClonk, 0, aTempGoalSave[i]);
	if(addGoalArray[i] == 1 && DefinitionCall(goal,"PossibleOptionalGoal"))
		AddMenuItem("%s (aktiv): optional", Format("SetGoalStatus(%d,%d)",2,i), goal, pClonk, 0, aTempGoalSave[i]);
	if(addGoalArray[i] == 1 && !DefinitionCall(goal,"PossibleOptionalGoal"))
		AddMenuItem("%s (aktiv): löschen", Format("SetGoalStatus(%d,%d)",0,i), goal, pClonk, 0, aTempGoalSave[i]);
	if(addGoalArray[i] == 2)
		AddMenuItem("%s (optional): löschen", Format("SetGoalStatus(%d,%d)",0,i), goal, pClonk, 0, aTempGoalSave[i]);
    i++;
  }
  if(!optionalGoalCount) return(_inherited(Par(0),Par(1),Par(2),Par(3)));
  AddMenuItem("$Finished$", "GoalReady", CHOS,pClonk,0,0,"$Finished$",2,3);
}

func GoalReady()
{
	var lastGoal, i, goalI;
	for(var goalBool in addGoalArray)//Wurde ein Spielziel ausgewählt?
	{
		if(goalBool==1)
		{
			lastGoal = aGoals[i];
			goalI = i;
		}
		i++;
	}
	
	if(!lastGoal)
	{
		Sound("Error");
		return(OpenGoalChooseMenu());//Ansonsten weiter zwingen
	}
	
	i = 0;
	for(var goalBool in addGoalArray)//Alle möglichen Ziele durchgehen
	{
		var goalID = aGoals[i];
		if(goalBool>=1)//Ist ein Ziel hinzugefügt?
		{
			var goal = FindObject(goalID);
			if(!goal) goal = CreateObject(goalID,5,5,-1);
			if(goalBool==2)
				goal->~SetOptional();
		}
		i++;
	}
	
	CreateGoal(lastGoal,aTempGoalSave[goalI]);
	return(OpenMenu());
}
protected func SetGoalStatus(int status,int goalArrayPos)
{
  addGoalArray[goalArrayPos] = status;
  var goalID = aGoals[goalArrayPos];
  var i;
  if(!DefinitionCall(goalID,"PossibleOptionalGoal") && !DefinitionCall(goalID,"AdditionalGoal"))//Ist das Ziel nicht optional und kann auch nicht zusätzlich gewählt werden? Dann werden alle anderen Ziele gelöscht oder optional gesetzt.
  {
	for(var goal in aGoals)
	{
		if(goal!=goalID)
		{
			if(addGoalArray[i]==1 && DefinitionCall(goal,"PossibleOptionalGoal"))
				addGoalArray[i] = 2;//Optional
			if(addGoalArray[i]==1)
				addGoalArray[i] = 0;
		}
		i++;
	}
  }
  else
  {
	for(var goal in aGoals)//Alle bisher hinzugefügten Ziele durchgehen, Wenn ein Ziel nicht optional oder zusätzlich gewählt werden kann, wird es deaktiviert
	{
		if(goal!=goalID)
		{
			if(addGoalArray[i]==1 && (!DefinitionCall(goal,"PossibleOptionalGoal")&&!DefinitionCall(goal,"AdditionalGoal")))
				addGoalArray[i] = 0;
		}
		i++;
	}
  }
  OpenGoalChooseMenu();
}

protected func CreateGoal(id idGoal, int iScore)
{
  // Spielziel erstellen
  var goal = FindObject(idGoal);
  if(!goal) goal = CreateObject(idGoal, 0,0, -1);
  // Alten Wert setzen
  SetWinScore(iScore, goal);
  // Alle benachrichtigen
  Log("$Goal$", GetName(0, idGoal));
  // Array leeren, damit das Menü nicht nochmal kommt
  aGoals = CreateArray();

	GameCallEx("GoalChosen");
	
  // Normales Menü öffnen
  OpenMenu();
}

/*Regelwahl für Offene Szenarien*/

protected func OpenOpenRuleMenu(id dummy, int iSelection)
{
  Chooser_Cat = 524288;
  var pClonk = GetCursor(iChoosingPlr);
  // Menü aufmachen
  CreateMenu(GetID(), pClonk);
  // Regeln einfügen
  for(var i=0, idR, def, j, check ; idR = GetDefinition(i, Chooser_Cat) ; i++)
    if(!GetLength(FindObjects(Find_ID(idR))) && !DefinitionCall(idR,"Unchoosable"))
      {
      def = CreateObject(idR, 0,0, -1);
      if(aRules[i])
        {
        SetGraphics("Chosen", def, WPCH, 1, GFXOV_MODE_Picture);
        SetObjDrawTransform(650,0,5000,0,650,5000, def, 1);
        }
      AddMenuItem("%s", "ChangeRuleConf", idR, pClonk, 0, i, 0, 4, def);
      if(i == iSelection)
        check = true;
      if(!check)
        j++;
      RemoveObject(def);
      }
  // Fertig
  AddMenuItem("$Finished$", "OpenMenu", CHOS, pClonk,0,0,0,2,3);
  // Menüeintrag auswählen
  SelectMenuItem(j, pClonk);
}

protected func ChangeRuleConf(id dummy, int i)
{
  // Regel wurde ausgewählt
  if(!aRules[i])
    aRules[i] = true;
  // Regel wurde abgewählt
  else
    aRules[i] = false;
  // Geräusch
  Sound("Grab", 1,0,0,iChoosingPlr+1);
  // Regelmenü wieder aufmachen
  if(!IsOpenScenario())
	OpenRuleMenu(0, i);
  else
	OpenOpenRuleMenu(0, i);
}