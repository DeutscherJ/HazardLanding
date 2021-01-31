/*-- Neues Script --*/

#strict
#appendto VALG
#appendto MONE
#appendto WPHT

func ConfigurableInChooserMenu(){return(1);}
	
func CooseMenu(pClonk,pChooser)
{
	CreateMenu(GetID(), pClonk, 0, 0, Format("Anzahl der %s ändern",Blar()), 0, 1);
	AddMenuItem(Format("%d Mehr",Interval()),    Format("ChangeNumber(1,Object(%d))",ObjectNumber(pClonk)), CHOS, pClonk, 0,0, "Erhöhe Anzahl",2,1);
	AddMenuItem(Format("%d Weniger",Interval()), Format("ChangeNumber(-1,Object(%d))",ObjectNumber(pClonk)), CHOS, pClonk, 0,0, "Senke Anzahl",2,2);
	AddMenuItem(Format("Fertig: %d %s",Points(),Blar()), Format("Ready(Object(%d))",ObjectNumber(pClonk)), CHOS, pClonk, 0,0, "",2,3);
	return(1);
}

func ChangeNumber(iPlus,pClonk)
{
	LocalN(PointString())+=iPlus*Interval();
	CooseMenu(pClonk);
	var menuPos = 1;
	if(iPlus==1) menuPos = 0;
	SelectMenuItem(menuPos,pClonk);
	return(1);
}

func Ready(pClonk)
{
	FindObject(CHOS)->~OpenMenu();
	return(1);
}

func Points()
{
	return(LocalN(PointString()));
}

func PointString()
{
	if(GetID()==VALG) return("TargetScore");
	if(GetID()==MONE) return("TargetWealth");
	if(GetID()==WPHT) return("AllowedDeaths");
	return("");
}

func Blar()
{
	if(GetID()==VALG) return("benötigten Siedlungspunkte");
	if(GetID()==MONE) return("benötigten Geldpunkte");
	if(GetID()==WPHT) return("Erlaubte Wipftote ");
	return("");
}

func Interval()
{
	if(GetID()==VALG) return(100);
	if(GetID()==MONE) return(100);
	if(GetID()==WPHT) return(1);
	return(0);
}