/*-- Bodenschalter --*/

#strict

static const _FLS_NeededWeight = 20;
static const _FLS_DownPos      = 4;

local iYPos, fBoolDestoryable;

protected func Timer10()
  {
  // Zielposition nach draufliegendem Gewicht
  var iWgt, obj;
  while (obj = FindObject(0, -25,-30,50,30, 0, 0,0, NoContainer(), obj))
    if (obj->GetContact(0, -1, 8))
      if (~obj->GetCategory() & C4D_StaticBack)
        iWgt += obj->GetMass();
  var iDesiredY;
  if (iWgt >= _FLS_NeededWeight) iDesiredY = _FLS_DownPos;
  // Zielposition erreicht?
  if (iDesiredY == iYPos) return();
  // Kein Ziel? ("Klemmt"!)
  if (!Local())
    {
    iYPos = iDesiredY;
    Sound("ArrowHit");
    Message("$MsgStuck$", this());
    return(1);
    }
  // Sound am Anfang
  if (!iYPos || iYPos == _FLS_DownPos) Sound("Elevator");
  // Nach oben/unten bewegen
  iDesiredY = BoundBy(iDesiredY-iYPos,-1,1);
  while (obj = FindObject(0, -25,-30,50,30, 0, 0,0, NoContainer(), obj))
    if (obj->GetContact(0, -1, 8))
      if (~obj->GetCategory() & C4D_StaticBack)
        obj->SetPosition(obj->GetX(), obj->GetY()+iDesiredY);
  SetPosition(GetX(), GetY()+iDesiredY);
  iYPos += iDesiredY;
  // Angeschlossene Objekte benachrichtigen
  var i; while (obj = Local(i++))
    if (iDesiredY*Local(i++)>0)
      obj->ControlUp(this());
    else
      obj->ControlDown(this());
  // Sound am Ende
  if (!iYPos || iYPos == _FLS_DownPos) Sound("Chuff");
  }

public func AddTarget(object pTarget, int iDir)
  {
  if (!iDir) iDir=1;
  var i; while (Local(i)) ++++i;
  Local(i++) = pTarget; Local(i) = iDir;
  }

public func IsSwitch() { return(true); }
public func FloorDis() { return(6);}
public func HardPlace()
{
	SetPosition((GetX()/10)*10+5,GetY());
	Draw10Rect("Brick-Flat",GetX()/10-3,GetY()/10,7,2);
	Draw10Rect("Wall-Flat",GetX()/10-2,GetY()/10,5,1);
	return(1);
}

func Damage()
{
	if(!fBoolDestoryable) return(0);
	if(GetDamage()>500)
	{
		Split2Components(this());
	}
	return(1);
}