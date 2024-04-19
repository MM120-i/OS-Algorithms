#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "MemManagement.c"
#include "MemManagement.h"
#include "../DataStructures/LinkedList.c"

int main(void)
{
    MemoryBlock memory[MEMORY_SIZE];
    init_memory(MEMORY_SIZE);

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
        printf("Hash Map is not implemented yet.\n");
        break;

    case 3:
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
 * Function to calculate the time differences in miliseconds.
 */
double timeDiff(clock_t start, clock_t end)
{
    return ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
}

/**
 * Perform data structure operations using the First-Fit algorithm.
 * ========================================================================================= LINKED LIST =========================================================================================
 */
void firstFit(MemoryBlock *memory)
{
    int head_address = firstFitAllocate(memory, SIZE, MEMORY_SIZE);
    clock_t start_time = clock();

    for (int i = 0; i < ITERATIONS; ++i)
    {
        goto A;
    }

A:
    if (head_address != -1)
    {
        printf("Memory allocation for head node at address: %d\n", head_address);

        // Create a pointer to the head node and initialize it
        Node *head = create_node(0);
        head->next = NULL;

        // Allocate memory for additional nodes of the data structure
        int node1_address = firstFitAllocate(memory, SIZE, MEMORY_SIZE);
        int node2_address = firstFitAllocate(memory, SIZE, MEMORY_SIZE);

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
            deallocate_memory(memory, head_address, MEMORY_SIZE);
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

    clock_t end_time = clock();
    printf("Time taken: %.2f milliseconds\n", timeDiff(start_time, end_time));
}

/**
 * Perform data structure operations using the Best-Fit algorithm.
 *  ========================================================================================= LINKED LIST =========================================================================================
 */
void bestFit(MemoryBlock *memory)
{
    int head_address = bestFitAllocate(memory, SIZE, MEMORY_SIZE);
    clock_t start_time = clock(); // Record start time

    for (int i = 0; i < ITERATIONS; ++i)
    {
        goto A;
    }

A:
    if (head_address != -1)
    {
        printf("Memory allocation for head node at address: %d\n", head_address);

        // Create a pointer to the head node and initialize it
        Node *head = create_node(0);
        head->next = NULL;

        // Allocate memory for additional nodes of the data structure.
        int node1_address = bestFitAllocate(memory, SIZE, MEMORY_SIZE);
        int node2_address = bestFitAllocate(memory, SIZE, MEMORY_SIZE);

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
            deallocate_memory(memory, head_address, MEMORY_SIZE);
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

    clock_t end_time = clock();                                                // Record end time
    printf("Time taken: %.2f milliseconds\n", timeDiff(start_time, end_time)); // Print time taken
}

/**
 * Perform data structure operations using the Worst-Fit algorithm.
 *  ========================================================================================= LINKED LIST =========================================================================================
 */
void worstFit(MemoryBlock *memory)
{
    int head_address = worstFitAllocate(memory, SIZE, MEMORY_SIZE);
    clock_t start_time = clock(); // Record start time

    for (int i = 0; i < ITERATIONS; ++i)
    {
        goto A;
    }

A:
    if (head_address != -1)
    {
        printf("Memory allocation for head node at address: %d\n", head_address);

        // Create a ptr to head node and initialize it
        Node *head = create_node(0);
        head->next = NULL;

        // Allocate memory for additional nodes of the data structure.
        int node1_address = worstFitAllocate(memory, SIZE, MEMORY_SIZE);
        int node2_address = worstFitAllocate(memory, SIZE, MEMORY_SIZE);

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
            deallocate_memory(memory, head_address, MEMORY_SIZE);
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

    clock_t end_time = clock();                                                // Record end time
    printf("Time taken: %.2f milliseconds\n", timeDiff(start_time, end_time)); // Print time taken
}

/**
 * Perform data structure operations using the Next-Fit algorithm.
 *  ========================================================================================= LINKED LIST =========================================================================================
 */
void nextFit(MemoryBlock *memory)
{
    static int last_allocated_index = 0;
    clock_t start_time = clock(); // Record start time

    int start_index = last_allocated_index + 1;

    // Iterate through the memory blocks to find a suitable block for allocation
    for (size_t i = start_index; i < MEMORY_SIZE; ++i)
    {
        // Check if the block is free and large enough to accommodate the requested size
        if (!memory[i].is_allocated && memory[i].size >= SIZE)
        {
            int start_address = memory[i].start_address;

            memory[i].is_allocated = 1;

            // Split block if necessary
            if (memory[i].size > SIZE)
            {
                MemoryBlock new_block;
                new_block.start_address = start_address + SIZE;
                new_block.size = memory[i].size - SIZE;
                new_block.is_allocated = 0;

                // Shift memory blocks to make space for the new block
                for (size_t j = MEMORY_SIZE - 1; j > i; --j)
                {
                    memory[j] = memory[j - 1];
                }

                memory[i + 1] = new_block;
                memory[i].size = SIZE;
            }

            last_allocated_index = i;

            printf("Memory allocation for head node at address: %d\n", start_address);

            Node *head = create_node(0);
            head->next = NULL;

            int node1_address = start_address + SIZE;
            int node2_address = start_address + 2 * SIZE;

            if (node1_address < MEMORY_SIZE && node2_address < MEMORY_SIZE)
            {
                printf("Memory allocation for additional nodes successful.\n");

                Node *node1 = create_node(20);
                Node *node2 = create_node(30);
                Node *node3 = create_node(40);
                Node *node4 = create_node(50);
                Node *node5 = create_node(60);
                Node *node6 = create_node(70);

                head->next = node1;
                node1->next = node2;
                node2->next = node3;
                node3->next = node4;
                node4->next = node5;
                node5->next = node6;

                print_list(head);
                deallocate_memory(memory, start_address, MEMORY_SIZE);
            }
            else
            {
                printf("Failed to allocate memory for additional nodes.\n");
            }

            clock_t end_time = clock();                                                // Record end time
            printf("Time taken: %.2f milliseconds\n", timeDiff(start_time, end_time)); // Print time taken

            return;
        }
    }

    printf("Failed to allocate memory for the head node.\n");
}
