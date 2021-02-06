/*-- Menü v3--*/

#strict
#appendto CHOS

protected func OpenMenu()
{
  /*if(GetLength(aGoals)) return(OpenGoalChooseMenu());

  var pClonk = GetCursor();
  if(!pClonk) return(ScheduleCall(this(), "OpenMenu", 1));

  if(GetMenu(pClonk))
    CloseMenu(pClonk);

  CreateMenu(GetID(), pClonk, 0, 0, 0, 0, 1);
  // Spielziele
  AddMenuItem("$CreateRules$", "OpenRuleMenu", CTFL, pClonk, 0,0, "$RuleInfo$");
  // Dunkelheit
  if(IsDark())
    AddMenuItem("%s", "OpenDarknessMenu", DARK, pClonk,0,0,"$DarknessChose$");
  AddMenuItem("%s", "ST", SPTM, pClonk,0,0,"$DarknessChose$");
  AddMenuItem("Wurfgegenstand", "ThrowObject", idThrowObject, pClonk,0,0,"$DarknessChose$");
  // Spielregel
  if(GoalIsCompatible()) AddMenuItem("%s", "OpenGoalMenu", GetID(pGoal), pClonk,0,0,"$GoalChose$");
  // Fertig
  AddMenuItem("$Finished$", "ConfigurationFinished", BOOM, pClonk,0,0,"$Finished$");
  */
  inherited();
  
  var pClonk = GetCursor();
  if(!GetLength(aGoals))
  {
	AddMenuItem("%s", "ST", SPTM, pClonk,0,0,"$DarknessChose$");
	AddMenuItem("Wurfgegenstand", "ThrowObject", idThrowObject, pClonk,0,0,"$DarknessChose$");
  }
}

/* Sondermenü: Spawnschutzzeit */

protected func ST(id dummy, int iSelection)
{
  var pClonk = GetCursor();
  // Menü aufmachen
  CreateMenu(GetID(), pClonk, 0,0,0,0, 1);
  // Anzeige
  AddMenuItem("%s", "ST", SPTM, pClonk, SPSeconds, 0, " ");
  // Zähler erhöhen
  AddMenuItem("$MoreST$", "STConf", CHOS, pClonk, 0, +1, "$MoreST$",2,1);//, CHOS, pClonk, 0, +1, "$MoreDarkness$",2,1
  // Zähler senken
  AddMenuItem("$LessST$", "STConf", CHOS, pClonk, 0, -1, "$LessST$",2,2);//, CHOS, pClonk, 0, +1, "$MoreDarkness$",2,1
  // Fertig
  AddMenuItem("$Finished$", "OpenMenu", CHOS, pClonk,0,0, "$Finished$",2,3);
  // Letzten Eintrag auswählen
  SelectMenuItem(iSelection, pClonk);
}

protected func STConf(id dummy, int iChange)
{
  // Stand verändern
  SPSeconds = BoundBy(SPSeconds+iChange, 0, 20);
  // Geräusch
  Sound("Grab", 1,0,0,1);
  // Menü wieder öffnen
  var iSel = 1;
  if(iChange == -1) iSel = 2;
  ST(0, iSel);
}

protected func ThrowObject()
{
  var pClonk = GetCursor();
  // Menü aufmachen
  CreateMenu(idThrowObject, pClonk, 0,0,0,0, 1);
  AddMenuItem("%s", "TO", ROCK, pClonk, 0, 0, " ");
  AddMenuItem("%s", "TO", FLNT, pClonk, 0, 0, " ");
  AddMenuItem("%s", "TO", SFLN, pClonk, 0, 0, " ");
  AddMenuItem("%s", "TO", EFLN, pClonk, 0, 0, " ");
  AddMenuItem("%s", "TO", BALL, pClonk, 0, 0, " ");
  // Letzten Eintrag auswählen
}

static idThrowObject;

func TO(id object)
{
	idThrowObject= object;
	return(OpenMenu());
}


protected func ConfigurationFinished()
{
  Death = true;
  // Regeln erzeugen
  var i = 0, j, pCrew, tmp, log = "$Rules$";
  for(var check in aRules)
    {
    if(check)
      {
      CreateObject(GetDefinition(i, Chooser_Cat), 10,10, -1);
      log = Format("%s, %s", log, GetName(0, GetDefinition(i, Chooser_Cat)));
      }
    i++;
    }
  // Dunkelheit erzeugen
  log = Format("%s, %s x%d", log, GetName(0, DARK), iDarkCount);
  Log(log);

  // Spieler freilassen
  for(i = 0 ; i < GetPlayerCount() ; i++)
    {
    for(j = 0 ; pCrew = GetCrew(GetPlayerByIndex(i), j) ; j++)
      {
      tmp = Contained(pCrew);
      RemoveObject(tmp, 1);
      
      pCrew->~Recruitment();
      }
    for(var rule in FindObjects(Find_Category(Chooser_Cat), Find_Exclude(this())))
      rule->~InitializePlayer(GetPlayerByIndex(i));
    }
  // Überschüssiges TIM1-Objekte entfernen (falls Spieler ziwschenzeitlich geflogen sind)
  for(tmp in FindObjects(Find_ID(TIM1)))
    if(!(tmp->Contents()))
      RemoveObject(tmp, 1);
	  
  // ein schneller GameCall für Einstellungen
  GameCall("ChooserFinished",iDarkCount);
  // Selber entfernen
  RemoveObject();
}