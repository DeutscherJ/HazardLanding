/*-- StippelCount --*/
#strict

private Execute:
   // Wieviel Stippel sind noch am Leben?
   SetVar(1,0);
   while (SetVar(0, FindObject(ST5B,0,0,0,0,0, 0,0, 0, Var(0)) ))
     if(GetAlive(Var(0)))
       IncVar(1);
   while (SetVar(0, FindObject(MF5B,0,0,0,0,0, 0,0, 0, Var(0)) ))
     if(GetAlive(Var(0)))
       IncVar(1);
   while (SetVar(0, FindObject(MI5B,0,0,0,0,0, 0,0, 0, Var(0)) ))
     if(GetAlive(Var(0)))
       IncVar(1);
   while (SetVar(0, FindObject(KG5B,0,0,0,0,0, 0,0, 0, Var(0)) ))
     if(GetAlive(Var(0)))
       IncVar(1);
   while (SetVar(0, FindObject(SK5B,0,0,0,0,0, 0,0, 0, Var(0)) ))
     IncVar(1);
   while (SetVar(0, FindObject(_PLT,0,0,0,0,0, 0,0, 0, Var(0)) ))
     if(GetAlive(Var(0)))
       IncVar(1);
  SetLocal(0,Var(1));
  // Stippelanzeige bei allen 12 Spielern setzen
  SetVar(2,-1);
  while(LessThan(IncVar(2),13))
    SetWealth(Var(2), Var(1));
  return(1);

protected Activate:
  MessageWindow(GetDesc(),Par());
  return(1);
