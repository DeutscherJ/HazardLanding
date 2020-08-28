/*-- Schlafen --*/

#strict

global func Sleep(int iDuration, object pObj)
{
	if(!iDuration)
		iDuration = 36*10;//10 Sekunden
	if(!pObj)
		pObj = this();
	AddEffect("SleepNSpell",pObj,123,25,pObj,GetID(),iDuration);
	return(1);
}

global func IsSleeping(object pObj)
{
	if(!pObj) pObj=this();
	if(GetEffect("SleepNSpell",pObj))
		return(EffectVar(0,pObj,GetEffect("SleepNSpell",pObj)));
	return(0);
}

global func WakeUp(object pObj)
{
	if(!pObj) pObj=this();
	RemoveEffect("SleepNSpell",pObj);
	return(1);
}

global func FxSleepNSpellStart(object pTarget, int iEffectNumber, int iTemp, int iTime) {
  // temporäre aufrufe
  if(iTemp) return();
  // Scheintoter Zustand
  ObjectSetAction(pTarget,"Dead");
  // mit schnarchen anfangen
  Sound("Snore",0,pTarget,0,0,+1);
  // Zeit bis zum Aufwachen speichern
  EffectVar(0,pTarget,iEffectNumber)=iTime;
  // Fertig
  return(1);
}

global func FxSleepNSpellEffect(szNewEffect, pTarget, iEffectNumber)
  {
  // Wenn schon ein Schlafzauber wirkt, darf kein neuer dazukommen
  if (szNewEffect eq "SleepNSpell") return(-1);
  // Sonst keine Behandlung
  return();
  }

global func FxSleepNSpellStop(object pTarget, int iEffectNumber) {
  // clonk hat den Schlaf nicht überstanden ;)
  if(!GetAlive(pTarget)) return(1);
  // aufstehen
  ObjectSetAction(pTarget,"FlatUp",0,0,1);
  // mit schnarchen aufhören
  Sound("Snore",0,pTarget,0,0,-1);
  // stehenbleiben
  SetComDir(COMD_Stop(),pTarget);
  // Fertig
  return(1);
}

global func FxSleepNSpellTimer(object pTarget, int iEffectNumber, int iTime) {
  var iMaxTime=EffectVar(0,pTarget,iEffectNumber);
  if(iMaxTime==-1) iMaxTime = iTime*2;
  // nach einer bestimmten Zeit aufhören
  if(iTime>=iMaxTime) return(-1);
  // Zzz-Partikel casten
  CreateParticle("Zzz",AbsX(GetX(pTarget)),AbsY(GetY(pTarget)),2+(iTime%50)*3/25+RandomX(-1,+1),-5,60,
                 RGBa(255,255,255,(iTime-iMaxTime/2)**2 * 180*4/iMaxTime**2));
}

global func FxSleepNSpellDamage(object pTarget, int iEffectNumber, int iDmgEngy) {
  // Bei Damage aufwachen
  RemoveEffect(0,pTarget,iEffectNumber);
  return(iDmgEngy);
}

global func FxSleepNSpellInfo() { return("{{MBOT}} $SpellInfo$"); }
