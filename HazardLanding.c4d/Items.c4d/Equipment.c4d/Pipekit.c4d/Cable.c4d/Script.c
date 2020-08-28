/*--- Datenkabel ---*/

#strict

/* Locals */

// 0,1: Farben
// 2,3: Verbindungsvertices

protected func Initialize()
{
  // Local 0 und 1 sind die Lininenfarben
  SetLocal(0,55); //m�gliche Zahlen 11(gr�n) 12(blau) 55(hellgr�n) 97-99(sch�nes blau)
  SetLocal(1,66);  
  // Die ersten beiden Vertices auf aktuelle Position legen
  SetVertex(0,0,GetX()); SetVertex(0,1,GetY());
  SetVertex(1,0,GetX()); SetVertex(1,1,GetY());
}

global func PipeConnect(pObj1,pObj2)
{
	var cable= CreateObject(DTA_);
	ObjectSetAction(cable,"Connect",pObj1,pObj2);
	return(cable);
}