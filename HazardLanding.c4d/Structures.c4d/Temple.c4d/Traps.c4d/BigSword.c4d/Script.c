/*-- 4Z-Falle --*/

#strict

local randFac;
local iTimer;
local bOn;
local iAngle;

func Initialize()
{
	SetAction("Init");
	bOn = false;
	Set();
	return(1);
}

func Initialized()
{
	randFac = 3+Random(3);
	SetAction("Wait");
}

func Set(iangle)
{
	iAngle = iangle-90;
	SetR(iAngle+90);
}

func DoPunch()
{
	if(!bOn) return();
	iTimer++;
	if(iTimer % randFac == 0)
	{
		ExecPunch();
		iTimer=0;
	}
}

//Beim Zustechen
func IsPunching()
{
	//Nicht immer tödlich
	if(!Inside(GetPhase(),5,7))return();
 
	var pTargets=[];
	//mögliche Opfer raussuchen und in Array speichern
	for(var obj in FindObjects(Find_InRect(-65,-65,130,130),Find_OCF(OCF_Alive())))
		pTargets[GetLength(pTargets)] = obj; 
	
	//Länge nach das Messer "abgehen"
	for(var cnt=0;cnt<50;cnt+=4)
	{
		var x = Cos(iAngle,cnt);
		var y = Sin(iAngle,cnt);
		for(var i=0;i<GetLength(pTargets);i++)
		{
			var obj = pTargets[i];
			if(!obj) continue;
			if(Distance(GetX()+x,GetY()+y,GetX(obj),GetY(obj)) < 10)
			{
				Punch(obj,10+Random(5));//Alle Leute die sich in Klinge befinden kaputt bollern
				pTargets[i]=0;
			}
		}
	}
}

//Anschalten
public func Activate()
{
	bOn=!bOn;
}

/*Für die Steuerung mit einem Schalter*/
func ControlRight(){bOn=0;}
func ControlRight(){bOn=1;}

//Zustechen
func ExecPunch()
{
	if(GetAction() eq "Wait")
	SetAction("DoPunch");
}