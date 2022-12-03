#include "muunnin.h"

const long double TUUMA_SENTTEINÄ = 2.54000508001016L;

long double sentit_tuumiksi(long double sentit)
{
	return sentit * TUUMA_SENTTEINÄ;
}

long double tuumat_senteiksei(long double tuumat)
{
	return tuumat / TUUMA_SENTTEINÄ; 
}
