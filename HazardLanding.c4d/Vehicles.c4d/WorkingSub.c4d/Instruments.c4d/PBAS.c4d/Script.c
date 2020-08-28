/*-- PBAS --*/

#strict

func Activate(pSub)
{
	var y;
	while(!GBackSolid(GetX(pSub),GetY(pSub)+y)) y++;
	var x= 240,h=200,ws=iWS,xa=80,kant=10;
	XSMatArea(Wall,-x,y,h,pSub);//Betonklotz
	XSMatArea("Water-Liquid",-x,y-100,100,pSub);//begradigen
	
	XSMatArea("Water-Liquid",-70,y-1,h-ws,pSub);//YGang
	XSMatArea("Water-Liquid",-x+ws,y+100,80,pSub);//XGang
	
	XSyncMatAreas(BWall,-x+ws,y+ws,Distance(0,70,0,x-ws)-ws,80,pSub);//Luft
	XSyncMatAreas(Wall,-x-xa,y+ws,xa,80+ws-kant,pSub);//kleine Räume
	XSyncMatAreas(BWall,-x-xa+ws,y+ws*2,xa,80-ws-kant,pSub);//zum Stehen
	CreateObject(FLGT,GetX(pSub),GetY(pSub)+y,GetOwner(pSub));
	CreateObject(BDBX,GetX(pSub)+100,GetY(pSub)+y+50,GetOwner(pSub))->Init(1);
	CreateObject(BDBX,GetX(pSub)-100,GetY(pSub)+y+50,GetOwner(pSub))->Init(-1);
	LocalN("iCurrentInstrument",pSub)=0;//Instrument verschwindet
	return(1);
}
