/*-- Schwebelift --*/
// (Dieses Script wird von den Liften von SLC und CoAl gemeinsam genutzt)

#strict

local AutoMode, AutoMoveDir;    // Dauerbetrieb: an/aus-Schalter, Richtung
local RangeTop, RangeBottom;    // Ober- und Untergrenze
local Liftdock;                 // Zeiger auf Liftdock

func IsElevator(){return(1);}

/* Initialisierung */

protected func Initialize()
{
  SetAction("Wait");
  UpdateRangeTop();
  UpdateRangeBottom();
  return(1);
}

public func SetOwnerObject(dock)
{
  Liftdock = dock;
  return(1);
}

private func UpdateRangeTop()
{
  RangeTop = GetY();
  UpdateTransferZone();
  return(1);
}

private func UpdateRangeBottom()
{
  var x = GetX();
  var y = GetY();
  while (PathFree(x, y, x, y+5) && (y < LandscapeHeight()))
    y += 5;
  RangeBottom = y+5;
  UpdateTransferZone();
  return(1);
}


/* Timer-Call */
func NeedLiftDock(){return(1);}
protected func Activity()
{
  // kein Liftdock da?
  if (!Liftdock && NeedLiftDock())
    return(Message("kein Lift!",this()));
  // keine Energie und nicht im Liftdock?
  if (HasEMP(Liftdock) || NoEnergy() && ((GetY()-RangeTop) > 5))
    return(SetYDir());
  // Lore fassen
  GrabLorry();
  
  // Objekte nach oben 
  var obj; 
  while (obj = FindObject(0, -23,0,45,10, OCF_Collectible(),0,0,NoContainer(),obj))
  {
    SetPosition(GetX(obj),GetY()+5,obj);
	SetSpeed(0, GetYDir() / 20, obj);
  }
    
  // zu wartenden Clonks fahren
  if (!AutoMode && !Passenger() && !GetCommand())
    MoveToWaitingClonk();
  // Sicherheitscheck: Bewegung ohne Kommando nur bei Schachtbohrung
  if (GetComDir())
    if (!GetCommand() && (GetAction() ne "Drill"))
      {Halt(); Message("angehalten",this()); }
  // fertig
  return(1);
}

private func MoveToWaitingClonk()
{
  if (HasEMP(Liftdock)) return(1);
  var pWaiting;
  // wartenden Clonk finden
  for(var clonk in FindObjects(Find_OCF(OCF_CrewMember),Find_InRect(-60, RangeTop-GetY(), 120, RangeBottom-RangeTop),Find_NoContainer()))
  {
	  // wartet der Clonk auch?
	  if (GetComDir(clonk) != COMD_Stop()) continue;
	  if (GetAction(clonk) ne "Walk"  && GetAction(clonk) ne "ArmedWalk" &&
		  GetAction(clonk) ne "Push"  && GetAction(clonk) ne "Swim" &&
		  GetAction(clonk) ne "Scale" && GetAction(clonk) ne "Hangle" &&
		  GetAction(clonk) ne "WalkArmed") continue;
	  // nicht bei verfeindeten Clonks
	  if (Hostile(GetController(clonk), GetOwner())) continue;
	  pWaiting = clonk;
  }
  // Weg muss frei ist
  //if (GetY(clonk) < GetY())  if (!PathFree(GetX(), GetY(),    GetX(), GetY(clonk)))    return(0);
  //if (GetY(clonk) > GetY())  if (!PathFree(GetX(), GetY()+PlateHeight()/2, GetX(), GetY(clonk))) return(0);
  // Zielposition setzen und starten
  if(pWaiting)
	SetMoveTo(GetY(pWaiting));
  return(1);              
}

private func GrabLorry()
{
  // Lore anfassen
  if (GetAction() ne "Wait") return(0);
  /*var lorry = FindObject(LORY, -12,-12, 25,35);
  if (!lorry) return(0);
  
  // Wenn ein Clonk dabei ist, nichts tun
  if (FindObject(0,-PlateWidth()/2,-PlateHeight(),PlateWidth(),PlateHeight(),OCF_CrewMember(),"Push",FindObject(LORY))) return(0);
  // Lore positionieren
  SetPosition(GetX(), GetY()-2, lorry);
  SetR(0, lorry);    SetRDir(0, lorry);
  SetXDir(0, lorry); SetYDir(0, lorry);
  */
  
  // Fahrzeuge
  var pObject;
  while (pObject = FindObject(0, -12, -12, 25, 35, OCF_Grab(), 0, 0, NoContainer(), pObject)) 
  {
    // Objekt passt in den Fahrstuhlkorb
    if (FitsInElevator(pObject)) 
    {
      if (!(GetCategory(pObject) & C4D_Vehicle())) continue;
      if (!Inside(GetXDir(pObject, 100), -1, +1)) continue;
      if (pObject->~IsTree() && GetCon(pObject) >= 50) continue;
      if (GetX(pObject) == GetX() && GetY(pObject) == GetY() + 1) continue;
      if (pObject->~IsElevator() ) continue;
      if (GetProcedure(pObject) eq "FLOAT") continue;
      
      GrabAdjustPosition(pObject);
    }
  }
  
  return(1);
}

private func FitsInElevator(pObject)
{
  // Alle (ungedrehten) Vertices des Objekts pr�fen
  var vertexCount = GetDefCoreVal("Vertices", "DefCore", pObject->GetID());
  for (var i = 0; i < vertexCount; i++) 
  {
    var vertexX = GetDefCoreVal("VertexX", "DefCore", pObject->GetID(), i);
    var vertexY = GetDefCoreVal("VertexY", "DefCore", pObject->GetID(), i);
    // Passt nicht
    if (!Inside(vertexX, -PlateWidth()/2+3, PlateWidth()/2-3) || !Inside(vertexY, -20, 15)) return(0);
  }
  // Passt
  return(1);  
}

private func GrabAdjustPosition(obj) 
{
  var offset = (GetObjHeight(this()) - GetObjHeight(obj)) / 2 - 1;
  var x = GetX();

  if (GetCategory(obj) & C4D_Object()) 
  {
    if(GetOCF(obj) & OCF_HitSpeed1() ) return(0);
    offset = 8 + GetYDir() / 10;
    x = GetX(obj);
  }
  else if (obj->~IsLorry())
    offset = -1 + GetYDir() / 10;
  
  SetSpeed(0, GetYDir() / 20, obj); SetRDir(0, obj);
  SetR(0, obj);
  SetPosition(x, GetY() + offset-2, obj);
}

private func SetMoveTo(position)
{
  // keine Energie
  if (NoEnergy() || HasEMP(Liftdock)) return(1);
  // los geht's
  SetAction("Travel"); 
  var Dir = 0;
  if (position > GetY())  Dir = +4;
  if (position < GetY())  Dir = -5;
  SetCommand(this(),"MoveTo", 0, GetX(), Max(position, RangeTop)+Dir);
  SetYDir(0);
  return(1);
}

public func Halt()
{
  // kein Liftdock da?
  if (!Liftdock && NeedLiftDock())
    return(SetAction("Idle"));
  // keine Energie und nicht im Liftdock?
  if (HasEMP(Liftdock) || NoEnergy() && !Inside(GetY()-GetY(Liftdock), -4, -1))
    return(SetYDir(0));
  // anhalten
  SetAction("Wait");
  SetCommand(this(),"None");
  SetComDir(COMD_Stop());
  SetYDir(0);
  if (GetY() > RangeBottom) UpdateRangeBottom();
  return(1);
}


/* Action-Calls */

private func Drilling()
{
  if (HasEMP(Liftdock)) Halt();
  // Steuermann verloren?
  if (!FindObject(0,0,0,0,0,OCF_CrewMember(),"Push",this()) &&
      !FindObject(0,0,0,0,0,OCF_CrewMember(),"Push",FindObject(LORY)))
    Halt();
  return(1);
}

private func Waiting()
{
  // Dauerbetrieb: selbst�ndig losfahren
  if (AutoMode == 1)
    SelfMovement();
  return(1);
}

private func SelfMovement()
{
  if (HasEMP(Liftdock)) return(1);
  // Selbst�ndig rauf- bzw. runterfahren
  if (AutoMoveDir)  SetMoveTo(RangeTop);
  if (!AutoMoveDir) SetMoveTo(LandscapeHeight()-12);
  AutoMoveDir = !AutoMoveDir;
  return(1);
}

/* Commands auswerten */

protected func ControlCommand(Cmd, Target, Tx, Ty)
{
  if (HasEMP(Liftdock)) return(0);
  if (!Liftdock && NeedLiftDock()) return(0);
  // nur Bewegungskommando auswerten
  if (Cmd ne "MoveTo")
    return(0);
  // Ziel einstellen
  if (Inside(Tx, GetX()-15, GetX()+15))
    return(SetMoveTo(Ty));
  return(0);
}

protected ControlCommandFinished:
  return(Halt());


/* Steuerung */

public func ControlDownSingle(clonk)
{
  [Abw�rts]
  // kein Liftdock oder keine Energie?
  if (!Liftdock && NeedLiftDock())  return(0);
  if (NoEnergy() || HasEMP(Liftdock)) return(0);
  Sound("Click");
  // verfeindet?
  if (Hostile(GetController(clonk), GetOwner())) return(0);
  // nach unten fahren
  SetMoveTo(LandscapeHeight()-12);
  return(1);
}

public func ControlUp(clonk)
{
  [Ausw�rts]
  // kein Liftdock oder keine Energie?
  if (!Liftdock && NeedLiftDock())  return(0);
  if (NoEnergy() || HasEMP(Liftdock)) return(0);
  Sound("Click");
  // verfeindet?
  if (Hostile(GetController(clonk), GetOwner())) return(0);
  // nach oben fahren
  SetMoveTo(RangeTop);
  return(1);
}

public func ControlLeft(clonk)
{
  [Anhalten]
  return(DoControlStop(clonk));
}

public func ControlRight(clonk)
{
  [Anhalten]
  return(DoControlStop(clonk));
}

private func DoControlStop(clonk)
{
  // nicht reagieren, wenn kein Liftdock da
  if (!Liftdock && NeedLiftDock()) return(0);
  Sound("Click");
  // verfeindet?
  if (Hostile(GetController(clonk), GetOwner())) return(0);
  // anhalten
  return(Halt());
}

public func ControlDigDouble(clonk)
{
  [Schachtbohrung]
  // kein Liftdock oder keine Energie?
  if (!Liftdock && NeedLiftDock())  return(0);
  if (NoEnergy() || HasEMP(Liftdock)) return(0);
  Sound("Click");
  // verfeindet?
  if (Hostile(GetController(clonk), GetOwner())) return(0);
  // kurz anhalten
  SetYDir(0);
  SetCommand(this(),"None");
  // jetzt wird gegraben
  SetAction("Drill");
  SetComDir(COMD_Down());
  return(1);
}

public func ControlThrow(clonk)
{
  [Dauerbetrieb]
  // ohne Liftdock geht da nix
  if (!Liftdock && NeedLiftDock()) return(0);
  if (HasEMP(Liftdock)) return(Sound("Error"));
  Sound("Click");
  // verfeindet?
  if (Hostile(GetController(clonk), GetOwner())) return(0);
  AutoMode = !AutoMode;
  if (AutoMode) Message("Dauerbetrieb an", this());
           else Message("Dauerbetrieb aus", this());
  return(1);
}


/* Kontakt */

protected func ContactBottom()
{
  Halt();
  UpdateRangeBottom();
  return(1);
}

protected ContactTop:
  return(Halt());

private Passenger:
  return(FindObject(0, -PlateWidth()/2+2,-PlateHeight()/2, PlateWidth()-4,PlateHeight(), OCF_CrewMember(),0,0,NoContainer()));

private NoEnergy:
	if(NeedLiftDock())
		return(!GetEnergy(Liftdock));
	else
		return(0);


/* Transfer */

protected func UpdateTransferZone()
{         
  if (!Liftdock && NeedLiftDock())
    return(SetTransferZone());
  var dockY = GetY(Liftdock);
  SetTransferZone(-(PlateHeight()-2), dockY-GetY(), PlateWidth(), RangeBottom-dockY+12);
  return(1);
}

protected func ControlTransfer(clonk, Tx, Ty)  
{
  // Durchgang am Boden des Fahrstuhlschachts: nicht warten
  if (Inside(GetY(clonk)-RangeBottom, -10, +10))
    if (Inside(Ty-RangeBottom, -10, +10))
      return(0);
  // Maximale Obergrenze Zielposition durch Fahrstuhl
  if (!Liftdock && NeedLiftDock()) return(0);
  Ty = Max(Ty, GetY(Liftdock)+15);
  // Fahrstuhl an Zielposition: erledigt
  if (Inside(Ty-GetY(), -5, +5))
    return(0);
  // Fahrstuhl f�hrt: warten
  if (GetAction() ne "Wait")
    return(1);
  // Fahrstuhl noch nicht beim Clonk: warten
  if (!Inside(GetY()-GetY(clonk), -5, +5))
    return(1);
  // Fahrstuhl nur in der Mitte anfassen
  if (!Inside(GetX()-GetX(clonk), -5, +5))
    return(AddCommand(clonk,"MoveTo",this()));
  // Fahrstuhl anfassen
  if (GetAction(clonk) ne "Push" || GetActionTarget(0,clonk) != this())
    return(AddCommand(clonk,"Grab",this()));
  // Fahrstuhl zur Zielposition steuern
  return(SetMoveTo(Ty));
}


/* Schaden */

protected func Damage()
{
  if (GetDamage() < GetMaxDamage()) return(1);
  return(Destroy());
}

protected func Hit2()
{
  // Aufprall auf den Boden
  if (NoEnergy()) return(Destroy());
  return(0);
}

public func Destroy()
{
  // Explosion
  Explode(20);
  return(1);
}

/* zu �berladende Funktionen f�r individuelle Objektdaten*/

protected func PlateHeight()
{
  return(1);
}

protected func PlateWidth()
{
  return(1);
}

protected func GetMaxDamage()
{
  return(1);
}

/* Eigenschaften */

public IsElevator: return(1);
