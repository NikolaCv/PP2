#pragma once

typedef struct Title
{
	float delay;
	float duration;
	char* subtitles;
}title;

typedef struct Node
{
	title *sub;
	struct Node* next;
	struct Node* prev;
}node;

//void add_node(node** l);
void load_txt_from_file(node** l, char* input);
void load_sub_from_file(node** l, char* input);
void print_list(node* l);
void delete_list(node ** l);
void change_delay(node** l);
void save_to_srt(node* l, char* output);