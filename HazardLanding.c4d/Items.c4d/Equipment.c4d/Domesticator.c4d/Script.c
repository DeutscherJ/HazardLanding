/*-- Domestikator --*/

#strict

local fActive,iAngle;

public func IsMachine(){return(1);}
public func IsThreat(){return(fActive);}
public func MaxDamage() { return 80; }
public func IsDrone() { return true; }
public func IsEquipment() { return true; }
public func IsMachine() { return true; }
public func IgnoreFriendlyFire() { return true; }
public func IsBulletTarget(){return(1);}
public func IsVehicleProduct(){return(1);}

//Wenn ein Gebäude betreten wird abschalten
func Entrance()
{
	fActive=true;
	ControlDigDouble();
	return(1);
}

func Initialize()
{
	SetColorDw(RGB(100,100,100));
	return(1);
}

func ControlDigDouble()
{
	[Aktiviere]
	fActive = !fActive;
	if(fActive)
		SetAction("On");
	else
	{
		SetColorDw(RGB(100,100,100));
		SetAction("Idle");
	}
	return(1);
}

public func OnDmg(int damage, int type)
{
  if(type == DMG_Melee)      return -30;
  if(type == DMG_Projectile) return +20;
  if(type == DMG_Fire)       return +30;
  if(type == DMG_Explosion)  return -10;
  if(type == DMG_Energy)     return -40;
  if(type == DMG_Bio)        return +50;
}

public func Damage() {
	if(GetDamage() < MaxDamage()) return;
  Explode(20);
}

func Timer()
{
	if(!fActive || EMPShocked()) return(0);
	
	var iOuterRadius = 200;
	var iInnerRadius = 100;
	
	//Effekte
	ScheduleCall(this(),"ParticleTimer",1,10);
	
	//In 250 Pixel Radius nur die Domestizierung "refreshen"
	for(var pObj in FindObjects(Find_Distance(iOuterRadius),Find_Func("MaxIntelligence",90),Find_OCF(OCF_Alive())))
	{
		//SetOwner(pObj,GetOwner());
		//Bekehrungseffekt auswirken
		if(GetEffect("Domestize",pObj) && GetOwner(pObj)==GetOwner())
		{
			EffectVar(1,pObj,GetEffect("Domestize",pObj))+=2;
			//Message("%d",pObj,EffectVar(1,pObj,GetEffect("Domestize",pObj)));
		}
	}
	
	//In 50 Pixel Radius Domestizierung neu machen
	for(pObj in FindObjects(Find_Distance(iInnerRadius),Find_Func("MaxIntelligence",90),Find_OCF(OCF_Alive())))
	{
		//SetOwner(pObj,GetOwner());
		//Log("BLa1");
		//Bekehrungseffekt auswirken
		AddEffect("Domestize",pObj,100,10,0,GetID(),GetOwner());//relativ niedriege Priorität
	}
	
	return(1);
}

func ParticleTimer()
{
	iAngle+=2;
	if(iAngle>360) iAngle-=360;
	var iOuterRadius = 200;
	var iInnerRadius = 100;
	SetColorDw(RGB(200,200,220+Sin(iAngle*12,20)));
	if(!Random(15))
		SetColorDw(RGB(255,255,255));
	CreateParticle("DomesticWave",0,0,0,0,iOuterRadius*10+Sin(iAngle*12,40)+RandomX(-10,10),RGBa(100,200,255,80));
	CreateParticle("DomesticWave",0,0,0,0,iInnerRadius*10-Sin(iAngle*12,30)+RandomX(-10,10),RGBa(100,200,255,70));
	return(1);
}

protected func FxDomestizeEffect(szNewEffect, pTarget, iEffectNumber)
  {
  // Wenn schon ein Schlafzauber wirkt, darf kein neuer dazukommen
  if (szNewEffect eq "Domestize")
  {
	EffectVar(1,pTarget,iEffectNumber)+=6;//Alle Effekte hochzählen
	return(-1);
  }
  // Sonst keine Behandlung
  return();
  }

func FxDomestizeStart(object pTarget, int iEffectNumber, int iTemp, int iOwner)
{
	/*if(GetEffect("Domestize",pTarget))
		if(GetEffectCount("Domestize",pTarget)>=2)
		{
			//Log("Bla%d Bla%d",iEffectNumber,GetEffect("Domestize",pTarget));
			EffectVar(1,pTarget,iEffectNumber)+=10;//Alle Effekte hochzählen
			return(-1);//Hinzufügen verhindern, wenn schon da
		}*/
	//Log("BLa3");
	//alten Besitzer speichern
	EffectVar(2,pTarget,iEffectNumber)=GetOwner(pTarget);
	EffectVar(1,pTarget,iEffectNumber)=10;
	EffectVar(3,pTarget,iEffectNumber)=iOwner;
}

func FxDomestizeTimer(object pTarget, int iEffectNumber)
{
	EffectVar(1,pTarget,iEffectNumber)=Min(100,EffectVar(1,pTarget,iEffectNumber)-1);
	var clr = GetPlrColorDw(EffectVar(3,pTarget,iEffectNumber));
	if(EffectVar(1,pTarget,iEffectNumber)<0)
		return(-1);	
	//Besitzer ändern
	if(EffectVar(1,pTarget,iEffectNumber)>80)
		if(EffectVar(3,pTarget,iEffectNumber)!=GetOwner(pTarget))
		{
			SetOwner(EffectVar(3,pTarget,iEffectNumber),pTarget);
			CastParticles("PxSpark",6,30,AbsX(GetX(pTarget)+RandomX(-5,5)),AbsY(GetY(pTarget))+RandomX(-5,5),60,100,clr,clr,pTarget);//clr);//RGBa(200,200,255,150)
			pTarget->~ChangeOwner(EffectVar(3,pTarget,iEffectNumber),EffectVar(2,pTarget,iEffectNumber));
		}
	//Partikeleffekt
	if(EffectVar(3,pTarget,iEffectNumber)!=GetOwner(pTarget))
		CreateParticle("PSpark",AbsX(GetX(pTarget)+RandomX(-5,5)),AbsY(GetY(pTarget))+RandomX(-5,5),0,0,30,clr,pTarget,1);//,clr);
	else
		CreateParticle("PxSpark",AbsX(GetX(pTarget)+RandomX(-5,5)),AbsY(GetY(pTarget))+RandomX(-5,5),0,0,50,clr,pTarget,1);//,clr);
	//Log("Blar");
}

func FxDomestizeStop(object pTarget, int iEffectNumber)
{
	//Particleeffekte
	//Soundeffekt?
	//Besitzer zum Ursprünglichen Besitzer zurückändern
	if(GetOwner(pTarget)==EffectVar(3,pTarget,iEffectNumber))
		pTarget->~ChangeOwner(EffectVar(2,pTarget,iEffectNumber),EffectVar(3,pTarget,iEffectNumber));
	SetOwner(EffectVar(2,pTarget,iEffectNumber),pTarget);
	//Log("Blar4");	
	//CreateParticle("PSpark",AbsX(GetX(pTarget)+RandomX(-5,5)),AbsY(GetY(pTarget))+RandomX(-5,5),0,0,500);

}
