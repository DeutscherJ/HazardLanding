/*-- Neues Script --*/

#strict
#appendto CLNK 
#appendto HZCK

func Schlagable(pObj){return(GetAlive()&&Hostile(GetOwner(),GetOwner(pObj)));}
func Hammered(pObj,iStrength)
{
	if(iStrength>15) BigHurt();
	if(!iStrength) iStrength=60;
	Punch(this(),iStrength);
	if(GetAction()eq"Dead") SplatterDead(pObj);
	return(1);
}

func BigHurt()
{
	if(GBackTunnel()&&GBackTunnel(-20,0)&&GBackTunnel(-20,0)&&GBackTunnel(20,0)&&GBackTunnel(0,-20))
	{
		var fleck=CreateObject(FLCK,0,20,-1);
		SetClrModulation(RGB(255,0,0),fleck);
		fleck->SetSize(25);
	}
	Sound("Splatter*");
	CastObjects(BLUT,60,20);
	return(1);
}

func Hurt(a,b,c,d,e)
{
	_inherited(a,b,c,d,e);
	
	Blood(10);
	if(a>20) return(BigHurt());
	if(!Random(8))
	{
		if(GBackTunnel()&&GBackTunnel(-20,0)&&GBackTunnel(-20,0)&&GBackTunnel(20,0)&&GBackTunnel(0,-20))
		{
			var fleck=CreateObject(FLCK,0,20,-1);
			SetClrModulation(RGB(255,0,0),fleck);
			fleck->SetSize(15);
		}
	}
	//if(GetEnergy()<50 && FindContents(NH5B) && GetPlrExtraData(GetOwner(),"FSE_Skill")==2) FindContents(NH5B)->~Activate(this());
	return(1);
}

public func OnDmg(int iDamage, int iType)
{
	if(iType == DMG_Melee)
	{
		Blood(iDamage*ObjectCount(RVIV));
	}
	return(_inherited(iDamage,iType));
}

func BigHurt()
{
	if(fAntiLaag==2) return(Sound("Splatter*"));
	if(GBackTunnel()&&GBackTunnel(-20,0)&&GBackTunnel(-20,0)&&GBackTunnel(20,0)&&GBackTunnel(0,-20))
	{
		var fleck=CreateObject(FLCK,0,20,-1);
		SetClrModulation(RGB(255,0,0),fleck);
		fleck->SetSize(100);
	}
	//CastPXS("Blood", 50, 50);
	Sound("Splatter*");
	if(!fAntiLaag) CastObjects(BLUT,60,20);
	return(1);
}