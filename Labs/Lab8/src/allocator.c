#include "dlist.h"
#include "dnode.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

// Doubly linked lists to simulate/represent allocated and free memory
struct dlist *allocated_list, *free_list;

int allocator_init(size_t size) {
    // Create/initialize the doubly linked lists
    allocated_list = dlist_create();
    free_list = dlist_create();

    // Allocate memory in OS
    void *initial_mem = malloc(size); 
    if (initial_mem == NULL) {
        return -1;
    }

    // Add/allocate initial memory address to free_list
    // Size will create a bound on what addresses are valid
    // Will range from [initial_mem, initial_mem + size)
    dlist_add_front(free_list, initial_mem, size);

    return 0;
}

void *find_first_fit(struct dlist *l, size_t size) {
    // Traverse until we find first fit
    struct memory *mem = (struct memory *)dlist_iter_begin(l);
    while (mem != NULL && mem->size < size) {
        mem = (struct memory *)dlist_iter_next(l);
    }

    // Return NULL if cannot find
    if (mem == NULL) return NULL;

    // Else, we found a first fit; return the memory
    return mem;
}

void *find_best_fit(struct dlist *l, size_t size) {
    // Initialize candidate
    struct dnode *candidate_node = NULL;

    // Traverse all list and look for best fit
    struct memory *mem = (struct memory *)dlist_iter_begin(l);
    while (mem != NULL) {
        // Found a node with valid size
        if (mem->size >= size) {
            // If candidate has not been initialized OR (if init) mem size < candidate size
            if (candidate_node == NULL || mem->size < candidate_node->mem->size) {
                candidate_node = l->iter;
            } 
        }
        mem = (struct memory *)dlist_iter_next(l);
    }

    // Return NULL if cannot find
    if (candidate_node == NULL) return NULL;

    // Else, we found a best fit; set iter & return the candidate
    l->iter = candidate_node;
    return candidate_node->mem;
}

void *find_worst_fit(struct dlist *l, size_t size) {
    // Initialize candidate
    struct dnode *candidate_node = NULL;

    // Traverse all list and look for worst fit
    struct memory *mem = (struct memory *)dlist_iter_begin(l);
    while (mem != NULL) {
        // Found a node with valid size
        if (mem->size >= size) {
            // If candidate has not been initialized OR (if init) mem size > candidate size
            if (candidate_node == NULL || mem->size > candidate_node->mem->size) {
                candidate_node = l->iter;
            } 
        }
        mem = (struct memory *)dlist_iter_next(l);
    }

    // Return NULL if cannot find
    if (candidate_node == NULL) return NULL;

    // Else, we found a worst fit; set iter & return the candidate
    l->iter = candidate_node;
    return candidate_node->mem;
}

void add_to_correct_addr_pos(struct dlist *l, struct memory *m) {
    // Add new node to list in correct position
    // Find correct position to add in list
    struct memory *mem_iter = (struct memory *)dlist_iter_begin(l); 
    while (mem_iter != NULL && mem_iter->data < m->data){
        mem_iter = (struct memory *)dlist_iter_next(l);
    }

    // Adding to back (iter reached the end, which is NULL)
    if (mem_iter == NULL) {
        dlist_add_back(l, m->data, m->size);
    } else if (mem_iter == l->front->mem) {
    // Adding to front (iter is still pointing to front)
        dlist_add_front(l, m->data, m->size);
    } else {
    // Adding somewhere in the middle (iter has something before & after)
        dlist_add_iter_prev(l, m->data, m->size);
    }
}

void *allocate(size_t size, int mode) {
    // Find free node's memory using a specific policy
    struct memory *candidate;
    if (mode == 0) {
        candidate = find_first_fit(free_list, size);
    } else if (mode == 1) {
        candidate = find_best_fit(free_list, size);
    } else if (mode == 2) {
        candidate = find_worst_fit(free_list, size);
    } else {
        return NULL;
    }
    
    // If no space available (cannot find in free_list), return NULL
    if (candidate == NULL) return NULL;

    // Remove node from free_list (COULD OPTIMIZE BY USING l->iter PTR, BUT MORE CONFUSING)
    dlist_find_remove(free_list, candidate->data);

    // Create and add new node into allocated_list 
    struct memory *new_alloc_mem = (struct memory *)malloc(sizeof(struct memory));
    new_alloc_mem->data = candidate->data;
    new_alloc_mem->size = size;
    add_to_correct_addr_pos(allocated_list, new_alloc_mem);

    // Modify free memory candidate
    candidate->data += size;
    candidate->size -= size;
    if (candidate->size < 0) {
        free(candidate);
        return NULL;
    } else if (candidate->size > 0) {
    // Add back modified free memory node into free_list (refactor deallocate)
        add_to_correct_addr_pos(free_list, candidate);
    } else {
    // Delete free memory candidate (NOT THE ACTUAL MEMORY ALLOCATED BY OS)
        free(candidate);
    }

    return new_alloc_mem->data;
}

// No checks for valid addresses needed as only valid allocation occurred 
// using free_list
int deallocate(void *ptr) {
    // Find and remove node from allocated_list and get memory struct
    struct memory *freed_mem = dlist_find_remove(allocated_list, ptr);
    if (freed_mem == NULL) return -1;

    add_to_correct_addr_pos(free_list, freed_mem);

    return 0;
}

double average_frag(struct dlist *l) {
    int largest_mem = 0;
    int total_mem = 0;

    // Iterate and find largest mem and total_mem
    struct memory *mem_iter = (struct memory *)dlist_iter_begin(l);
    while (mem_iter != NULL) {
        total_mem += (int)mem_iter->size;  // Assume that total mem is less than MAX_INT

        if ((int)mem_iter->size > largest_mem) {
            largest_mem = (int)mem_iter->size;
        }

        mem_iter = (struct memory *)dlist_iter_next(l);
    }

    // Edge case where everything is allocated
    if (total_mem == 0) {
        return 0.0;
    }

    return (1.0 - ((double)largest_mem / (double)total_mem));
}
