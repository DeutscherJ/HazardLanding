/*-- Append für den Effektmanager --*/

// dient zum Einbinden der Hintergrundlandschaft

#strict
#appendto SFXM

public func SetLightness(light)
{
  // Verdunklung der Landschaft bei Nacht
  var color = RGB(128+light/2, 128+light/2, 128+light/2);
  var obj;
  while (obj = FindObject(_BGL, 0,0,0,0, 0,0,0,0, obj))
    SetClrModulation(color, obj);
  return(inherited(light));
}

private func CreateHighFX()
{
  // alte Landschaft erst loswerden
  RemoveAll(_BGL);
  // Hintergrund-Landschaft neu aufbauen
  var x;
  var xplus = GetDefWidth(_BGL);
  for (x; x < LandscapeWidth(); x += xplus)
    SetPosition(x, 280, CreateObject(_BGL,0,0,-1));
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

private func ResetBGObjects()
{
  // Hintergrundlandschaft neu aufbauen
  if (GraphicFXmode == +1)
    CreateHighFX();
  return(1);
}

