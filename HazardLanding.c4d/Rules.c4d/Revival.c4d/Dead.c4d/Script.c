/*-- Totes Etwas --*/

#strict

func ControlDigDouble(pClonk) {
	var pObj = GetActionTarget();
	if(GetAlive(pObj))
		pObj->~ContextRivive();
	/*else
	{
		ChangeDef(_SKG,pClonk);
		pClonk->Start(pObj)
	}*/
	return(1);
}

func CheckDead()
{
	if(!GetActionTarget()) return(RemoveObject());
	if(GetAction(GetActionTarget()) ne "Dead" ) RemoveObject();
	return(1);
}

func IsDying(){return(1);}
func NotSchlagable(){return(1);}
func NotAttackable(){return(1);}