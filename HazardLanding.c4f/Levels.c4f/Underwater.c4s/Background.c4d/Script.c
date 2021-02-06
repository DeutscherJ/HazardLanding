/*-- Hintergrund-Landschaft --*/

#strict

// Anmerkung zu den Grafiken der Landschaften:
// Die eigentliche Landschaftsgrafik ist in zwei Teile eingeteilt. Der Gro�teil der Landschaft
// ist in der Graphics.png mit nur 8bit Farbtiefe gespeichert, um Speicherplatz zu sparen.
// F�r einfache Farb�berg�nge und transparente R�nder reichen 8bit nicht aus bzw. es sieht
// d�mlich aus, weshalb diese Teile der Grafik mit 32bit und Alphakanal in der Overlay.png
// gespeichert werden. Die Engine legt im Spiel beide Grafiken �bereinander, sodass wieder die
// urspr�ngliche Grafik entsteht.

protected func Initialize()
{
  // Parallaxit�t: 30%
  Local(0) = 30;
  Local(1) = 30;
  // Overlay komplett anzeigen
  SetColorDw(RGB(255,255,255));
  return(1);
}
