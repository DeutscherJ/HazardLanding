/*-- Konsole --*/

#strict
#appendto CNS2

func ControlDig(pClonk)
{
	return(1);
}

func ControlDigDouble(pClonk)
{
	if(GetWealth()<250 || Local(100))
	{
		Sound("Error");
		Message("Die Bedrohung ist nicht groß genug, dass sich der Einsatz von Kampfrobotern lohnen würde.");
		return(0);
	}
	Sound("PlayerJoin");
	ScheduleCall(this(),"New",50000);
	for(var i=GetPlayerCount();i>0;i--)
	{
		var robot=CreateObject(BLBT,AbsX(LandscapeWidth()/2),AbsY()+20,i-1);
		MakeCrewMember(robot,i-1);
		//SetCursor(i-1,robot);
		CreateObject(CFAL,0,0,i-1)->UseOn(robot);
	}
	Log("Kampfroboter sind nun im Einsatz");
	Local(100)=true;
	return(1);
}

func New()
{
	Local(100)=false;
}