/*-- Append für den Effektmanager --*/

// der Sternenhimmel funktioniert hier etwas anders als normal,
// außerdem muss die Hintergrundlandschaft eingebunden werden

#strict
#appendto SFXM


/* Effekte aufbauen bzw. löschen */

private func CreateLowFX()
{
  // Sternenhimmel aufbauen
  if (!starlight) InitStars();
  return(1);
}

private func RemoveLowFX()
{
  // Sternenhimmel löschen
  if (starlight) HideStars();
  return(1);
}

private func CreateHighFX()
{
  // alte Landschaft erst loswerden
  RemoveAll(_BGL);
  // Hintergrund-Landschaft neu aufbauen
  var x;
  var xplus = GetDefWidth(_BGL);
  for (x; x < LandscapeWidth(); x += xplus)
    SetPosition(x, 200, CreateObject(_BGL,0,0,-1));
  // Helligkeit neu setzen
  var timeobj = FindObject(TIME);
  if (timeobj) ObjectCall(timeobj, "RefreshScreen");
  return(1);
}

private func RemoveHighFX()
{
  // alte Hintergrund-Landschaft löschen
  RemoveAll(_BGL);
  return(1);
}


/* Aufrufe */

public func SetLightness(light)
{
  // Verdunklung der Landschaft bei Nacht
  var color = RGB(128+light/2, 128+light/2, 128+light/2);
  var obj;
  while (obj = FindObject(_BGL, 0,0,0,0, 0,0,0,0, obj))
    SetClrModulation(color, obj);
  return(inherited(light));
}

private func ResetBGObjects()
{
  // Hintergrundlandschaft neu aufbauen
  if (GraphicFXmode == +1)
    CreateHighFX();
  return(1);
}


/* Sternenhimmel */

private func InitStars()
{
  // Sternenhimmel aufbauen
  var starsky, depth;
  var x, y, i;
  for (i; i < 2; ++i)     // zwei Schichten Sterne
    for (x = 0; x < LandscapeWidth(); x += 300)
      for (y = 0; y < LandscapeHeight(); y += 300)
      {
        starsky = CreateObject(SSKY,0,0,-1);
        SetPosition(x, y, starsky);
        depth = y*255 / LandscapeHeight();
        SetClrModulation(RGBa(255-depth/2, 255-depth/2, 255, 64+depth*3/5), starsky);
      }
  starlight = 1;
  return(1);
}

private func HideStars()
{
  RemoveAll(SSKY);
  starlight = 0;
  return(1);
}

