/*-- Arbeits U-Boot --*/

#strict

local iCurrentInstrument, pTool;

func Initialize()
{
	SetAction("Swim2Left");
	var pEnter= CreateObject(ENTR);
	pEnter-> SetAction("Attach",this());
//	iCurrentInstrument=PBAS;
	return(1);
}

func ContainedLeft(pCaller)
{
	if(GetComDir()==COMD_Right()) return(SetComDir(COMD_None()));
	if(GetAction() eq "Swim2Right")
	{
		SetComDir(COMD_Stop());
		SetAction("Turn2Left");
	}
	if(GetAction() eq "Swim2Left") SetComDir(COMD_Left());
	return(1);
}

func ContainedRight(pCaller)
{
	if(GetComDir()==COMD_Left()) return(SetComDir(COMD_None()));
	if(GetAction() eq "Swim2Left")
	{
		SetComDir(COMD_Stop());
		SetAction("Turn2Right");
	}
	if(GetAction() eq "Swim2Right") SetComDir(COMD_Right());
	return(1);
}

func ContainedThrow(pCaller)
{
	[$Instrument$]
	if(!iCurrentInstrument) return(1);
	pTool = DefinitionCall(iCurrentInstrument,"Activate",this(),pTool);
	return(1);
}

func ContainedUpSingle(pCaller)
{
	if(Turning()) return(2);
	Horizontal("Up","Down");
	return(1);
}

func ContainedUpDouble(pCaller)
{
	Exit(pCaller);
	return(1);
}

func ContainedDown(pCaller)
{
	if(Turning()) return(2);
	Horizontal("Down","Up");
	return(1);
}

func Horizontal(szDir, szOpDir)
{
	if(GetComDir()==eval(Format("COMD_%s()",szOpDir)) ) return(SetComDir(COMD_None()));
	if(GetComDir()==eval(Format("COMD_%sLeft()",szOpDir))) return(SetSpeed(GetXDir()) && SetComDir(COMD_Left()));
	if(GetComDir()==eval(Format("COMD_%sRight()",szOpDir))) return(SetSpeed(GetXDir()) && SetComDir(COMD_Right()));

	if(GetComDir()==COMD_Left()) return( SetComDir(eval(Format("COMD_%sLeft()",szDir)) ) );
	if(GetComDir()==COMD_Right()) return( SetComDir(eval(Format("COMD_%sRight()",szDir)) ) );
	if(GetComDir()==COMD_None()) return( SetComDir(eval(Format("COMD_%s()",szDir)) ) );
}

func Speed()
{
	/*Vetexes*/
	SetVertexXY(4,-15*GetDir(),-32);
	SetVertexXY(5,-35*GetDir(),-32);

	if(Turning()) return(0);
	var b;
	if(b=Bubble(GetDir()*58+RandomX(-5,5),RandomX(-7,2))) b-> SetSpeed((-GetXDir()+(1*GetDir()))*10+RandomX(-6,6),RandomX(-6,6));
	return(1);
}

/*Ich weiß Funktionen überladen sit thimonisch aber hier brauch mans eh net*/
func GetDir()
{
	if(GetAction() eq "Swim2Right") return(-1);
	if(GetAction() eq "Swim2Left") return(1);
}

/*Dreht sich?*/
func Turning()
{
	if(GetAction() eq "Turn2Right") return(1);
	if(GetAction() eq "Turn2Left") return(1);
}

/*Recalls*/
public func Entering(){return(!Contents());}

func ContextOpenGates(pClonk)
{
  [$OpenGate$|Image=FLGT]
  var pGate= FindObject2(Find_Distance(150),Find_ID(FLGT));
  if(pGate) return(pGate->~ Activate(this()));
  Sound("Error");
  return(1);
}

func ContextOpenGates(pClonk)
{
  [$OpenGate$|Image=DOOR]
  Exit(pClonk);
  return(1);
}