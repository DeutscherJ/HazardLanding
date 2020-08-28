/*-- Gesicht --*/

#strict

local timerCount;

func Initialize()
{
  // Timer initialisieren
  timerCount = 0;
	SetAction("Travel");
	SetComDir(COMD_Left);
	return(1);
}

public func Timer()
{
  // Wählt zufällige Richtung aus
	var r = Random(360);
  
  // Berechnet Koordinaten für einen Abstand von 70
	var x =  Sin(r, 70);
	var y = -Cos(r, 70);
  
  // Erzeugt zufällige Effekte an den zufälligen Koordinaten
	CreateParticle("PSpark", x, y, 0, 0, 70, RGB(Random(255), Random(255), Random(255)));
	CreateParticle("Smoke", RandomX(-65, 65), 50, 0, 0, 170, RGB(Random(255), Random(255), Random(255)));
	
  // Timer-Zähler erhöhen und Moduloarithmetik anwenden um ihn bei 30 zurückzusetzen
  timerCount = Max(0,timerCount-1); 
	
  var target = FindObject2(Find_Hostile(GetOwner()), Find_InRect(-600, -40, 1200, 80), Find_OCF(OCF_Alive));
  
  // Wenn der Timer auf 0 steht und sich ein feindliches Lebewesen Rechts oder Links befindet schießen
	if(target && !timerCount)
	{
		var ammo = CreateObject(SHT2, sign(GetX(target)-GetX(this())) * 35, 20, GetOwner());
		MuzzleFlash(400, this(), 0, 20, Angle(GetX(ammo), GetY(ammo), GetX(target), GetY(target)), RGBa(150, 150, 255, 0));
		ammo->Launch(Angle(GetX(ammo), GetY(ammo), GetX(target), GetY(target)), 400, 800, 8, 200, 100, 0, 250);
		timerCount = 36;
    Sound("ER", 0, this(), 100, 0, 0);
	}
  
  // Selten kann es passieren dass dieser Gott das große Kotzen bekommt
  if(!Random(220))
  {
    ScheduleCall(this(), "kotzen", 2, 10);
    Sound("SFX", 0, this(), 100, 0, 0);
  }
  
	return(1);
}

public func kotzen()
{
  var nigger = CreateObject(JCLK, 0, 30, NO_OWNER);
  SetLocal(121, (((Random(2) * 2) - 1) * (Random(13) + 4)), nigger);
  SetLocal(122, Random(360), nigger);
  //Schedule("Local(122) = Local(122) + Local(121);", 2, 1500, nigger);
  //Schedule("SetDTRotation(Local(122), this());", 2, 1500, nigger);
  nigger->SetAction("Tumble");
  SetPhase(Random(5),nigger);
  while(RemoveVertex(0, nigger));
  SetXDir(Random(41) - 20, nigger);
  SetYDir(Random(5), nigger);
}

public func sign(int i)
{
  if(i > 0) { return(1); }
  else if(i < 0) { return(-1); }
  else { return(0); }
}

public func Damage()
{
  if(LessThan(GetDamage(), 300)) { return(0); }
  SetAction("Idle");
  Sound("Blast2");
  return(1);
}