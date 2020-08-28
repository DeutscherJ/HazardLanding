/* AlphaStippel */

#include ST5B
#strict


func IsAlien(){return(1);}
func IsBulletTarget(){return(1);}
public func IsThreat() { return(true); }
func IsStippel(){return(true);}
func Intelligence(){return(60);}
func MaxIntelligence(iLvl){return(Intelligence()<=iLvl);}
func Schlagable(){return(1);}

local action, target, campanion;

func CheckEnemy(){return(true);}
func Initialize()
{
	SetOwner(-1);
	SetCon(70);
	return(_inherited());
}

func Strength(){return(4);}

func Zyklus()
{
	if(action==2)
	{
		if(!target->~Open(this())) target->~DoOpen(this());
		SetCommand(this(),"Enter",target);
		return(1);
	}
	if(action==1)
	{
		SetCommand(this(),"Enter",target);
		return(1);
	}
	/*if(target=FindObject2(Find_Distance(50),Find_OCF(OCF_Entrance)))
	{
		action=1;
	}*/
	if(target=FindObject2(Find_Distance(50),Find_Func("Passange",this())))
	{
		action=2;
	}
	_inherited();
}