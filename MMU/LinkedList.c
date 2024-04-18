#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"

/**
 * Create a new node with the given data.
 */
Node *create_node(int data)
{
    Node *new_node = (Node *)malloc(sizeof(Node));

    if (new_node != NULL)
    {
        new_node->data = data;
        new_node->next = NULL;
    }

    return new_node;
}

/**
 * Append a new node with the given data to the end of the list.
 */
void append_node(Node **head_ref, int data)
{
    Node *new_node = create_node(data);

    if (new_node == NULL)
    {
        fprintf(stderr, "Failed to create a new node.\n");
        exit(EXIT_FAILURE);
    }

    if (*head_ref == NULL)
    {
        *head_ref = new_node;
    }
    else
    {
        Node *current = *head_ref;

        while (current->next != NULL)
        {
            current = current->next;
        }

        current->next = new_node;
    }
}

/**
 * Print the elements of the list
 */
void print_list(Node *head)
{
    printf("Linked List: ");

    while (head != NULL)
    {
        printf("%d -> ", head->data);
        head = head->next;
    }

    printf("NULL\n");
}

/**
 * Free the memory allocated for the list
 */
void free_list(Node *head)
{
    Node *current = head;

    while (current != NULL)
    {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

/**
 * Get the head node of the list
 */
Node *get_head(Node *head)
{
    return head;
}

/**
 * Get the tail node of the list
 */
Node *get_tail(Node *head)
{
    if (head == NULL)
    {
        return NULL;
    }

    while (head->next != NULL)
    {
        head = head->next;
    }

    return head;
}

/**
 * Destory the entire list.
 */
void destroy_list(Node **head_ref)
{
    Node *current = *head_ref;
    Node *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    // Set the head ptr to NULL to indicate that the list is empty.
    *head_ref = NULL;
}

/**
 * Count the number of nodes in the list.
 */
int count_nodes(Node *head)
{
    int count = 0;

    while (head != NULL)
    {
        count++;
        head = head->next;
    }

    return count;
}

/**
 * Inserts at the beginning of the list.
 */
void insert_at_beginning(Node **head_ref, int data)
{
    Node *new_node = create_node(data);

    if (new_node == NULL)
    {
        fprintf(stderr, "Failed to create a new node.\n");
        exit(EXIT_FAILURE);
    }

    new_node->next = *head_ref;
    *head_ref = new_node;
}

/**
 * Inserts at any given position of the list.
 */
void insert_at_position(Node **head_ref, int data, int position)
{
    if (position < 0)
    {
        fprintf(stderr, "Invalid position.\n");
        return;
    }
    else if (position == 0)
    {
        insert_at_beginning(head_ref, data);
        return;
    }

    Node *new_node = create_node(data);

    if (new_node == NULL)
    {
        fprintf(stderr, "Failed to creata  new node.\n");
        exit(EXIT_FAILURE);
    }

    Node *current = *head_ref;
    int count = 0;

    while (current != NULL && count < position - 1)
    {
        current = current->next;
        count++;
    }

    if (current == NULL)
    {
        fprintf(stderr, "Position out of bounds.\n");
        return;
    }

    new_node->next = current->next;
    current->next = new_node;
}

/**
 * Deletes a node at the beginning of the list.
 */
void delete_at_beginning(Node **head_ref)
{
    if (*head_ref == NULL)
    {
        fprintf(stderr, "List is empty.\n");
        return;
    }

    Node *temp = *head_ref;
    *head_ref = (*head_ref)->next;
    free(temp);
}

/**
 * Deletes a node at the end of the list.
 */
void delete_at_end(Node **head_ref)
{
    if (*head_ref == NULL)
    {
        fprintf(stderr, "List is empty.\n");
        return;
    }

    if ((*head_ref)->next == NULL)
    {
        free(*head_ref);
        *head_ref = NULL;
        return;
    }

    Node *current = *head_ref;

    while (current->next->next != NULL)
    {
        current = current->next;
    }

    free(current->next);
    current->next = NULL;
}