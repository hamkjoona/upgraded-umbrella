#include <stdio.h>
#include "muunnin.h"


int main()
{
	long double syöte_sentteinä;
	printf("Montako senttiä muutetaan tuumiksi? ");
	scanf("%Lf", &syöte_sentteinä);

	if (!syöte_sentteinä)
	{
		printf("Viallinen syöte.\n");
		return 1;
	}

	long double syöte_tuumina = sentit_tuumiksi(syöte_sentteinä);

	printf("%.2Lf senttiä on %.2Lf tuumaa.\n", syöte_sentteinä, syöte_tuumina);

	return 0;
}
