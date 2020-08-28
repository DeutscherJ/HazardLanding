/*-- Falle --*/

#strict

public func ControlDown(object switch, int iPlr) { return(Fire(iPlr)); }

func Initialize()
{
	SetClrModulation(RGB(250,200,150));
	return(1);
}

public func Fire(int iPlr, bool fAuto)
{
  if(GetEffect("Reload", this())) return();
  if(iPlr == NO_OWNER && !fAuto) return();

  var x,y,r;
  for(var i=0,arrow ; i < 3 ; i++)
  {
    Coords(x,y,r,i);
    arrow = CreateObject(_ARP, x,y, iPlr);
    arrow->SetR(r);
    arrow->Launch(r, 100, 450, 8, 50, 30);
  }
  Sound("Arrow");
  AddEffect("Reload", this(), 1, 100, this());
}

private func Coords(& x, & y, & r, int i)
{
  if(!i)
    { x = 8; y = -20; r = 93; }
  if(!--i)
    { x =17; y = -13; r = 85; }
  if(!--i)
    { x =27; y =  +8; r =110; }
}

// Timer

protected func AutoFire()
{
  if(Random(2)) Fire(NO_OWNER, true);
}
