/*-- Flieﬂband --*/

#strict

local father, x, y;


func Initialize()
{
  //Voreinstellungen:
  SetAction("Stop");
  x = GetX()-GetX(father);
  y = GetY()-GetY(father);
  return(1);
}


func CheckPosition() /* Position checken und geg. korrigieren */
{
  SetPosition(GetX(father)+x, GetY(father)+y);
  if(GetAction()ne"Stop") Push();
}

func Push()
{
  var dir;
  if(GetAction() S= "Left") dir = -1;
    else dir = 1;
  
  /* Auf dem Band */
  var objects = FindObjects(Find_Or(Find_Category(C4D_Living), Find_Category(C4D_Object), Find_Category(C4D_Vehicle)), Find_InRect(-20, -30, 40, 30), Find_Exclude(this()));
  for(object in objects)
    {
      if(GetCategory(object) & C4D_Living && GetContact(object, -1) & CNAT_Bottom)
        SetPosition(GetX(object)+dir, GetY(object), object);//+4*dir
      if(GetCategory(object) & C4D_Object || GetCategory(object) & C4D_Vehicle)
        SetXDir(30*dir/4, object);
    }
  
  /* Unter dem Band */
  var objects = FindObjects(Find_Category(C4D_Living), Find_InRect(-20, 0, 40, 30), Find_Exclude(this()));
  for(object in objects)
    {
      if(GetContact(object, -1) & CNAT_Top)
        //SetPosition(GetX(object)+4*-dir, GetY(object), object);
        SetXDir(30*-dir/4, object);
    }
  
  /* Neben dem Band */
  CheckEnds(dir);
}

func CheckEnds(dir) {return(0);}
