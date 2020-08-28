#strict
#include CLGH

/*
func IsBulletTarget()
{
	if(!Random(6)) return(1);
	DoDamage(Random(4));
	return(0);
}

Initialize:
  An();
  return(1);

Damage:
  if(SEqual(GetAction(),"An")) if(50<GetDamage())
  {
    SetAction("FlackerAn");
    if(!Local(0)) ObjectSetAction(Local(0)=CreateObject(LJ3V,-20,16),"Neon");
  }
  if(100<GetDamage()){Aus();}
  if(150<GetDamage())
  {
	RemoveObject(Local());
	CastObjects(_DF1,4,35,0,8);
	Explode(20);
  }
  return(1);
  
Flacker:
  if(Not(Random(15))) And(CastObjects(SU3V,Sum(1,Random(1)),Sum(5,Random(15)),Sum(-14,Random(28)),Sum(1,Random(2))),Sound("Spark*"));
  if(Not(Random(2))) return(0);
  if(Random(6)) return(ObjectSetAction(Local(0),"Neon")&&SetAction("FlackerAn"));
  if(Random(6)) return(ObjectSetAction(Local(0),"Aus")&&SetAction("FlackerAus"));
  return(1);

Energie:
  if (Not(GameCall("MainEnergySupply")) || 100<GetDamage()) return(Aus());
  if (GameCall("MainEnergySupply")) return(An());
  return(0);

An:
  if(Local(0)) return(1);
  SetAction("An");
  ObjectSetAction(Local(0)=CreateObject(LJ3V,-20,16),"Neon");
  return(1);

Aus:
  SetAction("Aus");
  if(Local(0)) RemoveObject(Local(0));
  return(1);