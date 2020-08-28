#strict
#include BCTG

func Destroy()
{
	Sound("Blast2");
	Sound("GlassBreak");
	if(TankContent()) TankContent()->~Free();
	SetPosition(GetX(),GetY(),CreateObject(DPG4,0,0,-1));
	RemoveObject();
	return(1);
}

func ContentAngle(contentID)
{
	if(contentID==ST5B) return(90);//Stippel drehen
	if(contentID==KG5B) return(90);
	return(0);
}

func ContentOffsetX(contentID)
{
	if(contentID==ST5B) return(-3);
	if(contentID==KG5B) return(-3);
	return(0);
}