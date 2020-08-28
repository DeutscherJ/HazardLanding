/*-- Neues Objekt --*/

#strict

static stationCount;

func Construction()
{
	SetAction("Exist");
	return(1);
}

func Set(letterNum,size,number)
{
	if(!size) size=100;
	if(!stationCount) stationCount=[1,1,1,1,1,1,1,1,1,1];
	if(!letterNum) letterNum=0;
	if(!number)
	{
		number=stationCount[letterNum]-1;
		stationCount[letterNum]=stationCount[letterNum]+1;
	}
	SetClrModulation(LetterColor(letterNum));
	SetAction("Exist");
	SetPhase(letterNum);
	var numObj = CreateObject(LTG4,21*size/100,15,-1);
	numObj->SetAction("Exist");
	SetClrModulation(LetterColor(letterNum),numObj);
	SetPhase(number,numObj);
	SetDir(1,numObj);
	SetCon(size);
	SetCon(size,numObj);
	return(1);
}

func LetterColor(i)
{
	if(i==0) return(RGB(200,50,50));
	if(i==1) return(RGB(50,200,0));
	if(i==2) return(RGB(50,50,200));
	if(i==3) return(RGB(200,200,50));
	if(i==4) return(RGB(50,200,200));
	if(i==5) return(RGB(200,50,200));
	return(RGB(200,200,200));
}

func Left(i)
{
	if(!i) i=0;
	var size = GetCon();
	SetCon(100);
	var arrowObj = CreateObject(LTG4,-21*size/100,15,-1);
	SetDir(2,arrowObj);
	SetPhase(i,arrowObj);
	SetCon(size);
	SetCon(size,arrowObj);
	SetClrModulation(GetClrModulation(),arrowObj);
	return(arrowObj);
}

func Right(i)
{
	if(!i) i=1;
	var size = GetCon();
	SetCon(100);
	var arrowObj = CreateObject(LTG4,21*size/100,15,-1);
	SetDir(2,arrowObj);
	SetPhase(1,arrowObj);
	SetCon(size);
	SetCon(size,arrowObj);
	SetClrModulation(GetClrModulation(),arrowObj);
	return(arrowObj);
}