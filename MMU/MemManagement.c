#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "MemManagement.h"

/**
 * Function to initialize memory and all that.
 */
MemoryBlock *init_memory(int size)
{
    MemoryBlock *memory = malloc(size * sizeof(MemoryBlock));

    if (memory == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Initialize memory blocks
    for (size_t i = 0; i < size; ++i)
    {
        memory[i].start_address = i;
        memory[i].size = 1; // Assuming each block has a size of 1 for simplicity
        memory[i].is_allocated = 0;
    }

    return memory;
}

int firstFitAllocate(MemoryBlock *memory, int size, int memory_size)
{
    int start_address = -1;

    for (size_t i = 0; i < memory_size; ++i)
    {
        if (!memory[i].is_allocated && memory[i].size >= size)
        {
            start_address = memory[i].start_address;
            memory[i].is_allocated = 1;

            // Split block if necessary
            if (memory[i].size > size)
            {
                MemoryBlock newBlock;
                newBlock.start_address = start_address + size;
                newBlock.size = memory[i].size - size;
                newBlock.is_allocated = 0;

                for (size_t j = memory_size - 1; j > i; --j)
                {
                    memory[j] = memory[j - 1];
                }

                memory[i + 1] = newBlock;
                memory[i].size = size;
            }
            break;
        }
    }

    return start_address;
}

/**
 * Function to deallocate memory.
 */
void deallocate_memory(MemoryBlock *memory, int address, int memory_size)
{
    for (size_t i = 0; i < memory_size; ++i)
    {
        if (memory[i].start_address == address && memory[i].is_allocated)
        {
            memory[i].is_allocated = 0;

            // Merge adjacent free blocks
            if (i > 0 && !memory[i - 1].is_allocated)
            {
                memory[i - 1].size += memory[i].size;
                // Shift memory blocks
                for (int j = i; j < memory_size - 1; ++j)
                {
                    memory[j] = memory[j + 1];
                }
                // Clear the last memory block
                memory[memory_size - 1].start_address = 0;
                memory[memory_size - 1].size = 0;
                memory[memory_size - 1].is_allocated = 0;
                break;
            }

            if (i < memory_size - 1 && !memory[i + 1].is_allocated)
            {
                memory[i].size += memory[i + 1].size;

                // Shift memory blocks
                for (size_t j = i + 1; j < memory_size - 1; ++j)
                {
                    memory[j] = memory[j + 1];
                }

                // Clear the last memory block
                memory[memory_size - 1].start_address = 0;
                memory[memory_size - 1].size = 0;
                memory[memory_size - 1].is_allocated = 0;

                break;
            }
        }
    }
}

/**
 * To address memory fragmentation, we use this compaction strategy. Basically, we move allocated
 * memory blocks to consolidate free space and reduce fragmentation.
 */
void compact_memory(MemoryBlock *memory)
{
    int free_index = 0;

    for (size_t i = 0; i < MEMORY_SIZE; ++i)
    {
        if (!memory[i].is_allocated)
        {
            continue; // Skip free blocks
        }

        if (i != free_index)
        {
            // Move allocated block to free space
            memory[free_index] = memory[i];
            memory[free_index].start_address = free_index;
            free_index++;
        }
        else
        {
            free_index += memory[i].size; // Update free index
        }
    }

    // Clear remaining memory
    for (size_t i = free_index; i < MEMORY_SIZE; ++i)
    {
        memory[i].is_allocated = 0;
    }
}

/**
 * Function to allocate memory using the Best-Fit algorithm.
 */
int bestFitAllocate(MemoryBlock *memory, int size, int memory_size)
{
    int start_address = -1;
    int min_size = INT_MAX;
    int min_index = -1;

    // Find the block with the minimum size that fits the requested size
    for (size_t i = 0; i < memory_size; ++i)
    {
        if (!memory[i].is_allocated && memory[i].size >= size)
        {
            if (memory[i].size < min_size)
            {
                min_size = memory[i].size;
                min_index = i;
            }
        }
    }

    // If no suitable block was found, return -1
    if (min_index == -1)
    {
        printf("No suitable block was found for the Best-Fit algorithm.\n");
        return -1;
    }

    // Allocate memory and update block info
    start_address = memory[min_index].start_address;
    memory[min_index].is_allocated = 1;

    if (memory[min_index].size > size)
    {
        MemoryBlock newBlock;
        newBlock.start_address = start_address + size;
        newBlock.size = memory[min_index].size - size;
        newBlock.is_allocated = 0;

        for (size_t j = memory_size - 1; j > min_index; --j)
        {
            memory[j] = memory[j - 1];
        }

        memory[min_index + 1] = newBlock;
        memory[min_index].size = size;
    }

    return start_address;
}

/**
 * Function to allocate memory using the Worst-Fit algorithm.
 */
int worstFitAllocate(MemoryBlock *memory, int size, int memory_size)
{
    int start_address = -1;
    int max_size = 0;

    for (size_t i = 0; i < memory_size; ++i)
    {
        // Check if the block is free and large enough to accommodate the requested size
        if (!memory[i].is_allocated && memory[i].size >= size)
        {
            if (memory[i].size > max_size)
            {
                start_address = memory[i].start_address;
                max_size = memory[i].size;
            }
        }
    }

    // If the start address is still -1, then no suitable block was found.
    if (start_address == -1)
    {
        printf("No suitable block was found for the Worst-Fit algorithm.\n");
        return -1;
    }

    // Allocate memory and update block info.
    for (size_t i = 0; i < memory_size; ++i)
    {
        if (memory[i].start_address == start_address)
        {
            memory[i].is_allocated = 1;

            // Split block if necessary.
            if (memory[i].size > size)
            {
                MemoryBlock newBlock;
                newBlock.start_address = start_address + size;
                newBlock.size = memory[i].size - size;
                newBlock.is_allocated = 0;

                for (int j = memory_size - 1; j > i; --j)
                {
                    memory[j] = memory[j - 1];
                }

                memory[i + 1] = newBlock;
                memory[i].size = size;
            }

            break;
        }
    }

    return start_address;
}
