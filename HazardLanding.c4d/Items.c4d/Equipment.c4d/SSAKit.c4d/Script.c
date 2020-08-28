#strict

public func IsWeaponProduct(){return(1);}
public Activate: 
  SetComDir(COMD_Stop(),Par(0));
  SetOwner(GetOwner(),CreateObject(_VT2));
  return(RemoveObject());


protected Hit:
  Sound("RockHit*");
  return(1);


protected func Entrance(pContainer) { SetOwner(GetOwner(pContainer)); return(); }
