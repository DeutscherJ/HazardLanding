/*Fleck*/

#strict

func SetSize()
{
  DoCon(Sub(Div(Mul(Par(0),100),40),100));
  SetLocal(0,Par(0));
  SetVar(0,Mul(Div(Sub(40,Div(Mul(40,GetCon()),100)),2),-1));
  SetPosition(GetX(),Sum(GetY(),Var(0)));
  return(1);
}

func Initialize()
{
  SetAction(Format("Blood%d",1+Random(14)));
  SetLocal(0,40);
  return(1);  
}