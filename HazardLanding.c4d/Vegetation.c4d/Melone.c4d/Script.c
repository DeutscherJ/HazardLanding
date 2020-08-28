/*-- Melone --*/

#strict

func Initialize()
{
  SetR(90*Random(5));
  return(1);
}

func Kickable(){return(1);}
func Schlagable(){return(1);}

func Hit()
{
	var i= Random(6);
	CreateObject(FTPT,0,0,GetOwner())->Init(0,GetR(),i);
	CreateObject(FTPT,0,0,GetOwner())->Init(1,GetR(),i);
	CreateObject(FTPT,0,0,GetOwner())->Init(2,GetR(),i);
	CastObjects(DTB7,3,15);
	CastParticles("PxSpark",20,30,0,0,30,80,RGB(255,0,0),RGB(255,0,0));
	RemoveObject();
	Sound("Splatter1");
	return(1);
}