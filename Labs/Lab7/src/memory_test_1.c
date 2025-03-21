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

int main(int argc, char*argv[]) {

  int r = allocator_init(500);
  if (r == -1) {
    printf("allocate init failed\n");
    exit(1);
  }

  printf("attempting to allocate memory blocks ...\n");
  int  *i;
  char *c;
  char *s;
  struct node * n;

  i = (int *)allocate(4);  // size of an int is 4 bytes
  *i = 10;
  printf("value of int i %d\n", *i);
  
  c = (char*)allocate(1);  // size of char is 1 byte
  *c = 'H';
  printf("value of int c %c\n", *c);
  
  s = (char*)allocate(10);  // 10 characters long
  strncpy(s, "Hello!", 7);
  printf("value of int s '%s'\n", s);
  
  n = (struct node *)allocate(sizeof(struct node));
  n->v = (char*)allocate(20);
  n->count = 3;
  strncpy(n->v, "How are you?", strlen("How are you?")+1);
  printf("value of int n->count %d\n", n->count);
  printf("value of int n->v %s\n", n->v);

  return 0;
}
