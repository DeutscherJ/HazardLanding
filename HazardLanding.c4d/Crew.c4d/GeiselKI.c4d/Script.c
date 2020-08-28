/*-- Ki-Steuerungsobjekt --*/

#strict
local pPuppet;

func Initialize()
{
  pPuppet = CreateObject(HZCK,0,0,GetOwner());
  SetColorDw(RGB(255,255,255),pPuppet);
  if(!Random(4)) SetGraphics("ABC",pPuppet,KSSL);
  else  SetGraphics("Knight",pPuppet,KSSL);
  SetVisibility(VIS_God());
  //Bewaffnen
  CreateContents(ENWP,pPuppet); 
  CreateContents(ENAP,pPuppet)->~Activate(pPuppet);
  return(1);
}

func Timer()
{
	if(!pPuppet) return(RemoveObject()); 
	if(!GetAlive(pPuppet)) return(RemoveObject());
	SetPosition(GetX(pPuppet),GetY(pPuppet));
	pPuppet->CheckInventory();
    pPuppet->SetAggroLevel(Aggro_Guard,100,GetX(),GetY());
	return(1);
}