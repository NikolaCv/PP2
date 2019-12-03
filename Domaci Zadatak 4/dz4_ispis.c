#include "dz4.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_list(node* l)
{
	if (!l)
	{
		printf("Lista je prazna.\n");
		return;
	}

	while (l)
	{
		printf("Name: ");
		for (int i = 0; l->name[i] != '\0'; ++i)
			printf("%c", l->name[i]);
		printf("\n");
		printf("Email: ");
		for (int i = 0; l->email[i] != '\0'; ++i)
			printf("%c", l->email[i]);
		printf("\n");
		printf("Num of tickets: %d\n", l->num_of_tickets);
		if (l->member)
			printf("Member: True\n");
		else
			printf("Member: False\n");
		printf("Bought: %d tickets\n", l->received_tickets);
		l = l->next;
		printf("\n");
	}
	printf("\n");
}
