/*-- Käfig --*/

#strict

local hostage;

func Initialize()
{
	SetAction("Hang");
	return(1);
}

/* Öffnung */
protected func ControlThrow(object pClonk)
  { [$CtrlOpen$|Image=_KEY]
  // Schon offen?
  if (GetAction() eq "Open") return();
  // Schlüssel dabei?
  var pKey = FindContents(_KEY, pClonk);
  if (!pKey) return(Message("$MsgNoKey$", pClonk, GetName(pClonk)), Sound("CommandFailure*"));
  // Aufschließen
  Open(pClonk);
  }
  
func Activate(pClonk){return(ControlLeft(pClonk));}

func ControlLeft(pClonk)
{
	if(pClonk->~IsSwitch())
	{
		Open(pClonk);
	}
	return(1);
}

func ControlRight(pClonk){return(ControlLeft(pClonk));}

func Open(pClonk)
{
  Sound("Connect", this());
  Sound("ChestOpening", this());
  SetAction("Open");
  SetSolidMask();
  GameCall("OnCageOpened", this());
  if(hostage)
	if(pClonk)
	{
		MakeCrewMember(hostage,GetOwner(pClonk));
		SetOwner(GetOwner(pClonk),hostage);
	}
}

func CreateHostage()
{
	hostage = CreateObject(KNIG,-8,12,-1);
	return(hostage);
}