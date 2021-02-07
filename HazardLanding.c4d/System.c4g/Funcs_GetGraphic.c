/*-- GetGraphics --*/

#strict
static const GraphicLocal = 7800;

// string szGfxName, object pObj, id idSrcDef, int iOverlay, int iOverlayMode, string szAction, int dwBlitMode, object pOvelayObject
// SetGraphics("",this(),0,1,GFXOV_MODE_Object,"",0,FindObject(HZCK))
global func SetGraphics(par1,par2,par3,par4,par5,par6,par7,par8)
{
	Local(GraphicLocal,par2)=[par1,par2,par3,par4,par5,par6,par7,par8];
	return(_inherited(par1,par2,par3,par4,par5,par6,par7,par8));
}

global func GetGraphics(pObj)
{
	var out = Local(GraphicLocal,pObj);
	if(!out)
		out = [0,0,0,0,0,0,0,0];
	if(!out[0]) out[0] = "";
	if(!out[1]) out[1] = pObj;
	if(!out[2]) out[2] = GetID(pObj);
	if(!out[3]) out[3] = 0;
	if(!out[4]) out[4] = 0;
	if(!out[5]) out[5] = "";
	if(!out[6]) out[6] = 0;
		
	return(out);
}