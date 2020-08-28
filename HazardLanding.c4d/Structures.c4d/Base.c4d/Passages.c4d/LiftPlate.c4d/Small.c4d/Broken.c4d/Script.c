/*-- Kleine kaputte Schwebeplatte --*/
#strict

local x,y;

func ControlDigDouble(pClonk)
{
	if(FindContents(CNKT,pClonk))
	{
		var pPlate=CreateObject(NewID(),0,0,-1);
		if(GetY()-30>y) y= GetY()-30;
		SetPosition(x,y,pPlate);
		Local(0,pPlate)=Local(0);
		Local(1,pPlate)=Local(1);
		Local(2,pPlate)=Local(2);
		Local(3,pPlate)=Local(3);
		Local(4,pPlate)=Local(4);
		Local(5,pPlate)=Local(5);
		RemoveObject(FindContents(CNKT,pClonk));
		RemoveObject();
	}
	else
	{
		Message("Kein Reperaturkit",this());
		Sound("Error");
	}
	return(1);
}

func NewID(){return(_LFS);}