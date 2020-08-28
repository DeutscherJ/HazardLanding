/*-- Liane --*/

#strict
#include LADR

func Initialize() {
	_inherited();
	
	SetAction("Vine"); //damit sie nicht runterfallen ;)
	SetPhase(Random(10));
	ID = GetID();
	sizeX = GetDefCoreVal("Width",0,GetID())/2;
	sizeY = GetDefCoreVal("Height",0,GetID())/2;
	Graphics = AddEffect("LadderPartSave",this(),1,0,this(),GetID());
	ID = AddEffect("LadderPartSave",this(),1,0,this(),GetID());
	//AddGraphics("Part1",LADR);
	AddPart(); //einen Teil hinzufügen :>
	AdjustSize();
	Set(1);
	SetGraphics (0,this(),L_LA,1,1); 
	return(1);
}