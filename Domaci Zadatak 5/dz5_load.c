#include <stdio.h>
#include <stdlib.h>
#include "dz5.h"
#include <math.h>
#include <time.h>

int scan_str(FILE* input, char** str)
{
	char c = '\0';
	int n = 0, i = 0;
	while ((c = fgetc(input)) != '\n')
	{
		if (c == EOF)
			return -1;
		//ako nema mesta prosirimo za duplo
		if (i + 1 > n)
		{
			n = n * 2 + 1;
			*str = (char*)realloc(*str, n);
		}
		(*str)[i++] = c;
	}
	//shrink to fit data
	*str = (char*)realloc(*str, i + 1);
	(*str)[i] = '\0';

	if (i == 0)
		return 1;

	return 0;
}

int str_to_int(char *s)
{
	int n = 0;
	int exp = 1;
	for (int i = strlen(s) - 1; i >= 0; --i)
	{
		n += (s[i] - '0') * exp;
		exp = exp * 10;
	}
	
	return n;
}

float to_time(char* str)
{
	int i;
	for (i = 0; str[i] != '}'; ++i)
		str[i] = str[i + 1];
	str[i - 1] = '\0';
	
	return str_to_int(str);
}

void edit_str(char **s)
{
	if ((*s)[0] == '{')
	{
		int i = 1;
		while ((*s)[i] != '}')
			i++;

		i++;

		int j = 0;

		for (j = 0; (*s)[i] != '\0'; )
		{
			(*s)[j++] = (*s)[i++];
		}
		(*s)[j++] = '\0';
		*s = (char*)realloc(*s, j + 1);
	}
}

int scan_time(FILE* input, char** str)
{
	char c = '\0';
	int n = 0, i = 0;

	//za '{'
	c = fgetc(input);
	if (c == EOF)
		return -1;

	*str = (char*)realloc(*str, ++n);
	(*str)[i++] = c;

	while ((c = fgetc(input)) != '}')
	{
		if (c == EOF)
			return -1;
		//ako nema mesta prosirimo za duplo
		if (i + 1 > n)
		{
			n = n * 2;
			*str = (char*)realloc(*str, n);
		}
		(*str)[i++] = c;
	}
	//shrink to fit data
	(*str)[i++] = c;
	//*str = (char*)realloc(*str, i + 1);
	(*str)[i] = '\0';

	if (i == 0)
		return 1;

	return 0;
}
/*
node* scan_node_sub(FILE* input_file, int* b)
{
	float del, dur;
	node* t = malloc(sizeof(node));
	char *sub1 = NULL, *sub2 = NULL;

	fscanf_s(input_file, "%f %f\n", &del, &dur);
	t->sub = malloc(sizeof(title_sub));
	t->sub->delay = del;
	t->sub->duration = dur;

	scan_str(input_file, &sub1);
	if (scan_str(input_file, &sub2) == -1)	//EOF je -1
		*b = 1;

	//ako nije EOF spojimo sub1 i sub2 (2 reda)
	if (!*b)
	{
		sub1 = (char*)realloc(sub1, strlen(sub1) + strlen(sub2) + 1);
		strcat(sub1, "\n");
		strcat(sub1, sub2);
	}

	t->sub->subtitles = sub1;

	return t;
}
*/
node* scan_node_txt(FILE* input_file, int* b, float *last_time)
{
	node* t = malloc(sizeof(node));
	char *sub1 = NULL;
	char *time1 = NULL, *time2 = NULL;
	int last_time1 = *last_time;
	if (scan_time(input_file, &time1) != -1)
	{
		scan_time(input_file, &time2);
		t->sub = malloc(sizeof(title));

		float t1 = to_time(time1);
		float t2 = to_time(time2);

		*last_time = t2;

		t->sub->delay = t1;
		t->sub->duration = t2;
		

		if (scan_str(input_file, &sub1) != -1)
		{
			edit_str(&sub1);

			t->sub->subtitles = sub1;
		}
		else
			*b = 1;
		
	}
	else
		*b = 1;

	return t;
}
/*
void load_sub_from_file(node** l, char *input)
{
	if (*l)
	{
		printf("Fajl je vec ucitan.\n");
		return;
	}
	
	FILE *input_file;
	fopen_s(&input_file, input, "r+");

	if (!input_file)
	{
		printf("Greska pri ucitavanju fajla.\n");
		return;
	}

	int b = 0;

	//prvo ucitavanje
	node *t = scan_node_sub(input_file,&b);
	if (b)
		return;

	t->next = NULL;
	t->prev = NULL;
	*l = t;
	node *p = *l;

	//ostala ucitavanja
	while (1)
	{
		t = scan_node_sub(input_file, &b);
		
		t->next = NULL;
		p->next = t;
		t->prev = p;
		p = t;

		if (b)
			break;
	}

	fclose(input_file);

	printf("Uspesno ucitano.\n");
}
*/
void load_txt_from_file(node** l, char* input)
{
	clock_t time;
	time = clock();

	
	if (*l)
	{
		printf("Fajl je vec ucitan.\n");
		return;
	}

	FILE *input_file;
	fopen_s(&input_file, input, "r+");

	if (!input_file)
	{
		printf("Greska pri ucitavanju fajla.\n");
		return;
	}

	int b = 0;

	//prvo ucitavanje
	float last_time = 0;
	node *t = scan_node_txt(input_file, &b,&last_time);

	if (b)
		return;

	t->next = NULL;
	t->prev = NULL;
	*l = t;
	node *p = *l;

	//ostala ucitavanja
	while (1)
	{
		t = scan_node_txt(input_file, &b, &last_time);

		if (b)
			break;

		t->next = NULL;
		p->next = t;
		t->prev = p;
		p = t;
	}

	fclose(input_file);

	printf("Uspesno ucitano.\n");

	time = clock() - time;
	double time_taken = ((double)time) / CLOCKS_PER_SEC * 1000;

	printf("Vreme izvrsavanja: %f\n", time_taken);
}

void print_list(node* l)
{
	clock_t time;
	time = clock();

	if (!l)
	{
		printf("Lista je prazna.\n");
		return;
	}

	//float time = 0;

	while (l)
	{
		printf("{%.0f}{%.0f}", l->sub->delay, l->sub->duration);
		printf("%s", l->sub->subtitles);

		printf("\n");
		//time += l->sub->delay * 25 + l->sub->duration * 25;
		l = l->next;
	}
	printf("\n");

	time = clock() - time;
	double time_taken = ((double)time) / CLOCKS_PER_SEC * 1000;
	printf("Vreme izvrsavanja: %f\n", time_taken);
}
