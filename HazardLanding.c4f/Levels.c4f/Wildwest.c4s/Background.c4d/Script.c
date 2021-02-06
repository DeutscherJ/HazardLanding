/*-- Hintergrund-Landschaft --*/

#strict

// Anmerkung zu den Grafiken der Landschaften:
// Die eigentliche Landschaftsgrafik ist in zwei Teile eingeteilt. Der Großteil der Landschaft
// ist in der Graphics.png mit nur 8bit Farbtiefe gespeichert, um Speicherplatz zu sparen.
// Für einfache Farbübergänge und transparente Ränder reichen 8bit nicht aus bzw. es sieht
// dämlich aus, weshalb diese Teile der Grafik mit 32bit und Alphakanal in der Overlay.png
// gespeichert werden. Die Engine legt im Spiel beide Grafiken übereinander, sodass wieder die
// ursprüngliche Grafik entsteht.

protected func Initialize()
{
  // Parallaxität: 30%
  Local(0) = 30;
  Local(1) = 30;
  // Overlay komplett anzeigen
  SetColorDw(RGB(255,255,255));
  return(1);
}
