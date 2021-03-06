/*-- Schalter --*/

#strict
/*Jede gerade Lokale stellt das Objeklt dar, welches gesteuert werden soll jede ungerade einen parameter ob aus oder an gemacht werden soll*/


protected func Initialize()
  {
  SetAction("Normal");
  SetPhase(Random(1));
  }

protected func ControlLeft(object pClonk)
  {
  [$DescSwitch$]
  SetOwner(GetOwner(pClonk));
  if (!GetPhase()) return();
  Sound("Click"); SetPhase();
  // Angeschlossene Objekte benachrichtigen
  var i,obj; while (obj = Local(i++))
    if (Local(i++)>0)
      obj->ControlLeft(this());
    else
      obj->ControlRight(this());
  if (Local()) SetPlrView(GetController(pClonk), Local());
  return(true);
  }

protected func ControlRight(object pClonk)
  {
  [$DescSwitch$]
  SetOwner(GetOwner(pClonk));
  if (GetPhase()) return();
  Sound("Click"); SetPhase(1);
  // Angeschlossene Objekte benachrichtigen
  var i,obj; while (obj = Local(i++))
    if (Local(i++)<0)
      obj->ControlLeft(this());
    else
      obj->ControlRight(this());
  if (Local()) SetPlrView(GetController(pClonk), Local());
  return(true);
  }

public func AttachBottom()
  {
  var obj = FindObject(0, 0,13,0,0);
  if (!obj) return();
  // Vertex ankleben
  SetVertex(0, 0, obj->GetX()-GetX()+GetVertex(0, 0, obj));
  SetVertex(0, 1, obj->GetY()-GetY()+GetVertex(0, 1, obj));
  SetAction("Attach", obj);
  return(true);
  }

public func AddTarget(object pTarget, int iDir)
{
	if (!iDir) iDir=1;
	var i;
	while (Local(i)) ++++i;
	Local(i++) = pTarget;
	Local(i) = iDir;
}

public func IsSwitch() { return(true); }

func Schlagable(){return(1);}
func Hammered(pClonk){return(Switch(pClonk));}
func Switch(pClonk)
{
	if(GetPhase())  ControlLeft(pClonk);
	if(!GetPhase()) ControlRight(pClonk);
	return(1);
}