/*-- Tageszeiten --*/

#strict

/* Locals */

//   0: Geschwindigkeit 1-10
//   1: Tageszeit 0-TimeResolution (Mittag-Mittag)
//   2: Helligkeit 0-100
// 4,5: Hilfsobjekte (Abwärtskompatiblität)
// 6-25: Himmelsfarben (Abwärtskompatiblität)

local SkyAdjustOrig;

private func TimeResolution() { return(10000); }
private func DayTimeLength() { return(TimeResolution() / 2); }

/* Verzögerte Initialisierung */

protected func Initialize()
{
  SetAction("Initialize");
  // Starthelligkeit
  Local(2) = 100;
  return(1);
}

private func Initialized()
{
  // Geschwindigkeit ermitteln
  Local() = ObjectCount(GetID()) + 1;
  // Andere Objekte des gleichen Typs entfernen
  var pOther;
  while(pOther = FindObject(GetID()))
    RemoveObject(pOther);
  // Steuerungsaktion
  SetAction("Time");
  // Fertig
  return(1);  
}
  
/* Helligkeitsberechnung */
private func GetLightIntensity(iTime)
{
  return BoundBy(Cos((iTime * 360) / TimeResolution(), 250) - Cos((DayTimeLength() * 180) / TimeResolution(), 300), -50, 50) + 50;
}
  
/* Konfiguration */

public func SetTime(iTime) // 0 bis 100 = Mittag bis Mittag
{
  // Zeit setzen
  Local(1) = iTime * TimeResolution() / 100;
  // Helligkeit anpassen
  RestoreSkyColors(Local(2) = GetLightIntensity(Local(1)));
  return(1);
}
  
/* Zeitverlauf */  

private func Timing()
{
  // Zeitfortschritt
  Local(1) = (Local(1) + Local(0)) % TimeResolution();
  // Helligkeit nach Tageszeit berechnen
  var iIntensity = GetLightIntensity(Local(1));
  // Helligkeit und Himmelsfarbe anpassen
  if (iIntensity > Local(2)) RestoreSkyColors(++Local(2));
  if (iIntensity < Local(2)) RestoreSkyColors(--Local(2));
  
  var bla = FindObjects(Find_Func("DaytimeControlled",Local(2)));
  // Fertig
  return(1);
}
  
protected func UpdateTransferZone()
{
  // Kleiner Trick, damit der Himmel nach dem Laden aktualisiert wird
  if (GetAction() S= "Time") 
    RestoreSkyColors(Local(2));
  return(0);  
}
  
/* Status */

global func IsDay()
{
  var pTime; 
  if (!(pTime = FindObject(TIME))) return(1);
  if (Local(2, pTime)) return(1);
  return(0);
}
  
global func IsNight()
{
  return(!IsDay());
}
  
global func IsDusk()
{
  return(!IsBrightDay());
}

global func IsBrightDay()
{
  var pTime; 
  if (!(pTime = FindObject(TIME))) return(1);
  if (Local(2, pTime)==100) return(1);
  return(0);
}

global func GetDaytime()
{
  var pTime; 
  if (!(pTime = FindObject(TIME))) return(1);
  return(Local(1, pTime));
  return(0);
}

/* Himmelsfarbe */

private func RestoreSkyColors(iPercent)
{
	if(iPercent<100)
	{
		if(!FindObject(DARK)) CreateObject(DARK);
		var dark = FindObject(DARK);
		SetDarkness(10-iPercent/10);
	}
	else
		RemoveAll(DARK);
	return(1);
}