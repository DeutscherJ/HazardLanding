/*-- toller Radar --*/

#strict
#include BOB2

local basement, reach, minEnemyNum, minAlienNum;

func Initialize()
{
  SetAction("Radar");
}

func Timer()
{
	//Ist ein gesteuerter Clonk in der Nähe?
	
	//Zeige ihm an, wieviele Lebewesen sich in der Nähe befinden
	return(1);
}

func ControlLeft()
{
	[Reichweite Verringern]
	reach=Max(50,reach-10);
	Sound("Click");
	return(1);
}

func ControlRight()
{
	[Reichweite Erhoehen]
	reach=Min(1000,reach+10);
	Sound("Click");
	return(1);
}

func ControlDig()
{
	//Erstelle ein Menü um die Anzeige und Alarmoptionen ein zu stellen
	return(1);
}

protected func Construction()
{
  basement = CreateObject(BS08,4,+8,GetOwner());
}