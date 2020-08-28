/*-- Flie�band --*/

#strict

local parts;

func Initialize()
{
  //Voreinstellung
  Set(2);
  return(1);
}


/* Mit dieser Funktion wird ein neues Laufband erzeugt. a steht f�r die Anzahl der Teile */
public func Set(a) {CreateProductionLine(a);}


public func SetActions(string s) /* Funktion f�r das Setzen der Aktivit�t aller Teile */
{
  for(var part in parts)
  {
    var i = GetPhase(part);
    part -> SetAction(Format("%s", s));
    part -> SetPhase(i);
  }
}

private func GetActions() /* Abfragen der Aktivit�t aller Teile.. */
{
  for(var part in parts)
    var ans = GetAction(part);
  return(ans);
}


func CreateProductionLine(a) /* Erzeugt ein Flie�band */
{
  //Bei 1 und darunter sowie bei �ber 30 passiert nichts.
  if((a <= 1) || (a > 30)) return(0);
  
  //Flie�band zu gro�?
  if(GetX()+((a/(-2))*40) < 5 || GetX()+((a/2)*40) > LandscapeWidth()-5) {Sound("Error"); Log("Kann Flie�band nicht erzeugen: Flie�band �berschneidet Landschaftsrand."); return(0);}
  
  
  //Alte Teile l�schen:
  if(parts) ClearParts();
  parts = CreateArray();
  
  
  //Mittelst�cke platzieren:
  if(!(a == 2))
  {
    for(var i = ((a-2)/(-2))*40+GetBla(a); i <= ((a-2)/2)*40-GetBla(a); i += 40)
    {
      parts[GetLength(parts)] = CreateObject(PM1C, i, -9, -1);
    }
  }
  //Endst�cke platzieren:
  parts[GetLength(parts)] = CreateObject(PL1C, (a/(-2))*40+GetBla(a), -9, -1);
  parts[GetLength(parts)] = CreateObject(PR1C, (a/2)*40-GetBla(a), -9, -1);
  
  //Allen Teilen Erschaffer �bergeben und erneut initializieren:
  for(var part in parts)
  {
    LocalN("father", part) = this();
    part->Initialize();
  }
  
  SetShape((-a*40)/2+8, -10, a*40-16, 20);
}


func Destruction() /* Bei Zerst�rung Unterobjekte l�schen */
{
  ClearParts();
}


func ClearParts()
{
  for(var part in parts)
    RemoveObject(part);
}


public func ConsoleControl(int i)
{
  if(i == 1) return("$Left$");
  if(i == 2) return("$Right$");
  if(i == 3) return("$Stop$");
}

public func ConsoleControlled(int i)
{
  if(i == 1 && GetActions() ne "Left") SetActions("Left");
  if(i == 2 && GetActions() ne "Right") SetActions("Right");
  if(i == 3 && GetActions() ne "Stop") SetActions("Stop");
}

private func GetBla(a) /* Notwendig - Engine kennt keine Dezimalzahlen, kann also nicht mit 1.5 oder �hnlichem multiplizieren */
{
  if(a==2||a==4||a==6||a==8||a==10||a==12||a==14||a==14||a==16||a==18||a==20||a==22||a==24||a==26||a==28||a==30)
    return(20);
  else return(0);
}
