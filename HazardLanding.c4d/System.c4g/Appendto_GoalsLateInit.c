/*-- Neues Script --*/

#strict
#appendto MNTK
#appendto WPHT

func Initialize(a,b,c)
{
	if(FindObject(CHOS)) return(0);
	return(_inherited(a,b,c));
}
func GoalWithLateInit(){return(1);}
	
func LateInit()
{
	Initialize();
	return(1);
}