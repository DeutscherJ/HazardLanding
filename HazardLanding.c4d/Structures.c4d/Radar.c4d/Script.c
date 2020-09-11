/*-- toller Radar --*/

#strict
#include BOB2

local basement, reach, minEnemyNum, minAlienNum,pMarkerArray, manager;

public EnoughEnergy: return(GetEnergy());
public IsEnergyConsumer: return(1);
public InfoBarPos:  return(5);
public InfoBarSize: return(3);
public GetMaxDamage: return(65);

func Initialize(a,b,c)
{
  manager = CreateObject(BMAN,0,0,GetOwner());
  manager->~Init(this(), 1);
  SetAction("Radar");
  pMarkerArray=[];
  reach=50;
  return(_inherited(a,b,c));
}

func Timer()
{
	//Energieverbrauch
	if(!GetEnergy()) return(SetAction("Idle"));
	if(GetAction() ne "Radar") SetAction("Radar");
	
	DoEnergy(-1);
	//Ist ein gesteuerter Clonk in der Nähe?
	var pClonk = FindObject2(Find_OCF(OCF_CrewMember()),Find_Distance(30));
	if(!pClonk) return(0);
	
	//Zeige ihm an, wieviele Lebewesen sich in der Nähe befinden
	var i = ObjectCount2(Find_Distance(reach),Find_OCF(OCF_Alive()));
	Message("%d L",this(),i);
	return(1);
}

func ControlLeft(pClonk)
{
	[Reichweite Verringern]
	reach=Max(50,reach-10);
	Sound("Click");
	
	ShowRange(pClonk);
	return(1);
}

func ControlRight(pClonk)
{
	[Reichweite Erhoehen]
	reach=Min(1000,reach+10);
	Sound("Click");
	ShowRange(pClonk);
	return(1);
}

func ShowRange(pClonk)
{
	for (var i = 0; i < 72; i++)
	{
		var marker = pMarkerArray[i];
		if(!marker)
			marker = CreateObject(SMK1, 0,0, GetOwner(pClonk));
		pMarkerArray[i] = marker;
		SetPosition(GetX()+Cos(i*5,reach),GetY()+Sin(i*5,reach),marker);			
		marker->~SetTimer(2);
	}
	return(1);
}

func ControlDig(pClonk)
{
	//Erstelle ein Menü um die Anzeige und Alarmoptionen ein zu stellen
	return(1);
}

protected func Construction()
{
  basement = CreateObject(BS08,4,+8,GetOwner());
}

func Destruction()
{
  if(basement) RemoveObject(basement);
  if(manager)  RemoveObject(manager);
  return(_inherited());
}