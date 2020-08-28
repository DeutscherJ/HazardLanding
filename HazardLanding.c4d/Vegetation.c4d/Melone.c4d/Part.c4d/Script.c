/*-- Stück --*/

#strict

func Initialize(){return(SetAction("Exist"));}
func Hit(){	CastParticles("PxSpark",5,20,0,0,10,30,RGB(255,0,0),RGB(255,0,0));}
func Kickable(){return(1);}

func Init(i,r,d)
{
	SetSpeed(RandomX(-25,25),RandomX(-25,25));
	SetPhase(i);
	SetR(r);
	SetDir(d);
	SetRDir(RandomX(-3,3));
	return(1);
}