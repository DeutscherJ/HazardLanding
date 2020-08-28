/*-- Topf --*/

#strict

public func ContactBottom()
{
	if(Abs(GetXDir())+Abs(GetYDir())>25) Sound("PotPickup");
	if(Abs(GetXDir())+Abs(GetYDir())>40) Shatter();
	return(1);
}

public func ContactTop()
{
	if(Abs(GetXDir())+Abs(GetYDir())>30) Shatter();
	return(1);
}

public func Shatter()
{
  CastObjects(SHRP,3,20);
  Sound("PotShatter");
  var rnd=Random(2);
  for(var i=0; i<3; i++)
  {
	  var scherbe=CreateObject(SP_1,0,8,-1);
	  scherbe->SetAction("Exist");
	  scherbe->SetPhase(rnd*3+i);
	  SetSpeed(RandomX(-35,35),RandomX(-35,35),scherbe);
	  SetRDir(RandomX(-60,60),scherbe);
  }	  
  while(Contents()) Exit(Contents(),0,5,RandomX(0,360));
  RemoveObject();
  return(1);
}
func Schlagable(){return(1);}
func Hammered(){return(Shatter());}
func Grabbed(){return(Sound("PotPickup"));}
func Incineration(){return(Shatter());}

//Gegenstände herausnehmen
protected func ControlDig(object pClonk)
{
  // Herausnehmen per Graben: Holen-Menü öffnen
  pClonk->SetCommand(0, "Get", this(), 0,0, 0, 1);
}

//Bei Hoch wird es geworfen hehehe
func ControlUp(pClonk)
{
	//Log(GetName(pClonk));
	pClonk->SetAction("Walk");
	SetSpeed((GetDir(pClonk)*2-1)*30,-30);
	SetRDir(RandomX(3,10)*(Random(2)*2-1));
	return(0);
}