#strict

protected func Activate(iPlr) {
  MessageWindow(GetDesc(),iPlr);
}

global func ActiveMoff() {
  return(!ObjectCount(ASMO));
}

// Kann mittels des Spielzielauswählers ausgewählt werden
public func IsChooseable() { return(!GameCall("NoStippels")); }
func Unchoosable(){	return(!FindObject2(Find_Func("IsStippel"))&&!FindObject2(Find_ID(JT5B)));}