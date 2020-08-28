/*-- Neohexin --*/

#strict

public func IsChemicalProduct() { return(1); }
func Activate(pClonk)
{
  if (OnFire(pClonk)) return(Feuer(pClonk));
  if (GetBreath(pClonk)<GetPhysical("Breath",0,pClonk)/1000) 
    return(Luft(pClonk));
  if (GetEnergy(pClonk)<GetPhysical("Energy",0,pClonk)/1000)
    return(Energie(pClonk));
  PlayerMessage(GetOwner(Par(0)),"%s geht es gut.",Par(0),GetName(Par(0)));
  Sound("Error");
  return(1);
}

func Feuer(pClonk)
{
  Extinguish(pClonk);
  Sound("Pshshsh");
  RemoveObject();
  return(1);
}

func Luft(pClonk)
{
  DoBreath(GetPhysical("Breath",0,pClonk)/1000,pClonk);
  Sound("Breath");
  RemoveObject();
  return(1);
}

func Energie(pClonk)
{
  DoEnergy(GetPhysical("Energy",0,pClonk),pClonk);
  Sound("NHEnergie");
  RemoveObject();
  return(1);
}

func Hit()
{
  Sound("MetalHit*");
  return(1);
}

func HealAmount(){return(1337);}

// KI-Behandlung
protected func AI_Inventory(object pClonk)
{
  // Benutzen, wenn der Clonk weniger als 1/2 Leben hat
  if(pClonk->GetEnergy() < pClonk->GetPhysical("Energy") * 1/2 / 1000)
    // Benutzen (verzögert einsetzen)
    ScheduleCall(this, "Activate", 1, 0, pClonk);
  // übernehmen wir
  return(1);
}