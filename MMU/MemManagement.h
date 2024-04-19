#ifndef MEMORY_MANAGEMENT_H
#define MEMORY_MANAGEMENT_H

#define MEMORY_SIZE 1024  // Total memory size in bytes
#define SIZE sizeof(Node) // Size of each node in bytes
#define ITERATIONS 1000000

// Memory block structure
typedef struct MemoryBlock
{
    int start_address;
    int size;
    int is_allocated;

} MemoryBlock;

// Function prototypes
MemoryBlock *init_memory(int size);
int firstFitAllocate(MemoryBlock *memory, int size, int memory_size);
void deallocate_memory(MemoryBlock *memory, int address, int memory_size);
void compact_memory(MemoryBlock *memory);
void handle_data_structure(int choice, MemoryBlock *memory);
void handleAlgorithm(MemoryBlock *memory);
int bestFitAllocate(MemoryBlock *memory, int size, int memory_size);
int worstFitAllocate(MemoryBlock *memory, int size, int memory_size);
double timeDiff(clock_t start, clock_t end);

// Algorithms for memory mangement
void firstFit(MemoryBlock *memory);
void bestFit(MemoryBlock *memory);
void worstFit(MemoryBlock *memory);
void nextFit(MemoryBlock *memory);

#endif
