/*-- Fabrik-Objekt --*/

#strict

local Factory;                         // Objektzeiger
local Product, Endless;                // Herstellung
local CurrentPT, NextStepPT, FullPT;   // Produktionsfortschritt/-dauer
local ProdFactor;                      // spezielle Produktionsdauer in % des Normalwertes


/* Initialisierung */

protected func Initialize()
{
  // Produktion zurücksetzen
  Product = 0;
  Endless = 0;
}

public func Init(par_factory)
{
  Factory = par_factory;
}


/* Steuerung durch die Fabrik */

public func KeyUp(caller)
{
  // einfache Produktion starten
  if (!Product)
    OpenProductionMenu(SYF2,caller);
  // oder bereits begonnene Herstellung fortführen
  else
    ContinueProduction();
}

public func KeyDig(caller)
{
  // Produktionsinfos sofort einblenden
  if (!Product)
    Message("Nichts in Produktion", Factory);
  else
  {
    // erstmal versuchen, Rohstoffe zu holen
    GrabNeededComponents();
    // Anzeigestring aufbauen
    var str = "";
    if (Endless) str = Format("%s (endlos)", GetName(0,Product));
            else str = Format("%s", GetName(0,Product));
    if (NextStepPT == FullPT)
      str = Format("%s|Benötigtes Material vorhanden", str);
    else
    {
      // Auflistung der noch benötigten Materialien
      str = Format("%s|Noch benötigt:", str);
      var i = -1;
      var objID, components, used;
      while (objID = GetComponent(0,++i,0,Product))
      {
        components = GetComponent(objID,0,0,Product);
        used = ContentsCount(objID);
        if (used < components)
          str = Format("%s|%dx %s", str, components-used, GetName(0,objID));
      }
    }
    PlayerMessage(GetOwner(Factory), str, Factory);
  }
  // Auftragsmenü öffnen
  CreateMenu(GetID(Factory),caller,0,0,GetName(Factory),0,1);
  if (Product)
    AddMenuItem("Abbruch","StopProduction",SYF1,caller);
  AddMenuItem("Herstellung...",     "OpenProductionMenu",SYF2,caller,0,caller);
  AddMenuItem("Endlosproduktion...","OpenProductionMenu",SYF3,caller,0,caller);
}


/* Produktionsmenü */

private func OpenProductionMenu(symbol, caller)
{
  // bitte überladen!
}

protected func SelectProduction(productID, factor)
{
  // Auswahl getroffen
  StopProduction();
  NewProduction(productID, factor);
}


/* Produktion */

private func NewProduction(productID, factor)
{
  // Produktion starten
  Product = productID;
  if (factor) ProdFactor = factor;
         else ProdFactor = 100;     // Standard: 100%
  // alles auf Anfang
  CurrentPT = 0;
  NextStepPT = 0;
  FullPT = 0;
  // Produktionszeit berechnen
  var i = -1;
  var j, obj;
  while (obj = GetComponent(0,++i,0,Product))
    for (j = 0; j < GetComponent(obj,0,0,Product); ++j)
      FullPT += GetDefCoreVal("Mass","DefCore",obj) * ProdFactor / 100;
  // Update für Fortschrittsanzeige
  ShowInfoBar(IBRP, Factory, CurrentPT, FullPT, -1);
  // und gleich anfangen
  SetAction("Process");
}

private func ContinueProduction()
{
  // Rohstoffe verarbeiten
  GrabNeededComponents();
  // Produktionspause nötig?
  if ((CurrentPT < FullPT) && (CurrentPT == NextStepPT))
  {
    // bei Endlos: Produktion noch gar nicht begonnen?
    if (!NextStepPT && Endless)
      return(StopProduction());
    // warten und evtl. einen Clonk was besorgen lassen
    SetAction("Wait");
    if (!Endless) AutoAcquire();
    return(1);
  }
  // weiter mit der Herstellung
  if (GetAction() eq "Wait")
    SetAction("Process");
}

public func StopProduction()
{
  // alles raus hier
  var obj;
  while (obj = Contents())
    Enter(Factory,obj);
  // Produktion beendet
  Product = 0;
  CurrentPT = 0;
  NextStepPT = 0;
  FullPT = 0;
  // Anzeige ausblenden
  DisappearInfoBar(IBRP, Factory);
  SetAction("Idle");
}

private func GrabNeededComponents()
{
  // noch benötigte Components holen
  var i = -1;
  var obj, objID;
  var components, used;
  while (objID = GetComponent(0,++i,0,Product))
  {
    components = GetComponent(objID,0,0,Product);
    used = ContentsCount(objID);
    // genug davon da?
    while (used < components)
    {
      // in der Fabrik suchen
      obj = FindContents(objID,Factory);
      if (!obj) break;
      // hier herein verschieben
      Enter(this(),obj);
      NextStepPT += GetDefCoreVal("Mass","DefCore",objID) * ProdFactor / 100;
      ++used;
    }
  }
}

private func FindNeededComponent()
{
  // herausfinden, was noch benötigt wird
  var i = -1;
  var objID;
  while (objID = GetComponent(0,++i,0,Product))
    if (ContentsCount(objID) < GetComponent(objID,0,0,Product))
      return(objID);
  return(0);
}

protected func AutoAcquire()
{
  // Clonk in der Fabrik suchen
  var clonk = FindObject(0, 0,0,0,0, OCF_CrewMember(),"",0, Factory);
  if (!clonk) return(0);
  // was wird gebraucht?
  var objID = FindNeededComponent();
  if (!objID) return(0);
  // Befehle geben
  SetCommand(clonk, "Acquire", 0,0,0,0, objID);             // Rohstoff besorgen
  AppendCommand(clonk, "Put", Factory,0,0,0,1000, objID);   // und in die Fabrik legen
  return(1);
}


/* Action-Calls */

protected func CheckEnergy()
{
  // genug Energie, um weiterzumachen?
  if (NeedEnergy() && (GetEnergy(Factory) < 25))
    return(1);
  // Energie reicht
  SetAction("Process");
}

protected func Waiting()
{
  // Materialien suchen, um weiter produzieren zu können
  GrabNeededComponents();
  // welche gefunden?
  if (CurrentPT < NextStepPT)
    SetAction("Process");
}

protected func Process()
{
  // noch genug Energie da?
  if (NeedEnergy() && (GetEnergy(Factory) < 25))
    return(SetAction("CheckEnergy"));
  DoEnergy(-10, Factory);
  // weiter mit der Herstellung, bis Arbeitsschritt fertig
  if (CurrentPT < NextStepPT)
  {
    ++CurrentPT;
    // Update für Fortschrittsanzeige
    ShowInfoBar(IBRP, Factory, CurrentPT,FullPT, 0,1);
    return(DoSmoke());
  }
  // nächsten Schritt anfangen
  if (CurrentPT < FullPT)
    return(ContinueProduction());

  // komplett fertig
  var obj;
  // Aufruf für spezielle Auswertung
  if (!ProductionEndCall(Product)) return(1);
  // Komponenten löschen
  var i = -1;
  var j, objID;
  while (objID = GetComponent(0,++i,0,Product))
  {
    j = GetComponent(objID,0,0,Product) + 1;
    while (--j)
    {
      obj = FindContents(objID);
      if (obj) RemoveObject(obj);
    }
    // gefüllte Fässer: leeres Fass als Ersatz
    if (objID==WBRL || objID==SBRL || objID==OBRL ||
        objID==ABRL || objID==LBRL || objID==DBRL)
    {
      j = GetComponent(objID,0,0,Product) + 1;
      while (--j)
        CreateContents(BARL,Factory);
    }
  }
  // Meldung, dass fertig
  if (FullPT >= 150)
    CreateObject(SE07,0,0,GetOwner()); 
  // bei Endlosproduktion: gleich weiter
  if (Endless) NewProduction(Product, ProdFactor);
          else StopProduction();
}

private func ProductionEndCall(productID)
{
  // überladen, wenn bei Fertigstellung was anderes passieren soll
  var obj = CreateContents(productID, Factory);
  if (!obj) return(0);
  Sound("Pshshsh");
  return(1);
}

private func DoSmoke()
{
  // auch zum Überladen da
}


/* Eigenschaften */

private NeedEnergy: return(FindObject(ENRG));

