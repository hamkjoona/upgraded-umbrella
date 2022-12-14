#ifndef MUUNNIN_H
#define MUUNNIN_H

#include "muunnin.h"

const long double TUUMA_SENTTEINÄ = 2.54000508001016L;


long double sentit_tuumiksi(const long double sentit)
{
	return sentit * TUUMA_SENTTEINÄ;
}

long double tuumat_senteiksi(const long double tuumat)
{
	return tuumat / TUUMA_SENTTEINÄ;
}

#endif
