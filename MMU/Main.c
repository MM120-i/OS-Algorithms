#include <stdio.h>
#include <stdlib.h>

#include "MemManagement.c"
#include "MemManagement.h"
#include "../DataStructures/LinkedList.c"

int main(void)
{
    MemoryBlock memory[MEMORY_SIZE];
    init_memory(memory, MEMORY_SIZE);

    int choice;

    do
    {
        system("cls");

        printf("Choose a data structure:\n");
        printf("1. Linked List\n");
        printf("2. Hash Map\n");
        printf("3. Binary Tree\n");
        printf("4. Quit\n");
        printf("Enter your choide (1, 2, 3 or 4): ");

        scanf("%d", &choice);

        if (choice == 4)
        {
            exit(1);
        }

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
    int head_address;

    switch (choice)
    {
    case 1:
        handleAlgorithm(memory);
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
 * Handle user choice of Operating System algorithms.
 */
void handleAlgorithm(MemoryBlock *memory)
{
    int algorithm_choice;

    system("cls");

    printf("Choose a memory management algorithm:\n");
    printf("1. First-Fit\n");
    printf("2. Best-Fit\n");
    printf("3. Worst-fit\n");
    printf("4. Next-Fit\n");
    printf("Enter your choice (1, 2, 3, or 4): ");

    scanf("%d", &algorithm_choice);

    switch (algorithm_choice)
    {
    case 1:
        printf("Using the First-Fit algorithm.\n");
        firstFit(memory);
        break;

    case 2:
        printf("Using the Best-Fit algorithm.\n");
        bestFit(memory);
        break;

    case 3:
        printf("Using the Worst-Fit algorithm.\n");
        worstFit(memory);
        break;

    case 4:
        printf("Using the Next-Fit algorithm.\n");
        nextFit(memory);
        break;

    default:
        printf("Invalid choice.\n");
        break;
    }
}

/**
 * Perform data structure operations using the First-Fit algorithm.
 */
void firstFit(MemoryBlock *memory)
{
    int head_address = firstFitAllocate(memory, SIZE);

    if (head_address != -1)
    {
        printf("Memory allocation for head node at address: %d\n", head_address);

        // Create a pointer to the head node and initialize it
        Node *head = create_node(0);
        head->next = NULL;

        // Allocate memory for additional nodes of the data structure
        int node1_address = firstFitAllocate(memory, SIZE);
        int node2_address = firstFitAllocate(memory, SIZE);

        if (node1_address != -1 && node2_address != -1)
        {
            printf("Memory allocation for additional nodes successful.\n");

            // Access the additional nodes and initialize them
            Node *node1 = create_node(20);
            Node *node2 = create_node(30);
            Node *node3 = create_node(40);
            Node *node4 = create_node(50);
            Node *node5 = create_node(60);
            Node *node6 = create_node(70);

            // Link the nodes together
            head->next = node1;
            node1->next = node2;
            node2->next = node3;
            node3->next = node4;
            node4->next = node5;
            node5->next = node6;

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

/**
 * Perform data structure operations using the Best-Fit algorithm.
 */
void bestFit(MemoryBlock *memory)
{
    int head_address = bestFitAllocate(memory, SIZE);

    if (head_address != -1)
    {
        printf("Memory allocation for head node at address: %d\n", head_address);

        // Create a pointer to the head node and initialize it
        Node *head = create_node(0);
        head->next = NULL;

        // Allocate memory for additional nodes of the data structure.
        int node1_address = bestFitAllocate(memory, SIZE);
        int node2_address = bestFitAllocate(memory, SIZE);

        if (node1_address != -1 && node2_address != -1)
        {
            printf("Memory allocation for additional nodes successful.\n");

            // Access the additional nodes and initialize them.
            Node *node1 = create_node(20);
            Node *node2 = create_node(30);
            Node *node3 = create_node(40);
            Node *node4 = create_node(50);
            Node *node5 = create_node(60);
            Node *node6 = create_node(70);

            // Link the nodes together
            head->next = node1;
            node1->next = node2;
            node2->next = node3;
            node3->next = node4;
            node4->next = node5;
            node5->next = node6;

            // print
            print_list(head);

            // deallocate
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

/**
 * Perform data structure operations using the Worst-Fit algorithm.
 */
void worstFit(MemoryBlock *memory)
{
}

/**
 * Perform data structure operations using the Next-Fit algorithm.
 */
void nextFit(MemoryBlock *memory)
{
}
