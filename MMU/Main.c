#include <stdio.h>
#include <stdlib.h>

#include "MemManagement.c"
#include "MemManagement.h"
#include "LinkedList.c"

int main(void)
{
    MemoryBlock memory[MEMORY_SIZE];
    init_memory(memory, MEMORY_SIZE);

    int choice;

    do
    {
        printf("Choose a data structure:\n");
        printf("1. Linked List\n");
        printf("2. Hash Map\n");
        printf("3. Binary Tree\n");
        printf("Enter your choide (1, 2, or 3): ");

        scanf("%d", &choice);

        handle_data_structure(choice, memory);

        printf("Do you want to choose another data structure? (1 for Yes, 0 for No): ");
        scanf("%d", &choice);

    } while (choice == 1);

    compact_memory(memory); // Compact memory

    return 0;
}

/**
 * Handle data structure choices based on the user input.
 */
void handle_data_structure(int choice, MemoryBlock *memory)
{
    int head_address; // Declare the variable here

    switch (choice)
    {
    case 1:
        handle_linked_list(memory);
        break;

    case 2:
        // Handle hash map
        printf("Hash Map is not implemented yet.\n");
        break;

    case 3:
        // Handle binary tree
        printf("Binary Tree is not implemented yet.\n");
        break;

    default:
        printf("Invalid choice.\n");
        break;
    }
}

/**
 * Peform Link list operations using Operating System Memory Management algorithm.
 */
void handle_linked_list(MemoryBlock *memory)
{
    int head_address = allocate_memory(memory, SIZE);

    if (head_address != -1)
    {
        printf("Memory allocation for head node at address: %d\n", head_address);

        // Create a pointer to the head node and initialize it
        Node *head = create_node(0); // Initialize head with dummy data (0)
        head->next = NULL;

        // Allocate memory for additional nodes of the linked list
        int node1_address = allocate_memory(memory, SIZE);
        int node2_address = allocate_memory(memory, SIZE);

        if (node1_address != -1 && node2_address != -1)
        {
            printf("Memory allocation for additional nodes successful.\n");

            // Access the additional nodes and initialize them
            Node *node1 = create_node(20);
            Node *node2 = create_node(30);

            // Link the nodes together
            head->next = node1;
            node1->next = node2;

            // Print the linked list
            print_list(head);

            // Deallocate memory for the head node (the entire linked list will be deallocated as a result)
            deallocate_memory(memory, head_address);
        }
        else
        {
            printf("Failed to allocate memory for additional nodes.\n");
        }
    }
    else
    {
        printf("Failed to allocate memory for the head node.\n");
    }
}