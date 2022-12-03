#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#include "muunnin.h"

#define MAX_SYÖTTEEN_PITUUS 512
//#define SCANF_SYÖTETYYPPI "%"  MAX_SYÖTTEEN_PITUUS  "s"
#define SCANF_SYÖTETYYPPI "%512s"

double long käsittele_syöte(char* syöte)
{
	const int pituus = strlen(syöte);

	if (pituus > MAX_SYÖTTEEN_PITUUS)
	{
		printf("Syöte liian pitkä! \n");
		exit(1);
	}

	char syöte2[MAX_SYÖTTEEN_PITUUS+1] = {};

	bool omaa_jo_desimaalin = false;
	bool syöte_negatiivinen = false;

	for (int i = 0; i < pituus; i++)
	{
		char c = (char) syöte[i];

		if (i == 0 && c == '-')
		{
			syöte_negatiivinen = true;
			continue;
		}

		if (!isdigit(c) && (omaa_jo_desimaalin || (c != ',' && c != '.')))
		{
			goto syötevirhe;
		}

		if (i == 0 && c == '0')
		{
			// 0,5 = ok
			if (pituus == 1 || (syöte[1] == ',' && syöte[1] == '.'))
			{
				goto syötevirhe;
			}
		}
		
		if (c == ',')
		{
			c = '.';
		}

		if (c == '.')
		{
			assert(omaa_jo_desimaalin == false);
			omaa_jo_desimaalin = true;
		}

		syöte2[i] = (char) c;
	}

	long double ulos = 0;
	sscanf(syöte2, "%Lf", &ulos);

	if (syöte_negatiivinen)
	{
		ulos = -1;
	}

	return ulos;

	syötevirhe:
		printf("Viallinen syöte '%s'\n", syöte);
		exit(1);
}


int main(int argc, char **argv)
{
	// Sama tehtävissä ilman malloc:ia missään vaiheessa ohjelmaa?
	char** syöte = malloc(sizeof(void*));

	if (argc > 1)
	{
		*syöte = argv[1];
	} else {
		printf("Muunnettava luku? ");
		char tmp[MAX_SYÖTTEEN_PITUUS+1];
		scanf(SCANF_SYÖTETYYPPI, tmp);
		*syöte = tmp;
		//*syöte = malloc(512);
		//scanf(SCANF_SYÖTETYYPPI, *syöte);

	}

	long double syöte_käsitelty = käsittele_syöte(*syöte);

	long double syöte_tuumina = sentit_tuumiksi(syöte_käsitelty);
	long double syöte_sentteinä = tuumat_senteiksi(syöte_käsitelty);

	printf("%.2Lf senttiä on %.2Lf tuumaa.\n", syöte_käsitelty, syöte_tuumina);
	printf("%.2Lf tuumaa on %.2Lf senttiä.\n", syöte_käsitelty, syöte_sentteinä);

	free(syöte);

	return 0;
}
