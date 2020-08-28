/*-- Siedlungsfunktionen --*/

#strict
#appendto CLNK
#appendto HZCK


/* Gebäude-Abriss */

public func ContextDestruction()
{
  [Gebäudeabriss|Image=SYF1|Condition=BackAnything]
  var obj = BackAnything();
  if (!obj) return(1);
  CreateMenu(SYF1);
  AddMenuItem("%s abreissen","DoDestruction",GetID(obj),0,0,obj);
  AddMenuItem("Abbrechen","NoDestruction",SYCC);
}

private func BackBuilding()
{
  var obj;
  while (obj = FindObjectOwner(0,GetOwner(), -1,+9,0,0, OCF_Exclusive(), 0,0,obj))
    if (GetCategory(obj) & C4D_Structure())
      if (GetCon(obj) >= 100)
        if (!FindObject(DSTR,0,0,0,0,0,"Destruct",obj))
          return(obj);
  return(0);
}

private func BackConstruct()
{
  var obj;
  while (obj = FindObjectOwner(0,GetOwner(), -20,+8,40,5, OCF_Construct(), 0,0,obj))
    if (!FindObject(DSTR,0,0,0,0,0,"Destruct",obj))
      return(obj);
  obj = 0;
  while (obj = FindObjectOwner(0,GetOwner(), -1,+9,0,0, OCF_Construct(), 0,0,obj))
    if (!FindObject(DSTR,0,0,0,0,0,"Destruct",obj))
      return(obj);
  return(0);
}

private func BackAnything()
{
  var obj = BackBuilding();
  if (obj) return(obj);
  return(BackConstruct());
}

private func DoDestruction(par0, target)
{
  CreateObject(DSTR)->DoDestruction(target);
}

private func NoDestruction() {}


/* Gebäude-Reparatur */

public func ContextRepair()
{
  [Reparatur|Image=REPA|Condition=BackDamaged]
  var obj = BackDamaged();
  if (!obj) return(1);
  CreateObject(REPA,0,0,GetOwner())->Init(obj);  
}

public func ContextUndoRepair()
{
  [Reparatur|Image=REPA|Condition=BackDamaged]
  var obj = BackDamaged2();
  if (!obj) return(1);
  var rep = FindObject(REPA, 0,0,0,0, 0,"Repair",obj);
  if (rep) RemoveObject(rep);
}

private func BackDamaged()
{
  var obj;
  while (obj = FindObjectOwner(0,GetOwner(), -1,+9,0,0, OCF_Exclusive(), 0,0,obj))
    if (GetCategory(obj) & C4D_Structure())
      if (obj->~Repairable())
        if (GetDamage(obj))
          if (GetCon(obj) >= 100)
            if (!FindObject(REPA, 0,0,0,0, 0,"Repair",obj))
              return(obj);
  return(0);
}

private func BackDamaged2()
{
  var obj;
  while (obj = FindObjectOwner(0,GetOwner(), -1,+9,0,0, OCF_Exclusive(), 0,0,obj))
    if (GetCategory(obj) & C4D_Structure())
      if (obj->~Repairable())
        if (GetDamage(obj))
          if (GetCon(obj) >= 100)
            if (FindObject(REPA, 0,0,0,0, 0,"Repair",obj))
              return(obj);
  return(0);
}
