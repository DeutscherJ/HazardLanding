/*-- Datenblöcke können auch in einem Shuttle abgegeben werden --*/

#strict
#appendto SHTL

func Collection2(pObj)
{
	for(var i=0; Contents(i,pObj);i++)
	{
		var cont = Contents(i,pObj);
		if(cont->~DataCube())
			cont->~Saved(this());
	}
	if(Contents(0,pObj))
	{
		for(var i=0; Contents(i,pObj);i++)
		{
			var cont = Contents(i,pObj);
			if(cont->~DataCube())
				cont->~Saved(this());
		}
	}
	return(_inherited(pObj));
}