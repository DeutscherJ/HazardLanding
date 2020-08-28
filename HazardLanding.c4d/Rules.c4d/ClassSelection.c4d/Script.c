#strict

protected func Activate(iPlr) {
  MessageWindow(GetDesc(),iPlr);
}

//CreateObject(KSSL)->~ActivateSelection(this())

global func ClassSelection() {
  return(FindObject(KSSL));
}

// Kann mittels des Spielzielauswählers ausgewählt werden
public func IsChooseable() { return(1); }

func ActivateSelection(pClonk)
{
	if(GetMenu(pClonk)) return();
	CreateMenu(MEN1,pClonk,0,0,"Klassenwahl",0,1);
	SetMenuSize(3,2,pClonk);
	
	for(var iClass = 1; ClassData(iClass,1);iClass++)
	{
		AddMenuItem(ClassData(iClass,1),"SelectClass",ClassData(iClass,2), pClonk,0,pClonk, ClassDescription(iClass)); 
	}
	return(1);
}

func SelectClass(classID,pClonk)
{
	var classNum = GetClassNumByID(classID);
	var className = ClassData(classNum,1);
	var classData = ClassData(classNum);
	Log("%s ist als %s eingestiegen.",GetTaggedPlayerName(GetOwner(pClonk)),className);
	
	for(var kItem = 3; kItem<= GetLength(classData)-1; kItem+=2)
	{
		if(DefinitionCall (classData[kItem], "IsAmmo"))
			DoAmmo(classData[kItem],classData[kItem+1],pClonk);
		else if(DefinitionCall(classData[kItem],"IsAmmoPacket") || DefinitionCall(classData[kItem],"IsHazardGear") )
			for( var k = classData[kItem+1];k;k--)
				CreateContents(classData[kItem],pClonk)->~Activate(pClonk);
		else
		{
			CreateContents(classData[kItem],pClonk,classData[kItem+1]);
		}
	}
	SetGraphics(ClassData(classNum,3),pClonk,KSSL);
	return(1);
}


func ClassData(iClassNum,iData)
{
	var classData = 0;
	if(iClassNum == 1)
		classData = ["Sturmtrupp",ASRF,"Hazard",ASRF,1,PIWP,1,STAP,2,GRAM,3];
	if(iClassNum == 2)
		classData = ["Phasor",GGWP,"Spy",GGWP,1,ENAP,2,KLAS,1,PIWP,1,STAP,1];
	if(iClassNum == 3)
		classData = ["Sprengmeister",BO5B,"Wooza",BO5B,2,ZR5B,1,PIWP,1,STAP,2,GLWP,1];
	if(iClassNum == 4)
		classData = ["Grenadier",GLWP,"Future",GLWP,1,GRAP,2,KRFL,1,PIWP,1,STAP,2];
	if(iClassNum == 5)
		classData = ["Pyro-Desinfektor",FTWP,"Schutzanzug",FTWP,1,GSAP,2,PIWP,1,STAP,2,GSAP,1];
	if(iClassNum == 6)
		classData = ["Mediziner",MEDI,"TheEye",MEDI,2,NH5B,1,PIWP,1,STAP,2,GRAM,3];
	if(iClassNum == 7)
		classData = ["Jettruppe",JTPK,"Dune",JTPK,1,PIWP,1,STAP,2,GRAM,3];
	if(iClassNum == 8)
		classData = ["Berserker",MEZL,"Hat",MEZL,1,GSAP,2,BALL,1,PIWP,1,STAP,2,GRAM,3];
	if(iClassNum == 9)
		classData = ["Ingenieurdroide",DRSU,"Droid",KLAS,1,KRFL,1,DRSU,1,SSAK,1,PIWP,1,STAP,2,GRAM,3];
	if(classData ==0) return(0);
	if(iData==0) return(classData);
	if(iData>=0) return(classData[iData-1]);
	return(0);
}

func ClassDescription(iClassNum)
{
	var classData = ClassData(iClassNum);
	var log = Format("Wird ausgerüstet mit:");
	for(var kItem = 3; kItem<= GetLength(classData)-1; kItem+=2)
	{
		log = Format("%s %d %s, ",log,classData[kItem+1],GetName(0,classData[kItem]));
	}
	return(log);
}

func GetClassNumByID(classID)
{
	for(var i=1;ClassData(i,2);i++)
	{
		if(ClassData(i,2)==classID) return(i);
	}
	return(0);
}
/*
Ein Paar IDs
//Minen
 MINE
 LMIN
 SMIN

//Munition
 STAP//Munition
 ENAP//Energiepacks
 GRAP//Granaten
 GSAP//Benzin
 MIAP///Raketen
 ATB_//Atombomben
 A35B//Bomben
 A15B//MG-Magazin
 A25B//Raketen
 
 //

//Ausrüstung
 JTPK//Jetpack
 HSHD//Schild
 FLSH//Taschenlampe
 HARM//Rüstung
 AIRT//Lufttank

 NLGT//Leuchtstab
 NVDN//Novodekan
 DRSU//Unterstüzungsdrone
 MEDI//Medipack

//Upgrades
 KLAS//Laser
 KSLM//SChleim
 KRFL//Waffenteil

//Waffen
 BZWP//Bazooka
 MEZL//Motorsäge
 ENWP//Energiegewehr
 FTWP//Flammenwerfer
 GLWP//Granatenwerfer
 MIWP//Minigun
 GGWP//Motegun
 PIWP//Pistole
 PGWP//Pumpgun