/*-- Bodenplatte --*/

#strict

local iSwitchDir, pOppositePlate, iY;

protected func Initialize()
  {
  SetAction("Gate");
  SetComDir(iSwitchDir=COMD_Left);
  }

func Activate(pObj){ControlUp(pObj);}

public func ControlUp(object pController)
  {
  [$DescUp$]
  if (GetComDir() != COMD_Right) Sound("Elevator");
  // Schalter schalten dauerhaft; der Benutzer nur für max. 30 Frames
  if (pController && pController->~IsSwitch()) 
    iSwitchDir = COMD_Right;
  else
    Schedule("SetComDir(iSwitchDir)", 30);
  if(pOppositePlate) pOppositePlate->~ControlUp(pController);
  return(SetComDir(COMD_Right));
  }

public func ControlDown(object pController)
  {
  [$DescDown$]
  if (GetComDir() != COMD_Left) Sound("Elevator");
  // Schalter schalten dauerhaft; der Benutzer nur für max. 30 Frames
  if (pController && pController->~IsSwitch()) 
    iSwitchDir = COMD_Left;
  else
    Schedule("SetComDir(iSwitchDir)", 30);
  if(pOppositePlate) pOppositePlate->~ControlDown(pController);
  return(SetComDir(COMD_Left));
  }

func ControlLeft(pCaller){return(ControlDown(pCaller));}
func ControlRight(pCaller){return(ControlUp(pCaller));}

protected func VerticalFix()
  {
  SetYDir(0);
  SetPosition(GetX(),iY);
  }
  
protected func Hit()
  {
  Sound("Discharge");
  }
