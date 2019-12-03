#include "dz4.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void delete_list(node ** l)
{
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
}

void delete_elem(node ** l)
{
	if (*l == NULL)
	{
		printf("Lista je prazna.\n");
		return;
	}
	char* str = scan_str();
	if (str == NULL)
	{
		printf("Uneto ime je prazno.\n");
		return;
	}

	//p je prethodni, t je trenutni
	node* t = *l;
	node* p = NULL;
	while (t)
	{
		char* c = t->name;
		if (!strcmp(c, str))
		{
			//ako ne brisemo prvog
			if (p != NULL)
			{
				p->next = t->next;
				free(t);
				break;
			}
			//ako brisemo prvog clana
			else
			{
				*l = t->next;
				free(t);
				break;
			}
		}
		p = t;
		t = t->next;
	}

	if (*l != NULL)
		printf("Uspesno brisanje, lista nije prazna.\n");
	else
		printf("Uspesno brisanje, lista je prazna.\n");

}

void process_list(node ** l, int *num)
{
	int n;
	printf("Unesite broj karata: ");
	//ako je ostalo neraspodeljenih karata od proslog puta
	//zato dodajemo n na num
	scanf_s("%d", &n);
	*num += n;

	node* t = *l;
	while (t)
	{
		if (t->member)
		{
			t->received_tickets++;
			(*num)--;
		}
		//ako nema vise karata
		if (*num < 1)
			break;
		t = t->next;
	}

	t = *l;
	while (t)
	{
		//ako je potraznja veca od zaliha
		if (t->num_of_tickets - t->received_tickets >= *num)
		{
			t->received_tickets += *num;
			*num = 0;
			break;
		}
		else
		{
			*num -= t->num_of_tickets - t->received_tickets;
			t->received_tickets = t->num_of_tickets;
		}
		t = t->next;
	}

	if (*num)
		printf("Ima viska karata (%d).\n", *num);
	else
		printf("Sve karte su rasprodate.\n");
}
