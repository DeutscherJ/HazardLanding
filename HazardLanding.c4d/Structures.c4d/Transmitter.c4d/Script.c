/*-- Energietransmitter --*/

#strict
#include BOB2

local basement, manager;
local iSwitch;


/* Initialisierung */

protected func Initialize()
{
  manager = CreateObject(BMAN,0,0,GetOwner());
  manager->Init(this(), 1);
  // einschalten
  iSwitch = 1;
  SetAction("Transmitting");
}

protected func Construction()
{
  iSwitch = 0;
  basement = CreateObject(BS05,0,+8,GetOwner());
}
  
protected func Destruction()
{
  PreDestruction();
  if (basement) RemoveObject(basement);
}

public func PreDestruction()
{
  if (manager) RemoveObject(manager);
  inherited();
}


/* Steuerung */

protected func ControlUp(clonk)
{
  [Statusanzeige]
  if (!inherited(clonk)) return(1);   // wenn verfeindeter Spieler
  ShowInfoBar(IBRE, this(), GetEnergy(), 100, 5, 1);
  return(1);
}

protected func ControlDig(clonk)
{
  [Ein/Ausschalten]
  if (Hostile(GetController(clonk),GetOwner())) return(1);
  iSwitch = !iSwitch;
  if (!iSwitch) return(Message("ausgeschaltet",this()));
  // eingeschaltet
  SetAction("Transmitting");
  Message("eingeschaltet",this());
  return(1);
}

protected func ControlThrow(clonk)
{
  [Reichweite]
  if (Hostile(GetController(clonk),GetOwner())) return(1);
  var i, marker;
  for (i = 0; i < 72; i++)
  {
    marker = CreateObject(SMK1, Cos(i*5,TransmitterRange()), Sin(i*5,TransmitterRange()), GetOwner(clonk));
    marker->~SetTimer(15);
  }
  Message("Reichweite|wird angezeigt",this());
  return(1);
}


/* Action-Call: Energieübertragung */

protected func Transmit()
{
  // ausgeschaltet oder EMP-Einwirkung
  if (!iSwitch || HasEMP())
    return(SetAction("Idle"));
  // Update für Anzeige
  ShowInfoBar(IBRE, this(), GetEnergy(), 100, 0, 1);
  // keine Energie da?
  if (!GetEnergy())
    return(SetAction("Wait"));
  // Energie senden
  TransmitEnergy();
}

protected func CheckEnergy()
{
  if (!iSwitch || HasEMP()) return(1);
  if (GetEnergy())
    SetAction("Transmitting");
  return(1);
}

public GetSwitch: return(iSwitch);
public EnoughEnergy: return(GetEnergy() || !iSwitch);

public IsEnergyConsumer: return(1);


/* EMP-Reaktion */

public EMP_Reaction:
  DoEnergy(-100);
  return(1);


/* Eigenschaften */

public TransmitterRange: return(600);
public InfoBarSize: return(1);
public GetMaxDamage: return(50);




/* TimerCall (möglichst alle 5 Frames) */

protected func TransmitEnergy()
{
  // Abbruch, wenn Gebäude noch nicht fertig
  if (!(GetOCF() & OCF_Fullcon())) return(0);
  // Verbraucher in Reichweite ermitteln
  var count = 0;
  var need = 0;
  var range = TransmitterRange();
  var obj;
  while (obj = FindObject(0,-range,-range,range*2,range*2, OCF_PowerConsumer(),0,0,0, obj))
    if (obj->~IsEnergyConsumer())
      if (Distance(GetX(),GetY(),GetX(obj),GetY(obj)) <= range) // kreisförmiger Sendebereich
      {
        Var(count) = obj;            // Speicherung in nummerierten Variablen
        need += 100-GetEnergy(obj);  // gesamter Energiebedarf
        ++count;
      }
  // wird etwa nix gebraucht?
  if (!need) return(1);
  // Prozent des Bedarfs, der gedeckt werden kann
  var perc = Min(GetEnergy()*100/need, 100);
  // Energie nach Bedarf verteilen
  var nrg;
  var i = 0;
  for (i; i < count; ++i)
  {
    obj = Var(i);
    nrg = (100-GetEnergy(obj)) * perc/100;
    // Energie senden
    DoEnergy(-nrg);
    DoEnergy(+nrg, obj);
  }
}


/* Standard-Eigenschaften */

public func TransmitterRange() { return(250); }


