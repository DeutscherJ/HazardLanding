/*-- Br�ckensegment --*/

#strict

local cons;   // frei oder verankert?


/* Initialisierung */

protected Initialize:
  // Im Freien erzeugte Br�ckensegmente sind verankert
  if (!Contained())
  {
    SetSolidMask(0,0,72,3);
    cons = 1;
  }
  return(1);

protected Entrance:
  // Im Beh�lter: l�sen
  SetSolidMask();
  cons = 0;
  return(1);

public ControlDigDouble:
  [Verankern/L�sen]
  // L�sen
  if (cons) return(Release());  
  // Verankern
  if (!GBackSolid(0,+11))
    SetPosition(GetX(),GetY()+11);
  SetSolidMask(0,0,72,3);
  Sound("Connect");
  cons = 1;
  return(1);

private Release:
  SetSolidMask();
  cons = 0;
  Sound("Connect");
  // Aus der Erde l�sen
  var i;
  while (Stuck() && ++i < 12)
    SetPosition(GetX(),GetY()-1);
  return(1);


/* Schaden */

protected Damage:
  if (GetDamage() < GetMaxDamage()) return(1);
  return(Destroy());

public Destroy:
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
  return(1);


/* Eigenschaften */

public GetMaxDamage: return(75);
public IsVehicleProduct: return(1);