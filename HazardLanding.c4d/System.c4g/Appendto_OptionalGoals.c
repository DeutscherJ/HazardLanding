/*-- Mosterjagd und WIpfjagd können Optional eingestellt werden */

#strict
#appendto MNTK
#appendto WPHT
#appendto MONE
#appendto VALG
#appendto OREM
#appendto OILP
#appendto GLDM
#appendto ENGI

func AdditionalGoal(){return(1);}
func IsFulfilled(a,b,c)
{
	if(FindObject(CHOS)) return(0);//Solange noch regeln ausgewählt werden, wird nicht gewonnen
	return(_inherited(a,b,c));
}