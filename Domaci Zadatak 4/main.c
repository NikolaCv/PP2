#include <stdio.h>
#include "dz4.h"
#include <stdlib.h>

void menu(int *opt)
{
	printf("1. Ucitavanje liste\n");
	printf("2. Brisanje liste\n");
	printf("3. Dodavanje na kraj\n");
	printf("4. Dodavanje na pocetak\n");
	printf("5. Brisanje elementa\n");
	printf("6. Ispisivanje liste\n");
	printf("7. Obrada liste\n");
	printf("0. KRAJ\n");
	scanf_s("%d", opt);
	while (*opt > 7 || *opt < 0)
	{
		printf("Unesite validan broj.\n");
		scanf_s("%d", opt);
	}
	char c = getchar();
}

int main()
{
	int opt;
	int num = 0;
	node* l = NULL;

	while (1)
	{
		menu(&opt);
		switch (opt)
		{
			case 1:
			{
				load_list(&l);
				
				break;
			}
			case 2:
			{
				delete_list(&l);
				
				break;
			}
			case 3:
			{
				add_node_end(&l);

				break;
			}
			case 4:
			{
				add_node_start(&l);

				break;
			}
			case 5:
			{
				delete_elem(&l);

				break;
			}
			case 6:
			{
				print_list(l);

				break;
			}
			case 7:
			{
				process_list(&l,&num);

				break;
			}
			case 0:
			{
				delete_list(&l);
				system("pause");
				return 0;
			}
		}
		system("pause");
		system("cls");
	}
}