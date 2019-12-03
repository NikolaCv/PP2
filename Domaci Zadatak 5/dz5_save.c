#include "dz5.h"
#include <stdio.h>
#include <math.h>
#include <time.h>

//XXX time.h ??? popravi ispis majke ti
void add_time(float length, int* hours, int* minutes, float* seconds)
{
	//podeljeno sa fps
	*seconds = length / 25;
	/*printf("len: %f\n", length);
	printf("sec: %f\n", *seconds);
	system("pause");*/
	if (*seconds > 60)
	{
		*minutes = *seconds / 60;
		*seconds = *seconds - floor(*seconds / 60) * 60;
	}
	if (*minutes > 60)
	{
		*hours = *minutes / 60;
		*minutes = *minutes % 60;
	}
}

void print_formated(int p, FILE* output)
{
	if (p < 10)
		fprintf(output, "0%d", p);
	else
		fprintf(output, "%d", p);
}

void print_formated1(float p, FILE* output)
{
//	printf("p: %f\n", p);
	int a = round(p*1000);
//	printf("p: %f\n", p);
	if (a < 10)
		fprintf(output, "00%d", a);
	else
		if(a < 100)
			fprintf(output, "0%d", a);
		else
			fprintf(output, "%d", a);
}

void save_to_srt(node* l, char* output)
{
	clock_t time;
	time = clock();

	FILE* output_file;
	fopen_s(&output_file, output, "w+");

	if (!output_file)
	{
		printf("Greska pri otvaranju fajla.\n");
		return;
	}
	//00:00 : 15, 000 -- > 00:00 : 18, 000
	float seconds = 0;
	int hours = 0, minutes = 0;
	int i = 1;

	while (l)
	{
		fprintf(output_file, "%d\n", i++);
		add_time(l->sub->delay, &hours, &minutes, &seconds);

		print_formated(hours, output_file);
		fprintf(output_file, ":");
		print_formated(minutes, output_file);
		fprintf(output_file, ":");
		print_formated(seconds, output_file);
		fprintf(output_file, ",");
		print_formated1(seconds - floor(seconds), output_file);

		fprintf(output_file, " --> ");

		add_time(l->sub->duration, &hours, &minutes, &seconds);
		print_formated(hours, output_file);
		fprintf(output_file, ":");
		print_formated(minutes, output_file);
		fprintf(output_file, ":");
		print_formated(seconds, output_file);
		fprintf(output_file, ",");
		print_formated1(seconds - floor(seconds), output_file);
		
		
		for (int i = 0; l->sub->subtitles[i] != '\0'; ++i)
		{
			//printf("%d\n", i);
			if (l->sub->subtitles[i] == '|')
				l->sub->subtitles[i] = '\n';
		}
			

		fprintf(output_file, "\n%s\n\n", l->sub->subtitles);

		l = l->next;
	}

	fclose(output_file);

	printf("Uspesno sacuvano.\n");

	time = clock() - time;
	double time_taken = ((double)time) / CLOCKS_PER_SEC * 1000;
	printf("Vreme izvrsavanja: %f\n", time_taken);
}