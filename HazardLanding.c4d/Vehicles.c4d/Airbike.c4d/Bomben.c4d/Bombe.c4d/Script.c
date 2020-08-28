#strict

func Initialize()
{
  Sound("Fall");
  //SetCategory(8);
  return(SetAction("Fliegen"));
}

func Fliegen()
{
  //if(!Local(0)) SetLocal(0,GetR()/Abs(GetR()));
  //if(GetYDir()>25) SetRDir(GetRDir()+Local(0));
  SetR(Angle(GetXDir(),GetYDir())-180);
  
  var obj;
  obj= FindObject2(Find_OCF(OCF_Alive()),Find_Func("IsBulletTarget",A35B,this()),Find_Hostile(GetOwner()),Find_Distance(10),Find_NoContainer());
  if(obj){return(Hit());}
  return(1);
}

func Wasser()
{
  if(Abs(GetXDir())>0) SetXDir(GetXDir()-Local(0));
  if(GetYDir()>25)     SetRDir(GetRDir()+Local(0));
  SetComDir(COMD_Down());
  return(Bubble());
}

func Damage(){return(Hit());}
func Hit(){return(Explode(20));}