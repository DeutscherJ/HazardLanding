/*-- Nachschubkapsel --*/

#strict

local flame, step, speedX, speedY;


/* Initialisierung */

protected func Initialize()
{
  SetAction("Flight");
  step = 0;
  // passenden Winkel finden (soll ja nicht zum Rand rausfliegen)
  var i;
  speedY = 200;
  while (1)
  {
    speedX = GetWind() + Random(400)-200;
    if ((GetX()-speedX*5 >= 0) && (GetX()+speedX*5 < LandscapeWidth()))
      break;
    // Endlosschleife verhindern
    if (++i > 20) break;
  }
  // Flammeneffekt
  flame = CreateObject(SCAG);
  flame->Init(this(), Angle(speedX,speedY,0,0));
  return(1);
}


/* Flug */

protected func Flight()
{
  if (step)
  {
    if (step > 3)
      return(SetAction("Open"));
    // Pseudo-Explosion
    CreateParticle("Blast", speedX/10, speedY/10, 0,0, 150, RGB(255,255,255));
    Smoke(speedX/10-2, speedY/10, 10);
    Smoke(speedX/10+2, speedY/10, 10);
    DigFree(GetX()+speedX/40, GetY()+speedY/40, 15);   // 0.25
    DigFree(GetX()+speedX/20, GetY()+speedY/20, 15);   // 0.5
    DigFree(GetX()+speedX/13, GetY()+speedY/13, 15);   // 0.75
    DigFree(GetX()+speedX/10, GetY()+speedY/10, 15);   // 1.0
    Sound("Blast1");
    // verlangsamen
    speedX = speedX * 3/4;
    speedY = speedY * 3/4;
    ++step;
  }
  SetXDir(speedX);
  SetYDir(speedY);
  return(1);
}

protected func Hit()
{
  if (GetAction() eq "Flight")
    if (!step)
    {
      step = 1;
      flame->SwitchOff();
    }
  return(1);
}


/* Zerlegen */

protected func ControlDigDouble(clonk)
{
  [Zerlegen]
  while(Contents())
	  Exit(Contents(),0,10);
  //if (Contents())
  //  return(PlayerMessage(GetOwner(clonk), "Kapsel muss zum Zerlegen|leer sein!", this()));
  Split2Components();
  return(1);
}


/* Schaden */

protected Damage:
  // im Flug gilt's nicht
  if (GetAction() eq "Flight")
    if (Par(0) > 0)
      DoDamage(-Par(0));
  // zu viel Schaden?
  if (GetDamage() >= GetMaxDamage())
    return(Destroy());
  return(1);

public Destroy:
  // Inhalt rausschleudern
  var obj;
  while (obj = Contents())
    Exit(obj,0,0,Random(360), Random(9)-4, -Random(5), Random(51)-25);
  // Zerstörung durch Explosion
  var i = GetMaxDamage() / 8;
  while (i)
  {
    obj = CreateObject(SFRX, Random(GetObjWidth() * 2/3) - GetObjWidth() / 3,
                             Random(GetObjHeight() * 2/3) - GetObjHeight() / 3, GetOwner());
    ObjectCall(obj, "Settings", i*3/2, 20, 1);
    --i;
  }
  // Explosion
  obj = CreateObject(SFRX, 0,0,GetOwner());
  ObjectCall(obj, "Settings", GetMaxDamage()/10, 50);
  Explode(20);
  return(1);


/* Eigenschaften */

public GetMaxDamage: return(40);
public Repairable: return(1);

