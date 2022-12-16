#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

// #define KÄYTÄ_JAETTUA_KIRJASTOA

#define MAX_SYÖTTEEN_PITUUS 512

#ifndef KÄYTÄ_JAETTUA_KIRJASTOA
	#include "muunnin.h"
#else

#include <dlfcn.h>

long double (*sentit_tuumiksi)(long double);
long double (*tuumat_senteiksi)(long double);

void* kahva = NULL;

// https://linux.die.net/man/3/dlsym
void lataa_jaetut_funktiot()
{
	kahva = dlopen("lib/muunnin.so", RTLD_LOCAL | RTLD_LAZY);

	if (!kahva)
	{
        	fprintf(stderr, "%s\n", dlerror());
        	exit(EXIT_FAILURE);
	}

	*(void **) (&sentit_tuumiksi) = dlsym(kahva, "sentit_tuumiksi");
	*(void **) (&tuumat_senteiksi) = dlsym(kahva, "tuumat_senteiksi");

	assert(sentit_tuumiksi != NULL);
	assert(tuumat_senteiksi != NULL);

	printf("Jaetut funktiot ladattu.\n");
}

#endif


double long käsittele_syöte(const char* syöte)
{
	const size_t syötteen_pituus = strlen(syöte);

	if (syötteen_pituus > MAX_SYÖTTEEN_PITUUS)
	{
		printf("Syöte liian pitkä! \n");
		exit(1);
	}

	char syöte2[MAX_SYÖTTEEN_PITUUS+1] = { '\0' };
	memset(syöte2, '\0', MAX_SYÖTTEEN_PITUUS + 1); // Riittääkö ylempi alustus?

	bool omaa_jo_desimaalin = false;
	bool syöte_negatiivinen = false;

	size_t ulosteen_pituus = 0;

	for (int i = 0; i < syötteen_pituus; i++)
	{
		char c = syöte[i];

		if (ulosteen_pituus == 0 && c == '-')
		{
			syöte_negatiivinen = true;
			continue;
		}

		if (c == ' ')
		{
			continue;
		}

		c = (c == ',') ? '.' : c;

		if (!isdigit(c) && (omaa_jo_desimaalin || c != '.'))
		{
			goto syötevirhe;
		}

		if (i == 0 && c == '0')
		{
			// 0.5 = ok, 00.5 != ok
			if (syötteen_pituus == 1 || (syöte[1] == '.'))
			{
				goto syötevirhe;
			}
		}
		
		if (c == '.')
		{
			assert(omaa_jo_desimaalin == false);
			omaa_jo_desimaalin = true;
		}

		syöte2[ulosteen_pituus] = (char) c;
		ulosteen_pituus++;
	}

	long double uloste = 0;
	sscanf(syöte2, "%Lf", &uloste);

	if (syöte_negatiivinen)
	{
		uloste *= -1;
	}

	return uloste;

	syötevirhe:
		printf("Viallinen syöte '%s'\n", syöte);
		exit(1);

}


int main(int argc, char **argv)
{
	#ifdef KÄYTÄ_JAETTUA_KIRJASTOA
	lataa_jaetut_funktiot();
	#endif

	char syöte[MAX_SYÖTTEEN_PITUUS+1] = { '\0' };

	if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
		{
			assert( ( strlen(syöte) + strlen(argv[i]) ) <= MAX_SYÖTTEEN_PITUUS );
			strcat(syöte, argv[i]);
		}
	}
	else
	{
		printf("Muunnettava luku? ");
		fgets(syöte, MAX_SYÖTTEEN_PITUUS, stdin);
		char* rivivaihto = strchr(syöte, '\n');
		if (rivivaihto)
		{
			rivivaihto[0] = '\0';
		}
	}

	long double syöte_käsitelty = käsittele_syöte(syöte);

	long double syöte_tuumina = sentit_tuumiksi(syöte_käsitelty);
	long double syöte_sentteinä = tuumat_senteiksi(syöte_käsitelty);

	printf("%.2Lf senttiä on %.2Lf tuumaa.\n", syöte_käsitelty, syöte_tuumina);
	printf("%.2Lf tuumaa on %.2Lf senttiä.\n", syöte_käsitelty, syöte_sentteinä);

	#ifdef KÄYTÄ_JAETTUA_KIRJASTOA
	dlclose(kahva);
	#endif

	return 0;
}
