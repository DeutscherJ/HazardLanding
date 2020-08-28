/*-- Kartenlesegerät --*/

#strict
#appendto LKEY

public func CheckCard() {
  if(!Contents()) return();

  if(Contents()->GetKeyNumber() & cardid) {
    // es ist die richtige!
    if(target)
	{
		if(IsArray(target))
			for(pObj in target)
				pObj->~Access();
		else target->~Access();
	}

    // Effekt
    Sound("Beep");
    CreateParticle("NoGravSpark", 5, -7, 0, 0, 50, RGBa(0, 255, 0, 50));

    // der Einfachheit halber werden Karten nach Gebrauch zerstört
    // if(Contents()) RemoveObject(Contents());
    // doch nicht
  }
  else {
    // die falsche... :(
    Sound("Error");
    CreateParticle("NoGravSpark", 5, -7, 0, 0, 50, RGBa(255, 0, 0, 50));

    // ausspucken
    if(Contents()) Contents()->Exit();
  }
}