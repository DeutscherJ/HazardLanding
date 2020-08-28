#strict

/* Steuerung */

func IsHangarGate(){return(1);}

public ControlLeft:
  return (Move(COMD_Left()));

public ControlRight:
  return (Move(COMD_Right()));

/* Kontakt */

protected ContactLeft:
  return(Stop());

protected ContactRight:
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
  SetXDir(0); SetYDir(0);
  return(1);

/* Initialisierung */

protected Initialize:
  SetAction("Hold");
  return(1);

protected Damage:
  if ( LessThan( GetDamage(), 1000 ) ) return(0);
  CastObjects(SHRP,3,50,0,-5);
  CastObjects(SHRP,10,30,0,0);
  CastObjects(SHRP,3,40,0,-5);
  CastObjects(SHRP,10,20,0,0);
  RemoveObject();  
  Sound("Discharge");
  Sound("Blast2");
  return(1);