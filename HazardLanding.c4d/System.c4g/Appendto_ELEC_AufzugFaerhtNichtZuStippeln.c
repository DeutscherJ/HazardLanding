/*-- Fahrstühle sollen nicht zu Stippeln fahren, auch wenn diese mittlerweile als CrewMember gelten --*/

#strict
#appendto ELEC

private func FindWaitingClonk()
{
  var clnk, best, proc;
  while(clnk = FindObject(0, -30, RangeTop - GetY(), 60, 6000, OCF_CrewMember, 0, 0, NoContainer(), clnk) )
  {
	if(clnk->~IsStippel()) continue;
    proc = GetProcedure(clnk);
    if(GetComDir(clnk) == COMD_Stop || (proc eq "SWIM" && Inside(GetXDir(clnk), -5, 5)) )
    {
      if(proc eq "WALK" || proc eq "PUSH" || proc eq "SCALE" || proc eq "HANGLE" || proc eq "SWIM")
        if(!Hostile(GetController(clnk), GetOwner()) )
        {
          // Nicht erreichbar?
          if(GetY(clnk) < GetY() - 7) if(!PathFree(GetX(), GetY(), GetX(), GetY(clnk)) ) continue;
          if(GetY(clnk) > GetY() + 7) if(!PathFree(GetX(), GetY() + 16, GetX(), GetY(clnk)) ) continue;
          // Priorität prüfen (Cursor hat Priorität, sonst nächster Clonk)
          if(!best)
            best = clnk;
          else if(GetCursor(GetController(clnk)) == clnk)
            best = clnk;
          else if(GetCursor(GetController(best)) != best)
            if(ObjectDistance(clnk) < ObjectDistance(best))
              best = clnk;
        }
    }
  }
  return best;
}