/*--- Flint ---*/

#strict

protected func Hit()
{
  for(var r=0; r<360; r+=30)
  {
	  CreateNanite(r,1);
  }
  RemoveObject();
  return(1);
}

/* Kann in der Chemiefabrik hergestellt werden */
public func IsChemicalProduct() { return(1); }

func IsAlchemContainer() { return(true); }
func AlchemProcessTime() { return(100); }