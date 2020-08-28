#strict
Initialize:
  
  return(1);

Incineration:
  Extinguish();
  if(Local(0)) return(0);
  SetLocal(0,1);
  Sound("Crystal1");
  Sound("Crystal2");
  Sound("Crystal3");
  CreateObject(ST5B);
  return(1);
