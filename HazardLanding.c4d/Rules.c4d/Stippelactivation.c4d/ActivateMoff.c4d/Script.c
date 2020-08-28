#strict

protected func Activate(iPlr) {
  MessageWindow(GetDesc(),iPlr);
}

global func ActiveMoff() {
  return(!ObjectCount(ASMO));
}

// Kann mittels des Spielzielauswählers ausgewählt werden
public func IsChooseable() { return(!GameCall("NoStippels")); }