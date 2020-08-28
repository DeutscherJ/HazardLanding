/*-- Flutlicht --*/

#strict
#appendto FLHH

public func TurnOn() {
	if(EMPShocked()) return;
	bOn = true;
	if(Light())
		Light()->TurnOn();
}

public func TurnOff() {
	bOn = false;
	if(Light())
		Light()->TurnOff();
}