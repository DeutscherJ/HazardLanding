#strict


func IsGate(){return(1);}

/* Steuerung */

public ControlLeft:
  return (Move(COMD_Up()));

public ControlRight:
  return (Move(COMD_Down()));

/* Kontakt */

protected ContactTop:
  return(Stop());

protected ContactBottom:
  return(Stop());

/* Kommandos */

private Move:
  Sound("HangarOpen");
  SetAction("Travel");
  SetComDir(Par(0));
  SetYDir(0);
  return(1);  

private Stop:
  Sound("HangarClose");
  SetAction("Hold");
  SetComDir(COMD_Stop());
  SetXDir(0);
  SetYDir(0);
  return(1);

/* Initialisierung */

protected func Initialize()
{
  SetAction("Hold");
  //UpdateTransferZone();
  return(1);
}

protected Damage:
  if ( LessThan( GetDamage(), 250 ) ) return(0);
  CastObjects(SHRP,3,50,0,-5);
  CastObjects(SHRP,10,30,0,0);
  CastObjects(SHRP,3,40,0,-5);
  CastObjects(SHRP,10,20,0,0);
  RemoveObject();  
  Sound("Discharge");
  Sound("Blast2");
  return(1);

func IsClosed()
{
	return(GetContact()&CNAT_Bottom);
}

//Wenn ein durch die Wegfindungsroutine gesteuertes Objekt (pObj) die Transferzone dieses Objekts zum Zielpunkt iTx/iTy passieren möchte. Die Transferfunktion kann dem Objekt entsprechende Kommandos geben und sollte bei erfolgreicher Bearbeitung TRUE zurückliefern. Siehe auch SetTransferZone(). 