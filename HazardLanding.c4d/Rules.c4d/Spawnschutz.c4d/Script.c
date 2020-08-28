#strict

static SPSeconds;

protected func Activate(iPlr) {
  MessageWindow(GetDesc(),iPlr);
}

global func SpawnTime() {
  return(ObjectCount(SPSH));
}

// Kann mittels des Spielzielausw�hlers ausgew�hlt werden
public func IsChooseable() {return(1);}
func HasChooseMenu(){return(1);}

protected func RuleCooseMenu(pClonk, int iSelection)
{
	var relaunchObject = FindObject(SPSH);
	if(!relaunchObject) 
		relaunchObject = CreateObject(SPSH,0,0,-1);
  if(!pClonk) pClonk = GetCursor();
  // Men� aufmachen
  CreateMenu(GetID(), pClonk, relaunchObject,0,0,0, 1);
  // Anzeige
  AddMenuItem("%s", "ST", SPTM, pClonk, SPSeconds, 0, " ");
  // Z�hler erh�hen
  AddMenuItem("$MoreST$", "STConf", CHOS, pClonk, 0, +1, "$MoreST$",2,1);//, CHOS, pClonk, 0, +1, "$MoreDarkness$",2,1
  // Z�hler senken
  AddMenuItem("$LessST$", "STConf", CHOS, pClonk, 0, -1, "$LessST$",2,2);//, CHOS, pClonk, 0, +1, "$MoreDarkness$",2,1
  // Fertig
  AddMenuItem("$Finished$", "Ready", CHOS, pClonk,0,0, "$Finished$",2,3);
  // Letzten Eintrag ausw�hlen
  SelectMenuItem(iSelection, pClonk);
}

protected func STConf(id dummy, int iChange)
{
  // Stand ver�ndern
  SPSeconds = BoundBy(SPSeconds+iChange, 0, 20);
  // Ger�usch
  Sound("Grab", 1,0,0,1);
  // Men� wieder �ffnen
  var iSel = 1;
  if(iChange == -1) iSel = 2;
  RuleCooseMenu(0, iSel);
}
public func Ready(pClonk)
{
	FindObject(CHOS)->~OpenMenu();
	return(1);
}
func Destruction()
{
	SPSeconds = 0;
	return(1);
}
func Initialize(a,b,c)
{
  SPSeconds=5;
  return(_inherited(a,b,c));
}