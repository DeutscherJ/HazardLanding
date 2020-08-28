#strict
#include CHST

func Hit()
{
  Sound("Schepper");
  return(1);
}

protected func Opening() 
{
	return(1);
}
  
protected func Closing() 
{
	return(1);
}

func ControlUpDouble(pClonk)
{
	[Einpacken]
	if(Contents()) return(Message("Kiste muss leer sein",this()));
	Enter(pClonk);
	return(1);
}