#strict

protected func Activate(iPlr) {
  MessageWindow(GetDesc(),iPlr);
}

global func ActiveMiffel() {
  return(!ObjectCount(ASMI));
}

// Kann mittels des Spielzielauswählers ausgewählt werden
public func IsChooseable() { return(!GameCall("NoStippels")); }