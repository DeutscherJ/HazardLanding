/*-- No Friendly Fire --*/

#strict
//  Sound("Tinnitus",0,0,0,0,1);
protected func Activate(iPlr) {
  MessageWindow(GetDesc(),iPlr);
}

global func RivivalAble(){return(FindObject(RVIV));}

// Kann mittels des Spielzielausw�hlers ausgew�hlt werden
public func IsChooseable() { return(1); }
