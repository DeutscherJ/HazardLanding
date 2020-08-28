/*-- Haken --*/

#strict

local bike, Object;

func Timer()
{
  var dir= GetDir(bike)*2-1;
  SetSpeed(0,0,Object);
  if(Object) SetPosition(GetX(bike)+dir*24,GetY(bike),Object);
  SetPosition(GetX(bike)+dir*24,GetY(bike),this());
  return(1);
}

func Koppel()
{
  if(Object)
  {
	  for(var i=50;Stuck(Object)&&i;i--) SetPosition(GetX(Object),GetY(Object)+1,Object);
	  for(i=100;Stuck(Object)&&i;i--) SetPosition(GetX(Object),GetY(Object)-1,Object);
	  for(i=50;Stuck(Object)&&i;i--) SetPosition(GetX(Object)+1,GetY(Object),Object);
	  for(i=100;Stuck(Object)&&i;i--) SetPosition(GetX(Object)-1,GetY(Object),Object);
	  return(Object=0);
  }
  // Nächstes greifbares Objekt suchen
  var obj= FindObject2(Find_AtPoint(),Find_Category(C4D_Vehicle),Find_NoContainer(),Find_Not(Find_ID(ERBK)),Find_OCF(OCF_Grab));
  if(!obj)
	  return(0);
  // Keine verankerten Brückensegmente
  if (obj->~IsBridge() && obj->~IsLocked()) return(0);
  // Ankuppeln
  Object= obj;
  Sound("Connect");
  return(1);
}