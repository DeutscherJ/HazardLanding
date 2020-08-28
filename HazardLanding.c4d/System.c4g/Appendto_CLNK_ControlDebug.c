/*-- Neues Script --*/

#strict
#appendto CLNK

protected func ControlCommand(string szCommand, object pTarget, int iTx, int iTy, object pTarget2, int iData, object pCmdObj) 
{
  //Händisch um erlaubnis zum austreten Fragen
  if(Contained())
	if(pTarget != Contained() && Distance(GetX(),GetY(),iTx,iTy)>20)
		Contained()->~ExitCommand(this());
  return(_inherited(szCommand, pTarget, iTx, iTy, pTarget2, iData, pCmdObj) ); 
} 