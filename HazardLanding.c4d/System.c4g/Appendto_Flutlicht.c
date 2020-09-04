/*-- Das An und Ausschalten des Flutlicht debuggen --*/

#strict
#appendto FLHH

public func TurnOn() {
	if(EMPShocked()) return;
	bOn = true;
	Turning();
	if(Light())
		Light()->TurnOn();
}

public func TurnOff()
{
	bOn = false;
	Turning();
	if(Light())
		Light()->TurnOff();
}

public func Switch() {
	if(bOn)
		TurnOff();
	else
		TurnOn();
}