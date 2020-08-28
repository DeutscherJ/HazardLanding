/*-- Große Schwebeplatte --*/
#strict

/* Lokale Variablen */

// 0: Horizontale an/aus
// 1: Vertikale an/aus
// 2: ComDir für ResumeTravel, X/Y für SpeedTo
// 3: Y Obergrenze gesetzt
// 4: Y Obergrenze Transfer
// 5: Y Untergrenze Transfer

/* Steuerung */

public ControlCommand:
//  if (Not(GameCall("MainEnergySupply"))) return(Stop());
  // Bewegungskommando vertikal
  if (SEqual(Par(0),"MoveTo"))
    if (Vertical())
      if (Inside(Sub(Par(2),GetX()),-16,+16))
        if (LessThan(Par(3),GetY()))
          return(SetComDir(COMD_Up()));
  if (SEqual(Par(0),"MoveTo"))
    if (Vertical())
      if (Inside(Sub(Par(2),GetX()),-16,+16))
        if (GreaterThan(Par(3),GetY()))
          return(SetComDir(COMD_Down()));
  // Bewegungskommando horizontal
  if (SEqual(Par(0),"MoveTo"))
    if (Horizontal())
      if (Inside(Sub(Par(3),GetY()),-16,+16))
        if (LessThan(Par(2),GetX()))
          return(SetComDir(COMD_Left()));
  if (SEqual(Par(0),"MoveTo"))
    if (Horizontal())
      if (Inside(Sub(Par(3),GetY()),-16,+16))
        if (GreaterThan(Par(2),GetX()))
          return(SetComDir(COMD_Right()));
  // Andere Kommandos nicht auswerten
  return(0);

public ControlUp:
  if (Not(GameCall("MainEnergySupply"))) return(Stop());
  Sound("Click");
  if (Not(Vertical())) return(Stop());
  SetComDir(COMD_Up());
  SetXDir(0);
  SetAction("Travel");
  return(1);

public ControlDownSingle:
  if (Not(GameCall("MainEnergySupply"))) return(Stop());
  Sound("Click");
  if (Not(Vertical())) return(Stop());
  SetComDir(COMD_Down());
  SetXDir(0);
  SetAction("Travel");
  return(1);

public ControlLeft:
  if (Not(GameCall("MainEnergySupply"))) return(Stop());
  Sound("Click");
  if (Not(Horizontal())) return(Stop());
  SetComDir(COMD_Left());
  SetYDir(0);
  SetAction("Travel");
  return(1);

public ControlRight:
  if (Not(GameCall("MainEnergySupply"))) return(Stop());
  Sound("Click");
  if (Not(Horizontal())) return(Stop());
  SetComDir(COMD_Right());
  SetYDir(0);
  SetAction("Travel");
  return(1);

/* Kontakt */

protected ContactTop:
  if (Not(Vertical())) return(Stop());
  Wait(COMD_Down());
  return(1);

protected ContactBottom:
  if (Not(Vertical())) return(Stop());
  if (And(Horizontal(),Vertical())) return(Stop()); 
  Wait(COMD_Up());
  return(1);

protected ContactLeft:
  if (Not(Horizontal())) return(Stop());
  Wait(COMD_Right());
  return(1);

protected ContactRight:
  if (Not(Horizontal())) return(Stop());
  Wait(COMD_Left());
  return(1);

/* Konfiguration */

public EnableHorizontal:   
  return(SetLocal(0,1));

public DisableHorizontal:   
  return(SetLocal(0,0));

public EnableVertical:   
  return(SetLocal(1,1));

public DisableVertical:
  return(SetLocal(1,0));

private Horizontal:
  return(Local(0));

private Vertical:
  return(Local(1));

public SetYTop:
  return(SetLocal(3,Par(0)));
  
private YTop:
  return(Local(3));

func Bling()
{
	if(GameCall("MainEnergySupply"))
	{
		CreateParticle("PSpark",0,-6,0,0,60,RGBa(255,64,0,50),this());
		if(IsDark()) AddLightFlash(250,0,-6,RGBa(255,100,100,50),this());
		DigFreeRect(GetDefCoreVal("Offset", "DefCore",GetID(),0)+GetX(),GetDefCoreVal("Offset", "DefCore",GetID(),1)+GetY(),GetDefCoreVal("Width", "DefCore",GetID(),0),GetDefCoreVal("Height", "DefCore",GetID(),0)+2);
	}
	return(1);
}

/* Kommandos */

private Stop:
  SetAction("Travel");
  SetComDir(COMD_Stop());
  SetXDir(0); SetYDir(0);
  return(1);

private Wait: // Par(0) ist anschließende ComDir
  Stop();
  // Aktion Wait ruft als EndCall ResumeTravel auf
  SetAction("Wait"); 
  // ResumeTravel benutzt Local(2) als ComDir
  SetLocal(2,Par(0)); 
  return(1);  

private ResumeTravel: // EndCall von Aktion Wait
  SetAction("Travel");
  SetComDir(Local(2));
  return(1);

private Automatic: // EndCall von Aktion Travel
  // Keine Automatik, wenn ein Clonk mitfährt
  if (Passenger()) return(0); 
  // Zu einem wartenden Clonk hinfahren
  if (SpeedToVertical()) return(1);
  // Eigenständige Bewegung beginnen
  if (SelfTravel()) return(1);
  return(0);

private SelfTravel:
  // Nur wenn angehalten
  if (Not(Equal(GetComDir(),COMD_Stop()))) return(0);
  // Eigenständige Bewegung je nach zugelassener Richtung beginnen
  if ( And( Horizontal(), Not(Vertical()) ) ) SetComDir(COMD_Left());
  if ( And( Vertical(), Not(Horizontal()) ) ) SetComDir(COMD_Up());
  if ( And( Vertical(), Horizontal() ) ) SetComDir(COMD_Down());
  return(1);

private SpeedToVertical:
  if (!GameCall("MainEnergySupply")) return(Stop());
  if (Vertical()&&Horizontal()) return(0);
  if (!Vertical()) return(0);
  if (!SetVar(0,FindObject(0, -50,-1000,100,2000, OCF_CrewMember(),0,0,NoContainer()))) return(0);
  if (GetComDir(Var(0))!=COMD_Stop()) return(0);
  if (GetProcedure(Var(0)) eq "ATTACH") return(0);
  SetAction("SpeedToY");
  SetLocal(2, Max( GetY(Var(0)), Sum(YTop(),-10) ) ); // Speed to target y or YTop
  return(1);

/* Aktion */

private CheckYTop: // PhaseCall von Travel
  if (GreaterThan( GetY(), Sum(YTop(),-10) )) return(0);
  ForcePosition(this(),GetX(),Sum(YTop(),-10));
  ContactTop();
  return(1);

private SpeedToY: // StartCall von SpeedToY
  SetYDir(BoundBy(Sub(Local(2),GetY()),-50,+50));
  if (Inside(Sub(Local(2),GetY()),-4,+2)) Stop();
  return(1);

private SpeedToX: // StartCall von SpeedToX
  SetYDir(0);
  SetXDir(BoundBy(Sub(Local(2),GetX()),-50,+50));
  if (Inside(Sub(Local(2),GetX()),-10,+10)) Stop();
  return(1);

/* Status */

private Passenger:
  return( FindObject(0, -24,-13,48,16, OCF_CrewMember(),0,0,NoContainer()) );

/* Initialisierung */

protected Initialize:
  SetAction("Travel");
  return(1);
  
/* Transfer */

protected UpdateTransferZone:
  // Nur vertikale Schwebeplatten
  if (Local(0)) return(0);
  // Obergrenze ermitteln
  while (And( GreaterThan(Sum(GetY(),Var(0)),5), Not(GBackSolid(0,Var(0))) ))
    SetVar(0,Sum(Var(0),-5));
  // Untergrenze ermitteln
  while (And( LessThan(Sum(GetY(),Var(1),15),Sub(LandscapeHeight(),5)), Not(GBackSolid(0,Sum(Var(1),15))) ))
    SetVar(1,Sum(Var(1),+5));
  // Transferzone setzen
  SetTransferZone(-23,Var(0),48,Sum(Sub(Var(1),Var(0)),10));
  // Ober- und Untergrenze speichern
  SetLocal(4,Sum(GetY(),Var(0)));
  SetLocal(5,Sum(GetY(),Var(1)));
  return(1);
    
protected ControlTransfer: // C4Object* pObj, int iTx, int iTy
  
  // Durchgang am Boden des Fahrstuhlschachts: nicht warten
  if (Inside(Sub(GetY(Par(0)),Local(5)),-10,+10))
    if (Inside(Sub(Par(2),Local(5)),-10,+10))
      return(0);

  // Zielposition
  SetVar(1,Par(2));
  
  // Maximale Obergrenze
  SetVar(1,Max(Var(1),Local(4)));

  // Fahrstuhl mit Clonk an Zielposition: anhalten, erledigt
  if (Inside(Sub(Var(1),GetY()),-5,+5))
    if (Passenger())
      return(0,Stop());

  // Fahrstuhl noch nicht beim Clonk: warten
  if (Not(Inside(Sub(GetY(),GetY(Par(0))),-15,+15)))
    return(1);

  // Fahrstuhl nur in der Mitte anfassen
  if (Not(Inside(Sub(GetX(),GetX(Par(0))),-15,+15)))
    return(AddCommand(Par(0),"MoveTo",this(),0,0,0,15));

  // Fahrstuhl anfassen
  if (Not( And(SEqual(GetAction(Par(0)),"Push"),Equal(GetActionTarget(0,Par(0)),this())) ))
    return(AddCommand(Par(0),"Grab",this()));
  
  // Fahrstuhl zur Zielposition steuern
  if (LessThan(Var(1),GetY())) 
    return(SetComDir(COMD_Up()));  
  return(SetComDir(COMD_Down()));

func Damage()
{
  if ( LessThan( GetDamage(), 300 ) ) return(0);
  
  CastObjects(SHRP,3,50,0,-5);
  CastObjects(SHRP,10,30,0,0);
  CastObjects(SHRP,3,40,0,-5);
  CastObjects(SHRP,10,20,0,0);
  
  var broken= CreateObject(BLFP);
  SetPosition(GetX(),GetY(),broken);
  SetRDir(RandomX(-2,2),broken);
  LocalN("x",broken)=GetX();
  LocalN("y",broken)=GetY();
  Local(0,broken)=Local(0);
  Local(1,broken)=Local(1);
  Local(2,broken)=Local(2);
  Local(3,broken)=Local(3);
  Local(4,broken)=Local(4);
  Local(5,broken)=Local(5);
  
  RemoveObject();
  Sound("Blast2");
  return(1);
}

func Set()
{
	//SetLocal(3,Par(0))
	EnableVertical();
	DisableHorizontal();
	var xLeft = -GetDefCoreVal("Width", "DefCore", GetID())/2-3;
	var xRight = GetDefCoreVal("Width", "DefCore", GetID())/2+3;
	Local(4)=FindSolidInAngle(GetX(),GetY(),0,2);//Obere Deckenkante
	Local(5)=FindSolidInAngle(GetX(),GetY(),180,2);
	Local(3)=Min(FindSolidInAngle(GetX()+xLeft,Local(4),180,2),FindSolidInAngle(GetX()+xRight,Local(4)+5,180,2));//Von der Decke aus an den Aufzugseiten, erste Stufe suchen
	return(1);
}

Energie:
  if (!GameCall("MainEnergySupply")) return(Stop());
  if (GameCall("MainEnergySupply")) return(SetAction("Travel"));
  return(0);