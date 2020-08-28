/*-- Bohrkopf --*/

#strict

local derrick;


public func Init(par_derrick)
{
  derrick = par_derrick;
  SetAction("Level");
}

protected func DestructCheck()
{
  if (!FindLine()) RemoveObject();
}

private func TopCheck()
{
  var minY = GetY(derrick) + 20;
  if (GetY() >= minY) return(1);
  SetComDir(COMD_Stop());
  SetYDir(0);
  SetPosition(GetX(), minY);
  Sound("Click");
  return(0);
}

protected func ContactBottom()
{
  SetAction("Level");
  SetComDir(COMD_Stop());
  SetYDir(0);
  Sound("Click");
}

private FindLine: return(FindObject(SPIP,0,0,0,0,0,"Connect",Contents()));

