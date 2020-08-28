/*-- Bacta Tank Inhalt --*/

#strict

local contentID;
local contentAction;
local iTimer,pTank;

func Free()
{
	if(GetType(contentID)==C4V_C4Object())
		Exit(contentID);
	else
	{
		var miffelbaum;
		if(contentID==MI5B)
			miffelbaum = CreateObject(MB5B,0,3,-1);
		CreateObject(contentID,0,0,-1);
		if(miffelbaum) RemoveObject(miffelbaum);
	}
	RemoveObject();
	return(1);
}

//SetGraphics(0,0,0,1,GFXOV_MODE_Object,0,0,FindObject(HZCK));
//SetGraphics("",this(),0,1,GFXOV_MODE_ExtraGraphics,"",0,FindObject(HZCK))
//SetGraphics("",this(),0,1,GFXOV_MODE_Object,"",0,FindObject(HZCK))
func Timer()
{
	if(!pTank) RemoveObject();
	iTimer++;
	var y = Cos(iTimer,10000);
	//if(GetAction() ne contentAction[1])
	//	SetAction(contentAction[1]);
	var cID = contentID;
	if(GetType(cID)==C4V_C4Object())
		cID = GetID(cID); 
	//SetObjDrawTransform (1000,0,-GetDefCoreVal("Width","DefCore",cID)*500,0,1000,y-GetDefCoreVal("Height","DefCore",cID)*500,this()); 
	SetDTRotation(pTank->~ContentAngle(cID), -GetDefCoreVal("Width","DefCore",cID)/2+pTank->~ContentOffsetX(cID),y/1000-GetDefCoreVal("Height","DefCore",cID)/2+pTank->~ContentOffsetY(cID), this(),0,1,0,0);
	if(GetType(contentID)==C4V_C4Object() && GameCall("MainEnergySupply"))
	{
		if(GetEnergy(contentID)<GetPhysical("Energy",0,contentID)/1000)
			if(Random(2)) CreateParticle("PxSpark",RandomX(-10, 10),RandomX(-10,10)+y/1000,0,-10,Random(25)+10,RGBa(200,200,255,50));
	}
	SetPosition(GetX(pTank),GetY(pTank));
	return(1);
}

func Set(newContentID,tank)
{
	contentID = newContentID;
	var cID = newContentID;
	if(GetType(newContentID)==C4V_C4Object())
	{
		var graphics = GetGraphics(newContentID);
		SetGraphics(graphics[0],this(),graphics[2],graphics[3],graphics[4],graphics[5],graphics[6]);
		SetColorDw(GetColorDw(newContentID),this());
		cID = graphics[2];
	}
	if(cID==MF5B)
		contentAction=["","Moff"];
	if(cID==MI5B)
		contentAction=["","Miffel"];
	if(cID==ST5B)
		contentAction=["","Stippel"];
	if(cID==KG5B)
		contentAction=["","Queen"];
	if(cID==HZCK)
		contentAction=["","ClonkJump"];
	iTimer=Random(360);
	SetAction(contentAction[1]);
	if(GetType(newContentID)!=C4V_C4Object())
		SetGraphics(contentAction[0],this(),cID);
	if(tank)
		pTank = tank;
	Timer();
	return(1);
}

func IsTarget(pObj){return(pTank==pObj);}