/*-- Flieﬂband --*/

#strict

#include PM1C

func CheckEnds(dir)
{
  var objects = FindObjects(Find_Category(C4D_Living), Find_Or(Find_Action("Scale"), Find_Action("ScaleDown")), Find_InRect(10, -18, 30, 30), Find_Exclude(this()));
    for(object in objects)
      {
        //SetPosition(GetX(object), GetY(object)+4*dir, object);
        SetYDir(30*dir, object);
      }
}
