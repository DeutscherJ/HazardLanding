/*-- Fackel --*/

#strict
public func Initialize()
{
	Activate();
	SetDir(Random(2));
	SetPlrViewRange(50);
	AddFireLight(400,RGBa(255,180,150,30),this(),20);
	CreateSight(this(),50,100);
	return(1);
}
public func Activate()
{
  if(GetAction() S= "Burning") return(Extinguishsh());
  SetAction("Burning");
  return(this() );
}
  
private func Extinguishsh()
{
  SetAction("Idle");
  Sound("Pshshsh");
  return(1);
}

func ControlDigDouble(pClonk)
{
	Extinguishsh();
	RemoveObject();
	CreateObject(FCKL,0,0,GetOwner(pClonk));
	return(1);
}