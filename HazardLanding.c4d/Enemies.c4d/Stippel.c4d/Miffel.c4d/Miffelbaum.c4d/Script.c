//Local(0) - Basis-Stamm
//Local(1) - Anzahl der Äste
//Local(2) - Anwachsen gesperrt?

#strict

func CheckEnemy(){return(true);}
func IsStippel(){return(1);}
func IsBulletTarget(){return(1);}

Wachstum:
  if(GetCategory()==4)          return(0);
  if(Random(Local(1,Local(0)))) return(0); 
  if(GetCategory(Local(0))==4)  return(Incinerate());
  if(GetCon()==100)             return(Auswahl());
  return(DoCon(1));
  
Auswahl:  
  if(!Random(10)) return(Anbau(-12,-11));
  if(!Random(10)) return(Anbau(12,-11));
  if(!Random(10)) return(Anbau(0,-23));
  return(0);
  
Anbau:  
  if(!Inside(GetX()+Par(0),10,LandscapeWidth()-10)) return(0);
  if((GetY()+Par(1))<10)                            return(0);
  if(GBackSemiSolid(Par(0),Par(1)-1))               return(0);
  if(FindObject(MB5B,Par(0),Par(1)-1,1,2))          return(0);
  if(FindObject(MI5B,Par(0),Par(1)-2,1,1))          return(0);
  
  if(Local(1,Local(0))>10) return(Miffel(Par(0),Par(1)));
  if(Local(2))             return(0);
  
  Var(0)=CreateConstruction(MB5B,Par(0),Par(1),-1,1);
  
  if(!Local(0)) Local(0)=this();
  Local(0,Var(0))=Local(0);
  Local(1,Local(0))++;
  if(!Local(1)) Local(2)=1;  
  return(1);

Miffel:
  CreateConstruction(MI5B,Par(0),Par(1)-2,-1,1);
  return(1);

Incineration:
  if(GetCategory()==4) return(0); 
  SetAction("Schmoren");
  SetCategory(4);
  return(1);