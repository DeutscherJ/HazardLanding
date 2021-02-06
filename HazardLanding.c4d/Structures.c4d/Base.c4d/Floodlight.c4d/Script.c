/*-- Scheinwerfer --*/

#strict

local pLight, fOn;

protected func Initialize()
{
  pLight = CreateObject(F2G4, 0,0, -1);
	pLight -> Activate(this());
  fOn=1;
}

protected func ControlLeft()
{
	if(fOn)
	{
		pLight->TurnLeft();
		return(1);
	}
	return(0);
}

protected func ControlRight()
{
	if(fOn)
	{
		pLight->TurnRight();
		return(1);
	}
	return(0);
}

protected func ControlUp()
{
	if(fOn)
	{
		pLight->Stop();
		return(1);
	}
	SetYDir(-13);
	return(0);
}

public func ControlDigDouble(pClonk)
{
	fOn=!fOn;
	pLight->Switch();
	pLight->Stop();
	SetComDir(COMD_Stop,pClonk);
	return(1);
}

// Scriptaufruf

public func SetRotation(int iR, int iOwn)
{
  iR = BoundBy(iR, -90, 90);
  SetR(iOwn);

  pLight->SetR(iR+GetR());
  pLight->RotateLight();
}

// Kein Kran darf mich schnappen!
public func NoCrane() { return(1); }
public func HazardBuilding(){return(2);}
public func BasicObject(){return(1);}