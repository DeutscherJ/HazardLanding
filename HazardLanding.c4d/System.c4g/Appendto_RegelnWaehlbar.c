/*-- Neues Script --*/

#strict

#appendto IGIB //Insta GIB
#appendto CHOS //Spielregelwahl
#appendto NODR //Arena
#appendto NOCA //Kein Camping
#appendto WPST //Waffen bleiben
/*
#appendto THBA //Gemeinschaftsmaterial
#appendto TKNW //Gemeinschaftsbaupl�ne
#appendto TACC//Gemeinschaftskonto
#appendto RSNB//Schneeball
#appendto RVLR//Rivalit�t
#appendto REAC//Clonk Entlassen
#appendto NMTT//Kein Metall vor Geb�uden
#appendto LSBS//Verlust der Basis
#appendto KILC//Verlust Captain
FGRVFlagge abnehmbar
ENRG//Energiebedarf
//Geb�ude schneien ein
//Baumaterial
//Einsammelbare Tiere
//Verlust Flagge
func Initialize() {
  
  return(1);
}*/
func Unchoosable(){return(IsOpenScenario());}