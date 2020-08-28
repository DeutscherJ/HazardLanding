/*-- Magnet --*/

#strict
//iCurrentInstrument=MGNT
local fInUse, pRope, pSub, iLength, pMagObj;

func Initialize()
{
	fInUse=true;
	iLength=400;
	return(1);
}

func Timer()
{
	//if(fInUse) return(0);
	
	if(fInUse&&pMagObj)SetSpeed(GetX()-GetX(pMagObj),GetY()-GetY(pMagObj),pMagObj);
	if(iLength>10)
	{
		iLength--;
	}
	if(ObjectDistance(this(),pSub)<30)
	{
		if(!pMagObj||!fInUse) 
		{
		  RemoveObject(pRope);
		  return(RemoveObject());
		}
	}
	LocalN("Length",LocalN("Rope",pRope))=iLength;
	var pObj;
	if(pObj= FindObject2(Find_Distance(43),Find_Func("Magnetic")) )
	{
		if(!fInUse)return(1);
		pObj->~ IsAttracted(this());
		pMagObj=pObj;
	}
	return(1);
}

func Activate(Sub,pTool)
{
	if(pTool)//hat schon einen Magnet
	{
		pTool->~Switch();
		return(pTool);
	}
	var pMagnet= CreateObject(MGNT,GetX(Sub),GetY(Sub)+32,GetOwner(Sub));
	pMagnet->~ Init(Sub);
	return(pMagnet);
}

func Switch()
{
	fInUse=!fInUse;
	if(pMagObj)
	{
	  pMagObj->~Release(this());
	  pMagObj=0;
	}
	return(1);
}
func Init(Sub)
{
	pSub=Sub;
	pRope= CreateObject(161E,0,0,GetOwner());
	Enter(Sub,pRope);
	pRope->Verbinde(0,this());
	return(1);
}