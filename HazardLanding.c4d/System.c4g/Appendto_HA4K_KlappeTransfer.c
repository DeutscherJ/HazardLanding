/*-- Appendto für die Bodenklappe
Die Control Transfer Funktion der Bodenklappe war bisher so, dass Clonks die Klappe prinzipiell beim hinübergehen geöffnet haben.
Dadurch wurden einige Fehlleitungen und Selbstmorde in Lavabecken hervorgerufen.
Das wird hier behoben.
--*/

#strict
#appendto HA4K

func ControlTransfer(object pObj, int iTx, int iTy)
{
	//Liegt die Y Position zwischen der Ist Y-Position und der soll Y-Position
	if(GetY(pObj)<iTy)//Will Clonk nach unten?
		if(GetY()>GetY(pObj)) //und ist Luke dazwischen?
			return(_inherited(pObj,iTx,iTy));//Dann die normale Steuerung nutzen
	if(GetY(pObj)>iTy)//Will Clonk nach oben?
		if(GetY()<GetY(pObj)) //und ist Luke dazwischen?
			return(_inherited(pObj,iTx,iTy)); //Dann die normale Steuerung nutzen
			
	//Log("Ist %dx %dy. Soll %dx %dy",GetX(pObj),GetY(pObj),iTx,iTy);
}

/*Ist 2857x 9455y. Soll 2885x 9454y

-> Bodenlucke::GetX()
 = 2872
-> Bodenlucke::GetY()
 = 9467