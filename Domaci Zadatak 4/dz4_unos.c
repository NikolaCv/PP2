#include "dz4.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* scan_str()
{
	char c = '\0';
	char* str = NULL;
	int n = 0, i = 0;
	while ((c = getchar()) != '\n')
	{
		//ako nema mesta prosirimo za duplo
		if (i + 1 > n)
		{
			n = n * 2 + 1;
			str = (char*)realloc(str, n);
		}
		str[i++] = c;
	}

	if (i == 0)
		return NULL;
	//shrink to fit data
	str = (char*)realloc(str, i + 1);
	str[i] = '\0';
	return str;
}

node* scan_node()
{
	node* t = malloc(sizeof(node));

	t->name = scan_str();
	if (t->name == NULL)
		return NULL;
	t->email = scan_str();

	scanf_s("%d", &t->num_of_tickets);
	scanf_s("%d", &t->member);

	//c = '\n'
	char c = getchar();
	t->received_tickets = 0;
	t->next = NULL;

	return t;
}

void load_list(node ** l)
{
	if (*l != NULL)
	{
		printf("Lista je vec ucitana, mozete samo dodavati na kraj ili pocetak.\n");
		return;
	}

	//ucitamo prvi
	node* t = scan_node();
	*l = t;
	node* p = *l;

	//dok ne unesemo '\n' za ime (t tada postaje null u scan_node())
	while (t)
	{
		t = scan_node();
		p->next = t;
		p = t;
	}

	if (*l != NULL)
		printf("Uspesno dodavanje.\n");
	else
		printf("Lista je i dalje prazna.\n");
}

void add_node_start(node ** l)
{
	node* t = scan_node();

	if (*l == NULL)
		*l = t;
	else
	{
		t->next = *l;
		*l = t;
	}

	if (l != NULL)
		printf("Uspesno dodavanje.\n");
	else
		printf("Neuspesno dodavanje. Lista je prazna.\n");

}

void add_node_end(node ** l)
{
	node* t = scan_node();

	if (*l == NULL)
		*l = t;
	else
	{
		node *p = *l;
		while (p->next)
			p = p->next;
		p->next = t;
	}

	if (l != NULL)
		printf("Uspesno dodavanje.\n");
	else
		printf("Neuspesno dodavanje. Lista je prazna.\n");

}
