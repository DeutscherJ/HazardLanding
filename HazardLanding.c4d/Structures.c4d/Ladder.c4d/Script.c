/*-- Leiter --*/

#strict

local cons, ladder;

public func ControlDigDouble(pClonk)
{
  [Verankern/Lösen]
  // Lösen
  if (cons) return(Release());  
  // Verankern
  //if (!GBackSolid(0,+11))
    //SetPosition(GetX(),GetY()+11);
  SetSolidMask(0,64,36,4);
  Sound("Connect");
  cons = 1;
  ladder = CreateObject(LADR,0,32,GetOwner());
  ladder->Set(7);
  SetAction("Fixed");
  //SetCategory(3);
  /*for(var x=-16;x<=16;x+=4)
  {
	var p = CreateObject(L1G4,x,-29,GetOwner());
	if(Abs(x)<11) p->~UnSolid();
  }*/
	
  return(1);
}

private func Release(pClonk)
{
  //SetSolidMask();
  cons = 0;
  Sound("Connect");
  SetAction("Idle");
  RemoveObject(ladder);
  return(1);
}

/* Schaden */

protected func Damage()
{
  if (GetDamage() < GetMaxDamage()) return(1);
  return(Destroy());
}

public func Destroy()
{
  RemoveObject(ladder);
  // Fragmente
  var obj, i;
  for (i = 0; i < 5; ++i)
  {
    obj = CreateObject(SFRX, Random(GetObjWidth()) - GetObjWidth() / 2,
                             Random(GetObjHeight()) - GetObjHeight() / 2, GetOwner());
    ObjectCall(obj, "Settings", i, 15);
  }
  // Explosion
  Explode(20);
  return(1);;
}


/* Eigenschaften */

public func GetMaxDamage(){return(75);}
public func IsVehicleProduct(){return(1);}