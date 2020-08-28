/*-- 4Z-Falle aus TempleProfanation.c4s --*/

#strict

protected func Initialize()
{
  SetAction("Be");
  SetPhase (Random(1), 0); 
}

public func Set(phase)
{
  SetPhase(phase);
  var width = GetDefCoreVal("Width", "DefCore", GetID());
  var height = GetDefCoreVal("Height", "DefCore", GetID());
  return(1);
}

//Wenns aktiviert wird, Flints spucken
protected func Activate()
{
	var dir = RandomX(150,450);
	if(!GetEffect("*ScheduleCall*",this()))
		for(var c=10;c<150;c+=10)
		{
			if(Random(2))continue;
			ScheduleCall(this(),"Flints",c,1,dir+RandomX(-20,20));
		}
	return(1);
}

protected func Flints(dir)
{
	var x = Cos(dir,25);
	var y = Sin(dir,25);

	var f=CreateObject(FLNT,0,9,-1);
	f->SetXDir(x);
	f->SetYDir(y);
	Sound("Sound1B");
	return(1);
}