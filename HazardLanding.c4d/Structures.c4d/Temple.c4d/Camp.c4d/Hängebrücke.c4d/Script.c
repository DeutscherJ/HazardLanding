/*Hängebrücke*/

#strict

func Set(int r)
{
	var oldR = GetR();
	var yOld = Sin(oldR,96); 
	var xOld = Abs(Sin(oldR,20)); 
	SetR(r);
	var yNew = Sin(r,96); 
	var xNew = Abs(Sin(r,20)); 
	SetPosition(GetX()-xNew+xOld,GetY()-yOld+yNew);
	return(1);
}

func GetPos(dir)
{
	if(!dir) dir=DIR_Right;
	var mult = dir*2-1;
	return([GetX()+Cos(GetR(),90)*mult,GetY()+3+Sin(GetR(),90)*mult]);
}

/*
SetPosition(GetX()+90,GetY()+3,CreateObject(FLNT))
	SetPosition(GetX()+Cos(GetR(),90),GetY()+3+Sin(GetR(),90),CreateObject(FLNT))