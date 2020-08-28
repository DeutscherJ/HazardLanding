/* Selbstschussanlage */

#strict

// Local(0) - potentielles Ziel
// Local(3) - Munition
public func IsMachine() { return true; }
public func IsDrone() { return true; }

func IsBulletTarget()
{
	if(!Random(6)) return(1);
	//DoDamage(Random(4));
	return(0);
}

Initialize:
  SetAction("Ready");
  SetDir(Random(2));
  SetLocal(3,20);
  return(1);

Check:
  if(GetAction()eq"Fire") return(1);
  if(Local(3)<=0) return(SetAction("Reload"));
  if(GetAction()eq"Loading") return(1);
  if(SetLocal(0,FindObject2(Find_Or(Find_Hostile(GetOwner()),Find_Owner(-1)),Find_InRect(-170,-10,240,30),Find_OCF(OCF_Alive))))
	if(PathFree(GetX(),GetY(),GetX(Local(0)),GetY(Local(0))))
	  SetAction("Fire");
  return(1);

Schuss:
  //if(SEqual(GetAction(),"ReadyRight")) if(Equal(Local(2),1)) SetAction("Ready");
  if(!Local(0)) return(SetAction("Ready"));
  if(ObjectDistance(this(),Local(0))>170 || Abs(GetY()-GetY(Local()))>20) return(SetAction("Ready"));
  if(GetX(Local(0))>GetX()) SetDir(DIR_Right);
  if(GetX(Local(0))<GetX()) SetDir(DIR_Left);
  if(Local(3)<=0) return(SetAction("Reload"));
  //if(!FindObject(0,-170,-10,167,30,OCF_Living())) return(SetAction("Ready"));
  
  var dir= GetDir()*2-1;
  MuzzleFlash(50,this(),10*dir,-6,90*dir);
  BulletCasing(3*dir,-4,10*dir,10,4);
  
  var ammo = CreateObject(SHT1,10*dir,-6,GetOwner());
  ammo->Launch(Angle(10*dir+GetX(),-6+GetY(),GetX(Local()),GetY(Local()))+RandomX(-3,3),300,600,4,100,3);
  
  Local(3)--;
  return(1);

func Reload()
{
	Local(3)=20;
	return(1);
}

func Hurt(a,b,c)
{
}

Death:
  Sound("Discharge");
  if(BitAnd(GetOCF(Contained()),OCF_Living())) DoEnergy(-100,Contained());
  if(Contained()) Exit();
  Sound("Blast2");
  CastObjects(DFLM,3,15);
  Explode(10);
  return(0);