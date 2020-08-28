/*-- Ständer --*/

#strict

local fire;
local function;

public func Light(caller)
{
  //if(fire) return(0);
  //fire= CreateObject(FIRE,0,-7,-1);
  AddFireLight(180,RGB(150,150,255),this());
  if(!function)
  {
	  var i = 0;
	  while(Local(i))
	  {
		  Local(i)->~Activate(caller);
		  i++;
	  }
  }
  else eval(function);
  //MakeLight(this(),RGB(150,150,255),180,10);
  //eval(function);
  return(1);
}