#strict

static fAntiLaag;

protected func Activate(iPlr) {
  MessageWindow(GetDesc(),iPlr);
}

global func BloodAndGore() {
  return(ObjectCount(BFGR));
}

// Kann mittels des Spielzielauswählers ausgewählt werden
public func IsChooseable() { return(1); }


global func Blood(i)
{
	//CastPXS("Blood", i*3, 50);
	CastObjects(BLUT,i,20);
}

global func SplatterDead(pObj)
{
	Sound("Splatter*");
	if(fAntiLaag==2 && !this()) return(0);
	if(GBackTunnel()&&GBackTunnel(-20,0)&&GBackTunnel(-20,0)&&GBackTunnel(20,0)&&GBackTunnel(0,-20))
	{
		SetClrModulation(RGB(255,0,0),CreateObject(FLCK,0,20,-1));
	}
	if(fAntiLaag) return(0);
	var randomcnt = Random(8);
    if(randomcnt == 0) Splatter1();
    if(randomcnt == 1) Splatter2();
    if(randomcnt == 2) Splatter3();
    if(randomcnt == 3) Splatter4();
    if(randomcnt == 4) Splatter5();
    if(randomcnt == 5) Splatter6();
    if(randomcnt == 6) Splatter7();
    if(randomcnt == 7) Splatter9();
	while(Contents())
		Exit(Contents(), RandomX(-5,5), RandomX(-7,7), Random(361), RandomX(-3,3), RandomX(-3,-1), RandomX(-20,20));  

	// Blut in Massen !
	//CastPXS("Blood", 150, 50);
	if(!GetAlive(pObj)) SetClrModulation(RGB(255,0,0));
	CastObjects(BLUT,60,20);
}

global func Splatter1 () // Knochen
{
  CreateContents(PIEC, this())-> ~SetTo("Flesh");
  CreateContents(PIEC, this())-> ~SetTo("Skull");
  CreateContents(PIEC, this())-> ~SetTo("Bone");
  CreateContents(PIEC, this())-> ~SetTo("Breast");
  CreateContents(PIEC, this())-> ~SetTo("Haunch");
  CreateContents(PIEC, this())-> ~SetTo("Backbone");
}

global func Splatter2 () // Fleisch
{
  CreateContents(PIEC, this())-> ~SetTo("Flesh");
  CreateContents(PIEC, this())-> ~SetTo("Flesh");
  CreateContents(PIEC, this())-> ~SetTo("RottenFlesh");
  CreateContents(PIEC, this())-> ~SetTo("Heart");
  CreateContents(PIEC, this())-> ~SetTo("Kidneys");
  CreateContents(PIEC, this())-> ~SetTo("Foot");
}

global func Splatter3 () // Gedärme
{
  CreateContents(PIEC, this())-> ~SetTo("Brain");
  CreateContents(PIEC, this())-> ~SetTo("Heart");
  CreateContents(PIEC, this())-> ~SetTo("Kidneys");
  CreateContents(PIEC, this())-> ~SetTo("Milt");
  CreateContents(PIEC, this())-> ~SetTo("Eye");
  CreateContents(PIEC, this())-> ~SetTo("Stomach");
  CreateContents(PIEC, this())-> ~SetTo("Bowel");
}

global func Splatter4 () // Gemischt (Zerbrochene Knochen)
{
  CreateContents(PIEC, this())-> ~SetTo("BrokenSkull");
  CreateContents(PIEC, this())-> ~SetTo("Breast");
  CreateContents(PIEC, this())-> ~SetTo("Foot");
  CreateContents(PIEC, this())-> ~SetTo("Foot");
  CreateContents(PIEC, this())-> ~SetTo("Eye");
  CreateContents(PIEC, this())-> ~SetTo("Flesh");
}

global func Splatter5 () // Gemischt (Gedärme & Knochen)
{
  CreateContents(PIEC, this())-> ~SetTo("Flesh");
  CreateContents(PIEC, this())-> ~SetTo("Haunch");
  CreateContents(PIEC, this())-> ~SetTo("Backbone");
  CreateContents(PIEC, this())-> ~SetTo("Milt");
  CreateContents(PIEC, this())-> ~SetTo("Heart");
  CreateContents(PIEC, this())-> ~SetTo("Stomach");
  CreateContents(PIEC, this())-> ~SetTo("Bowel");
}

global func Splatter6 () // Gemischt (Brustkorb & Unterleibsgedärme)
{
  CreateContents(PIEC, this())-> ~SetTo("Breast");
  CreateContents(PIEC, this())-> ~SetTo("Brain");
  CreateContents(PIEC, this())-> ~SetTo("Milt");
  CreateContents(PIEC, this())-> ~SetTo("Bowel");
  CreateContents(PIEC, this())-> ~SetTo("Stomach");
  CreateContents(PIEC, this())-> ~SetTo("Eye");
}

global func Splatter7 () // Gemischt (Schädel & Gedärme)
{
  CreateContents(PIEC, this())-> ~SetTo("Skull");
  CreateContents(PIEC, this())-> ~SetTo("Heart");
  CreateContents(PIEC, this())-> ~SetTo("Kidneys");
  CreateContents(PIEC, this())-> ~SetTo("Milt");
  CreateContents(PIEC, this())-> ~SetTo("Eye");
  CreateContents(PIEC, this())-> ~SetTo("Stomach");
  CreateContents(PIEC, this())-> ~SetTo("Bowel");
}

global func Splatter8 () // Grünes Fleisch
{
  CreateContents(PIEC, this())-> ~SetTo("GreenFlesh");
  CreateContents(PIEC, this())-> ~SetTo("RottenFlesh");
  CreateContents(PIEC, this())-> ~SetTo("GreenFlesh");
  CreateContents(PIEC, this())-> ~SetTo("Milt");
  CreateContents(PIEC, this())-> ~SetTo("Eye");
  CreateContents(PIEC, this())-> ~SetTo("Eye");
}

global func Splatter9 () // Gemischt (Fleisch & Gedärme)
{
  CreateContents(PIEC, this())-> ~SetTo("Brain");
  CreateContents(PIEC, this())-> ~SetTo("Flesh");
  CreateContents(PIEC, this())-> ~SetTo("RottenFlesh");
  CreateContents(PIEC, this())-> ~SetTo("Milt");
  CreateContents(PIEC, this())-> ~SetTo("Heart");
  CreateContents(PIEC, this())-> ~SetTo("Stomach");
  CreateContents(PIEC, this())-> ~SetTo("Bowel");
}