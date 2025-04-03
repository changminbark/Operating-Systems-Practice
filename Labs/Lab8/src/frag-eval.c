/*
 * Test some basic memory allocation functions.
 * CSCI 315
 * For lab checks.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "allocator.h"
#include "dlist.h"

#define MAX_ALLOCATIONS 1000   // number of trials

extern struct dlist *free_list, *allocated_list;

bool is_integer(const char *str) {
  if (*str == '-' || *str == '+') str++; // skip sign

  if (*str == '\0') return false; // no digits

  while (*str) {
      if (!isdigit(*str)) return false;
      str++;
  }
  return true;
}

int main(int argc, char*argv[]) {

  if (argc != 4) {
    printf("Need 3 arguments: frag-eval [algorithm: int] [seed: unsigned int] [requests: int]\n");
    exit(1);
  }

  if (!is_integer(argv[1]) || !is_integer(argv[2]) || !is_integer(argv[3])) {
    printf("Arguments must be integers\n");
    exit(1);
  }

  if (atoi(argv[2]) < 0) {
    printf("Seed has to be positive\n");
    exit(1);
  }

  if (atoi(argv[1]) < 0 || atoi(argv[1]) > 2) {
    printf("Algorithm has to be 0 (first fit), 1 (best fit), or 2 (worst fit)\n");
    exit(1);
  }

  int algorithm = atoi(argv[1]);
  unsigned int seed = (unsigned int)atoi(argv[2]); 
  int requests = atoi(argv[3]);

  int r = allocator_init(10240);
  if (r == -1) {
    printf("allocate init failed\n");
    exit(1);
  }

  printf("attempting to allocate memory blocks ...\n");
  void *memory_block[MAX_ALLOCATIONS];
  int active_count = 0;
  int action = 0;
  
  srand(seed);

  int curr_req = 0;
  while (curr_req < requests) {
    action = rand() % 2;
    if (action == 0 || active_count == 0) {
      int block_size = 100 + (rand() % 10000);
      void *p = allocate(block_size, algorithm);
      printf("allocate %u bytes...\n", block_size);
      if (p != NULL && active_count < MAX_ALLOCATIONS) {
        memory_block[active_count] = p;
        active_count++;
      } else {
        printf("alloation failed\n");
      }
    } else {
      int idx = rand() % active_count;    // which block to free 
      r = deallocate(memory_block[idx]);
      if (r == 0) {
        memory_block[idx] = memory_block[active_count - 1];
        active_count--;
        printf("deallocate 0x%llx successfully\n", (unsigned long long)memory_block[idx]);
      } else {
        printf("deallocate 0x%llx unsuccessfully\n", (unsigned long long)memory_block[idx]);
      }
    }
    curr_req++;
  }

  double frag = average_frag(free_list);
  printf("Average fragmentation: %f\n", frag);

  return 0;
}
