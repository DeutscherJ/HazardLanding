/*-- Neues Script --*/

#strict
#appendto GOAL

public func IsFulfilled()
{
	if(FindObject(CHOS)) return 0;
	return 1;
}