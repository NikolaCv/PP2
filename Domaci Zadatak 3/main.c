#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
kako_si mi_ti
sta_____radis
nista_123123
traallalal
________
jos_jedan_string

kakoSi miTi
staRadis
nista123123
traallalal
josJedanString

*/

char** scan_strings(int *t)
{
	char end[] = "dosta Bruce Li\0";
	char** s = NULL;
	char c;
	//i is number of strings, n is length of string
	int i = 0, n;
	int curr_len_n = 0, curr_len_i = 0;

	while ((c = getchar()) != '\n')
	{
		n = 0;
		curr_len_n = 1;

		//if we need more memory, we'll multiply it by 2
		if (i + 1 > curr_len_i)
		{
			//+1 because curr_len_i is 0 at the start
			curr_len_i = 2 * curr_len_i + 1;
			s = (char**)realloc(s, curr_len_i * sizeof(char*));

			if (!s)
				return NULL;
		}
		
		s[i] = malloc(sizeof(char));
		if (!s[i])
			return NULL;
		s[i][n++] = c;

		while ((c = getchar()) != '\n')
		{
			//if we need more memory, we'll multiply it by 2
			if (n + 1 > curr_len_n)
			{
				curr_len_n *= 2;
				s[i] = (char*)realloc(s[i], curr_len_n* sizeof(char));

				if (!s[i])
					return NULL;
			}
			
			s[i][n++] = c;
		}
		
		//shrink memory to fit the string (+1 for '\0')
		s[i] = (char*)realloc(s[i], (n + 1) * sizeof(char));
		if (!s[i])
			return NULL;
		s[i][n] = '\0';
		
		if (!strcmp(s[i], end))
		{
			*t = 1;
			return NULL;
		}

		++i;
	}

	//shrink memory to fit data (+1 for NULL)
	if (i > 0)
	{
		s = (char**)realloc(s, (i + 1) * sizeof(char*));
		if (!s)
			return NULL;
		s[i] = NULL;
	}

	return s;
}

void print_strings(char** s)
{
	for (int i = 0; s[i]; ++i)
	{
		for (int j = 0; s[i][j] != '\0'; ++j)
			printf("%c", s[i][j]);
		printf("\n");
	}
}

char** modify_strings(char** s)
{
	int t = 0;
	int i;

	for (i = 0; s[i]; )
	{
		t = 0;
		int j, l;
		for (j = 0, l = 0; s[i][j] != '\0'; )
		{
			//if current char is '_' we won't increase l, only j
			if (s[i][j] == '_')
			{
				t = 1;
				j++;
			}
			else
			{
				//if current char is not '_' we check if the one before was
				//if the one before was, we check if current char is lower letter
				//if it is we change it to upper and copy it on l, increasing both l and j
				if (t && islower(s[i][j]))
				{
					t = 0;
					s[i][l++] = s[i][j++] - 'a' + 'A';
				}
				else
				//if it's not, we just copy from j to l
					s[i][l++] = s[i][j++]; 
			}
		}
		
		//shrinking to fit data
		if (l > 0)
		{
			s[i] = (char*)realloc(s[i], (l + 1) * sizeof(char));
			if (!s)
				return NULL;
			s[i][l] = '\0';
			i++;
		}
		//deleting current string since l == 0
		else
		{
			int k;
			char* r = s[i];
			for (k = i + 1; s[k]; ++k)
				s[k - 1] = s[k];
			free(r);
			s[k - 1] = NULL;
			s = (char**)realloc(s, k * sizeof(char*));
		}
	}

	return s;
}

int main()
{
	char** s;
	int t = 0;

	while (1)
	{
		s = scan_strings(&t);
		if (t)
		{
			system("pause");
			return 0;
		}
		if (!s)
		{
			printf("Neuspesna alokacija!\n");
			system("pause");
			system("cls");
			continue;
		}

		printf("Strings:\n");
		print_strings(s);

		modify_strings(s);

		if (!s)
		{
			printf("Neuspesna alokacija!\n");
			system("pause");
			system("cls");
			continue;
		}
		else
		{
			putchar('\n');
			printf("Modified strings:\n");
		}
		
		print_strings(s);

		int i;
		for (i = 0; s[i]; ++i)
			free(s[i]);
		free(s[i]);
		free(s);

		system("pause");
		system("cls");
	}
}