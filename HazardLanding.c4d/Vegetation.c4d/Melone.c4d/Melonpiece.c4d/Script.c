/* --- Melonenstück --- */

#strict 2

protected func ContextEat(object pClonk)
{
	[$TxtEat$|Image=DTB7]
	return Eat(pClonk);
}

protected func Activate(object pClonk)
{
	[$TxtEat$|Image=DTB7]
	return Eat(pClonk);
}

protected func Eat(object pClonk)
{
	if (!pClonk)
		return 1;
	pClonk->~Feed(GetFeedValue());
	RemoveObject();
	return 1;
}

public func GetFeedValue()
{
	return 30;
}

func Hit(){	CastParticles("PxSpark",5,20,0,0,10,30,RGB(255,0,0),RGB(255,0,0));}
func Kickable(){return(1);}