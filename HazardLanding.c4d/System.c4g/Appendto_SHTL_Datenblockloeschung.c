/*-- Datenblöcke können auch in einem Shuttle abgegeben werden --*/

#strict
#appendto SHTL

func Collection(pObj,fPut)
{
	for(var i=0; Contents(i,pObj);i++)
	{
		var cont = Contents(i,pObj);
		if(cont->~DataCube())
			cont->~Saved(pObj);
	}
	return(_inherited(pObj,fPut));
}