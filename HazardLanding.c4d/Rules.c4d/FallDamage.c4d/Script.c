#strict

protected func Activate(iPlr) {
  MessageWindow(GetDesc(),iPlr);
}

global func FallDamage() {
  return(ObjectCount(FLDM));
}

// Kann mittels des Spielzielausw�hlers ausgew�hlt werden
public func IsChooseable() { return(1); }
