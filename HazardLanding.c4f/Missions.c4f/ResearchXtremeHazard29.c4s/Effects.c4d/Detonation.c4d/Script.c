/*Explosion*/

#strict

static ExplosionHelper;

//static fFirstInit;
local zSize, zAngle, fExplode;
global func Explode(a,b,c,d,e,f)
{
	RemoveObject(b);
	Explosion2(a);
	_inherited(a,b,c,d,e,f);
}

global func Explosion2(int Staerke, fSicher)//Explosionen über 50 aus Anti laagt Gründen nur nach Sicherheitskontrolle
{
	if(Staerke>50 && !fSicher) Staerke=50;
	if(!ExplosionHelper)
	{
		ExplosionHelper=CreateObject(BLBL,AbsX(),AbsY(),-1);
		ExplosionHelper->IsHelper();
	}
	var explosion = CreateObject(BLBL,0,0,GetOwner());
	if(explosion) explosion->Lunch(Staerke);
	return(0);
}

func Initialize()
{
	SetAction("Blast");
	SetCon(100);
	SetClrModulation(RGBa(0,0,0,100));
	return(1);
}

func IsExploding(pObj)
{
	if(pObj==this()) return(0);
	//if(GetAction()eq"Blast") return(1);
	return(0);
}
func Lunch(int pStaerke)
{
	Blast();
	if(pStaerke==0) pStaerke=30;
	for(var pWinkel=360; pWinkel>=0; pWinkel-=45)
	{
		var pX= Sin(pWinkel,Groesse()), pY= -Cos(pWinkel,Groesse());
		if(!FreeWay(pX,pY)) continue;
		var explosion= CreateObject(GetID(),pX,pY,GetOwner());
		explosion->Lunch2(pStaerke-10, pWinkel);
	}
}

func NextExplode(iWinkel)
{
	if(!iWinkel) iWinkel=zAngle;
	if(zSize<5) return();
	for(var pWinkel2=-90; pWinkel2<=90; pWinkel2+=90)
	{
		var pX= Sin(iWinkel+pWinkel2,Groesse()), pY= -Cos(iWinkel+pWinkel2,Groesse());
		if(!FreeWay(pX,pY)) continue;
		var explosion= CreateObject(GetID(),pX,pY,GetOwner());
		SetPosition(GetX()+pX,GetY()+pY,explosion);
		if(explosion)explosion->Lunch2(zSize-10, iWinkel+pWinkel2);
	}
	
}

func Lunch2(int pStaerke,int pWinkel)
{
	var obj;
    if(obj= FindObject2(Find_ID(GetID()),Find_Func("IsExploding",this()),Find_AtPoint()))
	{
		if(pWinkel!=LocalN("zAngle",obj) && ObjectCount(GetID())<=1000) ExplosionHelper->ScheduleCall(ExplosionHelper,"Help",4,0,pWinkel,ObjectNumber(obj));
		RemoveObject();
		return(1);
	}
	Blast();
	zAngle = pWinkel;
	zSize = pStaerke;
	CreateParticle("Fire2",0,0,0,0,200+zSize*10);
}

func Help(iAngle, pObjNum)
{
	var obj= Object(pObjNum);
	if(obj) obj->~NextExplode(iAngle);
	return(1);
}

func IsHelper()
{
	SetAction("Idle");
	SetCategory(1);
	return(1);
}
func FreeWay(iX, iY)
{
	if(!PathFree(GetX()+iX,GetY()+iY,GetX(),GetY())) return(0);
	return(1);
}

func Groesse()
{
	return(30);
}

func Blast()
{
	Sound("explo*");
	BlastObjects(GetX(),GetY(),40);
	DigFree(GetX(),GetY(),20);
}

func Remove()
{
	RemoveObject();
}