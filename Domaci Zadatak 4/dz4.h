#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

typedef struct Node
{
	char* name;
	char* email;
	int num_of_tickets;
	int received_tickets;
	int member;
	struct Node *next;
}node;

void load_list(node** l);
void delete_list(node** l);
void delete_elem(node** l);
void add_node_start(node** l);
void add_node_end(node** l);
void print_list(node* l);
void process_list(node** l, int *num);

#endif // LIST_H_INCLUDED