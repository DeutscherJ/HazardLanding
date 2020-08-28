#strict

protected func Activate(iPlr) {
  MessageWindow(GetDesc(),iPlr);
}

global func FallDamage() {
  return(ObjectCount(FLDM));
}

// Kann mittels des Spielzielauswählers ausgewählt werden
public func IsChooseable() { return(1); }
