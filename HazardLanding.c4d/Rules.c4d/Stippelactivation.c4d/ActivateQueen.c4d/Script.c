#strict

protected func Activate(iPlr) {
  MessageWindow(GetDesc(),iPlr);
}

global func ActiveQueen() {
  return(!ObjectCount(ASQU));
}

public func IsChooseable() { return(!GameCall("NoStippels")); }
