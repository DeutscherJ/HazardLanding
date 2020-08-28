/*-- Neues Script --*/

#strict
#appendto CLMP

public func Ungrab() {
  if(!load) return();
  // Ziel loslassen
  SetAction("NoLoad");
  if(GetEffect("Loading", load)) RemoveEffect("Loading", load);
  load->~IsReleased();
  load = 0;
  Sound("Grapple");
}

public func Grab() {
  // Hat schon eines?
  if(GetAction() eq "Load") return(Ungrab());

  var obj;
  obj = FindObjects(Find_Or(Find_AtPoint(0,0), Find_AtPoint(0,20)), Find_NoContainer(), Find_Func("IsCraneGrabable"), Find_Exclude(this()));
  for(var pObj in obj)
    if(GetProcedure(pObj) ne "FLOAT")
      if(!pObj->~NoCrane())
      {
		var reaction = pObj->~IsGrabbed(this());
	    if(reaction) pObj=reaction;
        load = pObj;
        SetAction("Load");
        Sound("Grapple");
        AddEffect("Loading", load, 99, 1, this(), 0, GetX(load)-GetX(), GetY(load)-GetY());
        return(1);
      }
}