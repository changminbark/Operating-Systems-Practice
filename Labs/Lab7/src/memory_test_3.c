/*
 * Test some basic memory allocation functions.
 * CSCI 315
 * For lab checks.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "allocator.h"

struct node {
  int count;
  char *v;
};

extern struct dlist *free_list, *allocated_list;

int main(int argc, char*argv[]) {

  int r = allocator_init(500);
  if (r == -1) {
    printf("allocate init failed\n");
    exit(1);
  }

  printf("attempting to allocate memory blocks ...\n");
  int  *i;
  char *c;
  char *d;
  char *s;
  char *x;
  char *y;
  char *z;
  char *a;
  struct node * n;

  // Allocate 4 bytes
  i = (int *)allocate(4, 2);  // size of an int is 4 bytes
  *i = 10;
  printf("value of int i %d\n", *i);
  
  // Allocate 1 byte
  c = (char*)allocate(1, 2);  // size of char is 1 byte
  *c = 'H';
  printf("value of int c %c\n", *c);

  // Deallocate 4 bytes from int i
  deallocate(i);

  // Allocate 1 byte
  // SHOULD BE DIFFERENT FOR (first fit vs. worst fit)
  d = (char*)allocate(1, 2);  // size of char is 1 byte
  *d = 'E';
  printf("value of char* d %c\n", *d);
  
  s = (char*)allocate(10, 2);  // 10 characters long
  strncpy(s, "Hello!", 7);
  printf("value of char* s '%s'\n", s);

  x = (char*)allocate(9, 2);  // 9 characters long
  strncpy(x, "World!", 7);
  printf("value of char* x '%s'\n", x);

  y = (char*)allocate(8, 2);  // 8 characters long
  strncpy(y, "TEST!", 7);
  printf("value of char* y '%s'\n", y);

  deallocate(s);
  deallocate(y);

  // SHOULD BE DIFFERENT FOR (first fit vs. best fit)
  z = (char*)allocate(8, 2);  // 10 characters long
  strncpy(z, "YES!", 7);
  printf("value of int z '%s'\n", z);
  
  n = (struct node *)allocate(sizeof(struct node), 2);
  n->v = (char*)allocate(20, 2);
  n->count = 3;
  strncpy(n->v, "How are you?", strlen("How are you?")+1);
  printf("value of int n->count %d\n", n->count);
  printf("value of int n->v %s\n", n->v);

  // SHOULD BE DIFFERENT FOR (first fit vs. best fit)
  a = (char*)allocate(2, 2);  // 10 characters long
  strncpy(a, "a", 2);
  printf("value of char* a '%s'\n", a);

  /*
   * print free_list and allocated_list
   */
  printf("Free list:\n");
  dlist_print(free_list);

  printf("Allocated list:\n");
  dlist_print(allocated_list);

  return 0;
}
