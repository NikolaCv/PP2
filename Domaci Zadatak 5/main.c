#include <stdio.h>
#include <stdlib.h>
#include "dz5.h"
#include <time.h>

void menu(int *opt)
{
	printf("1. Ucitavanje titlova iz fajla\n");
	printf("2. Brisanje liste\n");
	printf("3. Obrada ucitanih titlova\n");
	printf("4. Napravi .SRT fajl\n");
	printf("5. Ispisivanje liste\n");
	printf("0. KRAJ\n");
	scanf_s("%d", opt);
	while (*opt > 7 || *opt < 0)
	{
		printf("Unesite validan broj.\n");
		scanf_s("%d", opt);
	}
	char c = getchar();
}

int main(int argc, char** argv)
{
	node* l = NULL;
	int opt;

	time_t rawtime;
	struct tm* time_date;

	time(&rawtime);
	time_date = localtime(&rawtime);
	printf("Vreme: %s", asctime(time_date));

	while (1)
	{
		menu(&opt);
		switch (opt)
		{
		case 1:
		{
			load_txt_from_file(&l, argv[1]);

			break;
		}
		case 2:
		{
			delete_list(&l);

			break;
		}
		case 3:
		{
			change_delay(&l);

			break;
		}
		case 4:
		{
			save_to_srt(l, argv[2]);

			break;
		}
		case 5:
		{
			print_list(l);

			break;
		}
		case 0:
		{
			delete_list(&l);

			time(&rawtime);
			time_date = localtime(&rawtime);
			printf("Current local time and date: %s", asctime(time_date));

			system("pause");
			return 0;
		}
		}
		system("pause");
		system("cls");
	}
}