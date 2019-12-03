#include "dz5.h"
#include <stdio.h>
#include <time.h>

void delete_list(node ** l)
{
	clock_t time;
	time = clock();

	if (*l == NULL)
	{
		printf("Lista je prazna.\n");
		return;
	}
	node* t = *l;

	while (*l)
	{
		*l = t->next;
		free(t);
		t = *l;
	}

	if (*l == NULL)
		printf("Uspesno obrisano.\n");
	else
		printf("Greska pri brisanju.\n");

	time = clock() - time;
	double time_taken = ((double)time) / CLOCKS_PER_SEC * 1000;
	printf("Vreme izvrsavanja: %f\n", time_taken);
}

void change_delay(node** l)
{
	clock_t time;

	if (!*l)
	{
		printf("Lista je prazna.\n");
		return;
	}

	node* t = *l;
	float p;
	printf("Unesite procenat smanjivanja/povecanja (negativan broj je za smanjivanje):\n");
	printf("Procenat: ");

	scanf_s("%f", &p);

	time = clock();

	p /= 100;

	int pomeraj = 0;
	int prethodni_validan = 0;
	while (t)
	{
		pomeraj += (t->sub->delay - prethodni_validan) * p;

		prethodni_validan = t->sub->duration;

		t->sub->delay = t->sub->delay + pomeraj;

		t->sub->duration = t->sub->duration + pomeraj;

		t = t->next;
	}

	printf("Uspesno obradjeno.\n");

	time = clock() - time;
	double time_taken = ((double)time) / CLOCKS_PER_SEC * 1000;
	printf("Vreme izvrsavanja: %f\n", time_taken);
}