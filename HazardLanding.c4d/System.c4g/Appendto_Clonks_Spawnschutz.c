/*-- Neues Script --*/

#strict
#appendto CLNK
#appendto HZCK

local fSpawnProtected;

func Initialize(a,b,c)
{
    if(!FindObject(CHOS)) AddEffect("SpawnProtect", this(), 1,1, this());
	return(inherited(a,b,c));
}

func LaterInit(a,b,c)
{
	AddEffect("SpawnProtect", this(), 1,1, this());
	return(_inherited(a,b,c));
}

func FxSpawnProtectStart(object target, int effect, int temp)
{
	fSpawnProtected=1;
    EffectVar(0, target, effect) =  SPSeconds*36;
}

func FxSpawnProtectTimer(object target, int effect, int temp)
{
	if(Local(101)) return(-1);//vorzeitiger Abbruch wegen Waffenbenutzung
	var iAngle=Random(360);
	var x= Sin(iAngle,15);
	var y= -Cos(iAngle,15);
	//CreateParticle("PSpark",Sin(EffectVar(0, target, effect),10),-Cos(EffectVar(0, target, effect),10),0,0,50,RGB(Random(255),Random(255),Random(255)),this());
	CreateParticle("PSpark",x,y,0,0,50,RGB(Random(255),Random(255),Random(255)),this());
    EffectVar(0, target, effect)--;
	if(EffectVar(0, target, effect)<=0) return(-1);
}

func FxSpawnProtectStop(object target, int effect, int temp)
{
	if(GetAlive()) fSpawnProtected=0;
	return(1);
}

public func IsBulletTarget(a,b,c)
{
	if(fSpawnProtected || IsDying()) return(0);
	return(1);
}

func QueryCatchBlow(a,b,c)
{ 
	//Log("%s Blar1",GetName());
	if(fSpawnProtected || IsDying()) return(1);
	else return(_inherited(a,b,c));
}

func Damage(a,b,c)
{
	//Log("%s Blar2",GetName());
	if(fSpawnProtected || IsDying()) DoEnergy(a);//Spawnschutz... Abgezogenen Energie wieder raufrechnen
	return(_inherited(a,b,c));
}

public func OnDmg(int iDamage, int iType,c,d,e)
{
	//Log("%s Blar3",GetName());
	//DoEnergy(iDamage, this(), true);
	if(fSpawnProtected || IsDying()) return(100);
	return(_inherited(iDamage,iType,c,d,e));
}


//Die Waffenfunktion vom Airbike wird benuzt, und der Spawnschutz mit Sicherheit abgebrochen
