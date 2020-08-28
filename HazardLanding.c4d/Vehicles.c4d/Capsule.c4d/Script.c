/*-- Landekapsel --*/

#strict

local flame;


/* Initialisierung */

protected func Initialize()
{
  SetAction("Flight");
  SetComDir(COMD_Down());
  // Flammeneffekt
  flame = CreateObject(SCAF,0,35);
  flame->Init(this());
  return(1);
}

protected func ContactBottom()
{
  // nur reagieren, wenn noch im Flug
  if (GetAction() ne "Flight")
    return(1);
  SetAction("Land");
  flame->SwitchOff();
  return(1);
}


/* Türsteuerung */

private OpenEntrance:  return(SetEntrance(1));
private CloseEntrance: return(SetEntrance(0));

private SoundOpenDoor: 
  Sound("SteelGate2");
  var max = GetMaxDamage();
  ShowInfoBar(SBQ0, this(), max-GetDamage(), max, 1, 1);
  return(1);

private SoundCloseDoor: return(Sound("SteelGate2"));

public ActivateEntrance:
  // nicht im Flug
  if (GetAction() eq "Stand")
    SetAction("OpenDoor");
  return(1);


/* Uplink-Steuerung */

protected ContainedUp:
  [Kauf|Image=SUPL|Condition=GetUplink]
  var uplink = GetUplink();
  if (!uplink)  return(0);
  if (HasEMP()) return(Sound("Error"));
  uplink->KeyUp(Par(0));
  return(1);

protected ContainedDig:
  [Verkauf|Image=SUPL|Condition=GetUplink]
  var uplink = GetUplink();
  if (!uplink)  return(0);
  if (HasEMP()) return(Sound("Error"));
  uplink->KeyDig(Par(0));
  return(1);

private GetUplink:
  return(FindObject(SUPA,0,0,0,0,0,"Turn",this()));


/* Zerlegen */

protected func ContainedDigDouble(clonk)
{
  [Zerlegen]
  if (GetUplink())
    return(0);
  if (FindOtherContents(HZCK))
    return(PlayerMessage(GetOwner(clonk), "Kapsel muss zum Zerlegen|leer sein!", this()));
  var obj;
  while (obj = FindContents(HZCK))
    Exit(obj, 0,-5);
  Split2Components();
  return(1);
}


/* Schaden */

protected Damage:
  // zu viel Schaden?
  if (GetDamage() >= GetMaxDamage())
    return(Destroy());
  // Anzeige
  var max = GetMaxDamage();
  ShowInfoBar(SBQ0, this(), max-GetDamage(), max, 5, 1);
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

public GetMaxDamage: return(60);
public Repairable: return(1);

