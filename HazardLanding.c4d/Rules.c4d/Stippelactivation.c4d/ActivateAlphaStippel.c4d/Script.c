#strict

protected func Activate(iPlr) {
  MessageWindow(GetDesc(),iPlr);
}

global func ActiveAlphaStippel() {
  return(!ObjectCount(ASAS));
}

// Kann mittels des Spielzielausw�hlers ausgew�hlt werden
public func IsChooseable() { return(!GameCall("NoStippels")); }
