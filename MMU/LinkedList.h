#ifndef LINKED_LIST_H
#define LINKED_LIST_H

// Node structure for the list
typedef struct Node
{
    int data;
    struct Node *next;

} Node;

// Function Prototypes:
Node *create_node(int data);
void append_node(Node **head_ref, int data);
void print_list(Node *head);
void free_list(Node *head);
Node *get_head(Node *head); // wink wink
Node *get_tail(Node *head);
void destroy_list(Node **head_ref);
int count_nodes(Node *head);
void insert_at_beginning(Node **head_ref, int data);
void insert_at_position(Node **head_ref, int data, int position);
void delete_at_beginning(Node **head_ref);
void delete_at_end(Node **head_ref);

#endif