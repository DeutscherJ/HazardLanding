/*-- AufgabenListe --*/

#strict

local closed, pClonk;

func Initialize() {
  //SetAction("Exist");
  SetPosition(155,250);
  //MakeCrewMember(this(),GetOwner());
  //SetCursor(
  //CreateObject(GLGH,0,0,GetOwner());
  return(1);
}

func Point(szName,szMessage)
{
  var iPoint=2;
  while(Local(iPoint)) iPoint++;
  var x=0;
  var y=-170+iPoint*35;
  Local(iPoint)= CreateObject(PNT1,x,y,GetOwner());
  Local(iPoint)->~ ShownMessage(szMessage); 
  SetName(szName,Local(iPoint));
  return(1);
}

func ChangePoint(szName,szMessage)
{
	var iPoint=2;
	while(iPoint<30)
	{
		if(GetName(Local(iPoint)) eq szName)//richtiger Punkt
			Local(iPoint)->~ ShownMessage(szMessage); 
		iPoint++;
	}
}

func Close()
{
  closed=1;
  SetVisibility(VIS_None());
  for(var num=2; Local(num);num++)
  {
   Local(num)->~Hide();
  }
  return(1);
}

func Open()
{
  closed=0;
  Sound("PlanUnfold",1,0,0,GetOwner());
  SetVisibility(VIS_Owner());
  for(var num=2; Local(num);num++)
  {
   Local(num)->~Show();
  }
  return(1);
}