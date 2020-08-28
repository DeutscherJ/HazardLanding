/*-- Rohrpostverwalter --*/

#strict
#appendto BOB1
#appendto DOOR

local pObjectTransmitter;

//Gebäude wurde an Rohrnetz angeschlossen
func ConnectPipe(pOtherSide)
{
	if(pObjectTransmitter)//Ist schon angeschlossen?
		return(0);
	else
	{
		var pTransmitter = FindObject2(Find_Func("ObjectTransmitter2",pOtherSide));//Ist das andere Gebäude bereits angeschlossen? dann schalte mich Gebäude dazu
		if(pTransmitter) pTransmitter->~AddHouse(this());
		else
			CreateObject(PCG4,0,0,GetOwner())->~AddHouse(this());//Ansonsten neue Verbindung erzeugen
	}
}
func Collection2(pObj)
{
	if(pObjectTransmitter)
		ScheduleCall(pObjectTransmitter,"CollectionCall",1,0,pObj,this());
	return(_inherited(pObj));
}

func Ejection(pObj)
{
	if(pObjectTransmitter)
		ScheduleCall(pObjectTransmitter,"EjectionCall",1,0,pObj,this());
	return(_inherited(pObj));
}

func ObjectPipeConnectable(){return(1);}