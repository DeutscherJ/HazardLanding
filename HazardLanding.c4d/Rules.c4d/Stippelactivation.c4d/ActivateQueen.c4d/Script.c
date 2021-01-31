#strict

protected func Activate(iPlr) {
  MessageWindow(GetDesc(),iPlr);
}

global func ActiveQueen() {
  return(!ObjectCount(ASQU));
}

public func IsChooseable() { return(!GameCall("NoStippels")); }

func Unchoosable(){	return(!FindObject2(Find_Func("IsStippel"))&&!FindObject2(Find_ID(JT5B)));}