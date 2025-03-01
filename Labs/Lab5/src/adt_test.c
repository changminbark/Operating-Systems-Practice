#include <stdio.h>
#include <stdlib.h>
#include "circular_list.h"

int main(int argc, char*argv[]) {

  struct circular_list my_list;
  int  i;        // loop index
  item value;    // item in the list
  int size = 10; // list size

  printf(" === Test list creation === \n");
  if (circular_list_create(&my_list, size) != 0) {
    fprintf(stderr, "circular list creation error...\n");
    exit(1);
  }

  printf(" === Test list insertion === \n");
  for (i = 0; i < size; i ++) {
    if (circular_list_insert(&my_list, (i + 10.0)) != 0) {
      fprintf(stderr, "circular list insertion error...\n");
      exit(2);
    }
  }

  printf(" === Test list removal === \n");
  for (i = 0; i < size/2; i ++) {
    if (circular_list_remove(&my_list, &value) != 0) {
      fprintf(stderr, "circular list insertion error...\n");
      exit(2);
    }
    printf("item[%d] == %f\n", i, value);
  }

  printf(" === Test insertion after some removal === \n");
  if (circular_list_insert(&my_list, 40.0) != 0) {
    fprintf(stderr, "circular list insertion error...\n");
    exit(2);
  }
  if (circular_list_insert(&my_list, 41.0) != 0) {
    fprintf(stderr, "circular list insertion error...\n");
    exit(2);
  }

  printf(" === Test removing everything === \n");
  while (my_list.elems > 0) {
    if (circular_list_remove(&my_list, &value) != 0) {
      fprintf(stderr, "circular list removal error...\n");
      exit(2);
    }
    printf("item retrieved == %f\n", value);
  }
  

  printf(" === Test completed === \n");
  return 0;
}
