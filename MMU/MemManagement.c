#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "MemManagement.h"

/**
 * Function to initialize memory and all that.
 */
void init_memory(MemoryBlock *memory, int size)
{
    memory->start_address = 0;
    memory->size = size;
    memory->is_allocated = 0;
}

/**
 * Function to allocate memory using First-Fit algorithm.
 */
int firstFitAllocate(MemoryBlock *memory, int size)
{
    int start_address = -1;

    for (size_t i = 0; i < memory->size; ++i)
    {
        if (!memory[i].is_allocated && memory[i].size >= size)
        {
            start_address = memory[i].start_address;
            memory[i].is_allocated = 1;

            // Split block if it is necessary:
            if (memory[i].size > size)
            {
                memory[i + 1].start_address = memory[i].start_address + size;
                memory[i + 1].size = memory[i].size - size;
                memory[i + 1].is_allocated = 0;
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
void deallocate_memory(MemoryBlock *memory, int address)
{
    for (size_t i = 0; i < MEMORY_SIZE; ++i)
    {
        if (memory[i].start_address == address && memory[i].is_allocated)
        {
            memory[i].is_allocated = 0;

            // Merge adjacent free blocks
            if (i > 0 && !memory[i - 1].is_allocated)
            {
                memory[i - 1].size += memory[i].size;

                // Shift memory blocks
                for (size_t j = i; j < MEMORY_SIZE - 1; ++j)
                {
                    memory[j] = memory[j + 1];
                }
            }

            if (i < MEMORY_SIZE - 1 && !memory[i + 1].is_allocated)
            {
                memory[i].size += memory[i + 1].size;

                // Shift memory blocks
                for (size_t j = i + 1; j < MEMORY_SIZE - 1; ++j)
                {
                    memory[j] = memory[j + 1];
                }
            }
            break;
        }
    }
}

/**
 * Function to compact memory.
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
int bestFitAllocate(MemoryBlock *memory, int size)
{
    int start_address = -1;
    int min_size = INT_MAX;

    for (size_t i = 0; i < MEMORY_SIZE; i++)
    {
        // Check if the block is free and large enough to accommodate the request size.
        if (!memory[i].is_allocated && memory[i].size >= size)
        {
            // Check if the current block size is smaller than the minimum size found so far.
            if (memory[i].size < min_size)
            {
                start_address = memory[i].start_address;
                min_size = memory[i].size;
            }
        }
    }

    // if start address is still -1, no suitable block was found
    if (start_address == -1)
    {
        printf("No suitable block was found.\n");
        return -1;
    }

    // Allocate memory and update block info.
    for (size_t i = 0; i < MEMORY_SIZE; i++)
    {
        if (memory[i].start_address == start_address)
        {
            memory[i].is_allocated = 1;

            // Split block if necessary
            if (memory[i].size > size)
            {
                // Create a new block after the allocated block.
                MemoryBlock newBlock;
                newBlock.start_address = start_address + size;
                newBlock.size = memory[i].size - size;
                newBlock.is_allocated = 0;

                // Shift memory blocks to make space for the new block.
                for (size_t j = MEMORY_SIZE - 1; j > i; --j)
                {
                    memory[j] = memory[j - 1];
                }

                // Insert the new block after the allocated block.
                memory[i + 1] = newBlock;

                // Update the size of the aloocated block
                memory[i].size = size;
            }
        }

        break;
    }

    return start_address;
}
