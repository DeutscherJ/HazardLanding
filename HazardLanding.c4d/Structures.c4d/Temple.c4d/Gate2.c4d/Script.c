/*-- Steintor --*/

#strict

func Hit(){return(Sound("RockHit*"));}

func ControlDigDouble(pClonk)
{
	for(var i=0; GetComponent(0,i); i++)
	{
		CastObjects(GetComponent(0,i),GetComponent(GetComponent(0,i)),5);
	}
	RemoveObject();
	return(1);
}