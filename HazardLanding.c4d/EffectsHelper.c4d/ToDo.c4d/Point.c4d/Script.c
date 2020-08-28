/*-- Aufgabenpunkt --*/

#strict

local szMessage, iHide;

func Initialize() {
  SetAction("Exist");
  Hide();
  return(1);
}

func Timer()
{
  if(!iHide) PlayerMessage(GetOwner(), "%s",this(), szMessage); 
  else PlayerMessage(GetOwner(), "",this(), szMessage); 
}

func Hide()
{
  iHide=1; 
}

func Show()
{
  iHide=0; 
}
func ShownMessage(szMsg)
{
  szMessage= szMsg;
  return(1);
}