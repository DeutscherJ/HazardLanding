/*-- Pipelinekit --*/

#strict 2

local pCable, pFrom;

protected func Hit()
{
  Sound("RockHit*");
}

func Activate()
{
	[$TxtConnect$|Image=CABL]
	var pTarget = FindObject2(Find_Func("ObjectPipeConnectable",this()),Find_AtPoint(),Find_NoContainer());
	if(pTarget && !pFrom) 
		return(ConnectTo(pTarget));
	if(pTarget && pFrom) 
		return(ConnectTo(pTarget));
	Sound("Error");
	Message("$NoConnection$",this());
	return(1);
}

public func ConnectTo(pObject)
{
  Sound("Connect");
  //pObject->~ConnectPipe(this());//Bescheid geben
  Message("$TxtConnectTo$",this(),GetName(pObject));
  if(pFrom)//Schon eine Seite verbunden?
  {
	pObject->~ConnectPipe(pFrom);//Bescheid geben
	pFrom->~ConnectPipe(pObject);//Bescheid geben
	ObjectSetAction(pCable,"Connect",pObject,pFrom);//Verbindung herstellen
	RemoveObject();
	return(1);
  }
  //Oder noch keine nader Seit verbunden?
  pFrom  = pObject;
  pCable = PipeConnect(this(),pObject);
  return(1);
}

/* Produkteigenschaften */

public func IsAnvilProduct() { return(1); }
