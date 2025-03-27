#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_

#include "dlist.h"
#include "dnode.h"

#include <stddef.h>

/**
 * This initializes the memory data structures.
 * Allocated_list will be empty and free_list will have 1 dnode with 
 * its mem.data set to the memory address and size as size.
 * 
 * @param size is the size of the total memory to be used
 * @return 0 if successful, -1 otherwise
 */
int allocator_init(size_t size);

/**
 * Finds the first available memory block that fits the requested size.
 * It searches through the doubly linked list and returns the first block 
 * that is large enough to satisfy the request.
 *
 * @param l is the doubly linked list representing free memory blocks
 * @param size is the size of memory requested
 * @return pointer to the memory block if found, NULL otherwise
 */
void *find_first_fit(struct dlist *l, size_t size);

/**
 * Finds the best fit memory block for the requested size.
 * This function searches through the free memory list and selects the 
 * smallest block that is still large enough to satisfy the request, 
 * reducing fragmentation.
 *
 * @param l is the doubly linked list representing free memory blocks
 * @param size is the size of memory requested
 * @return pointer to the best fitting memory block if found, NULL otherwise
 */
void *find_best_fit(struct dlist *l, size_t size);

/**
 * Finds the worst fit memory block for the requested size.
 * This function searches through the free memory list and selects the 
 * largest available block, leaving larger remaining free space.
 *
 * @param l is the doubly linked list representing free memory blocks
 * @param size is the size of memory requested
 * @return pointer to the worst fitting memory block if found, NULL otherwise
 */
void *find_worst_fit(struct dlist *l, size_t size);

/**
 * Inserts a memory block into the free list at the correct position 
 * based on its address. This ensures that the free list remains 
 * ordered, which can help with coalescing adjacent free blocks.
 *
 * @param l is the doubly linked list representing free memory blocks
 * @param m is the memory block to be inserted
 */
void add_to_correct_addr_pos(struct dlist *l, struct memory *m);

/**
 * This allocates memory (adds to allocated_list and updates free_list)
 * 
 * @param size is the size of the memory being allocated
 * @param mode selects the policy of the allocator
 * @return NULL if unsuccessful (no space), the pointer to memory data struct
 * in allocated_list
 */
void *allocate(size_t size, int mode);

/**
 * This frees the memory (removes from allocated_list and adds to free_list)
 * 
 * @param ptr is the pointer to the memory data structure (node) to deallocate
 * @return 0 if successful, -1 otherwise
 */
int deallocate(void *ptr);



#endif