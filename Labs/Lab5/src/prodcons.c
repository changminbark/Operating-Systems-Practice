/*
 * Copyright (c) 2013 Bucknell University
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: L. Felipe Perrone (perrone@bucknell.edu)
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h> 
#include <unistd.h>

#include "circular_list.h" 

/* SCALE_FACTOR is a constant for you to experiment with:
 * if you choose a very large SCALE_FACTOR, your threads
 * might spend a long time sleeping. If you choose it to be
 * too small, your threads will not sleep at all. Note
 * that in the producer and consumer functions, the sleep
 * time is computed as the INTEGER DIVISION below:
 *
 *  usleep(SCALE_FACTOR * rand_r(&seed) / RAND_MAX)
 *
 *  where RAND_MAX is the largest random number returned
 *  by rand_r. There are potential problems here in this computation,
 *  for example, it is possible that the value computed will be out 
 *  of range or will become zero.
 *
 *  Please make sure you think through this issue and revise
 *  the code so that a correct and meaningful value can be
 *  generated for the desired effect.
 *  
 *  You are responsible to come up with a correct solution.
 */
#define SCALE_FACTOR 1000
#define MIN_SLEEP 1000
#define MAX_SLEEP 10000

// global variables -----------------------

struct circular_list mylist;

// end of global variables ----------------

void *producer (void *param) {
  item i;
  unsigned int seed = (unsigned int)*(int *)param;

  // TODO: CHANGE THIS TO FINITE/INFINITE
  for (int k = 0; k < 100; k++) {
	/* The following solution to compute the amount of time to sleep
	 * is incorrect. You MUST fix it. See the "SCALE_FACTOR ..." comment
	 * section above.
	 */ 

   int sleep = MIN_SLEEP + (int)((MAX_SLEEP - MIN_SLEEP) * ((double)rand_r(&seed) / RAND_MAX));
    // sleep for random period of time
    usleep(sleep); 
    
    // generate a random number
    i = (item) (((double) rand_r(&seed)) / RAND_MAX);

    if (circular_list_insert(&mylist, i) == -1) {
      printf("PRODUCER: error condition\n");
    } else {
      printf("PRODUCER: produced value %lf\n", i);
    }
    fflush(stdout);
  }

  // Free the int param
  free(param);

  return NULL;
}

void *consumer (void *param) {
  item i;
  unsigned int seed = (unsigned int)*(int *)param;

  // TODO: CHANGE THIS TO FINITE/INFINITE
  for (int k = 0; k < 100; k++) {
    // sleep for random period of time
    int sleep = MIN_SLEEP + (int)((MAX_SLEEP - MIN_SLEEP) * ((double)rand_r(&seed) / RAND_MAX));
    // sleep for random period of time
    usleep(sleep); 

    if (circular_list_remove(&mylist, &i) == -1) {
      printf("CONSUMER: error condition\n");
    } else {
      printf("CONSUMER: consumed value %lf\n", i);
    }
    fflush(stdout);
  }

  // Free the int param
  free(param);

  return NULL;
}

int main (int argc, char *argv[]) {

  // get command line arguments
  int num_prod = -1;
  int num_cons = -1;
  int sleep_time = -1;

  if (argc != 4) {
    perror("Need 3 arguments: prodcons [num_prod] [num_cons] [sleep_time]\n");
    exit(1);
  }

  // Read in num_prod
  char *end_ptr1;
  num_prod = (int)strtol(argv[1], &end_ptr1, 10);
  if (*argv[1] == '\0' || *end_ptr1 != '\0') {
    fprintf(stderr, "[num_prod] must be a valid integer\n");
    exit(1);
  } else if (num_prod <= 0) {
    fprintf(stderr, "[num_prod] must be a greater than 0\n");
    exit(1);
  }

  // Read in num_cons
  char *end_ptr2;
  num_cons = (int)strtol(argv[2], &end_ptr2, 10);
  if (*argv[2] == '\0' || *end_ptr2 != '\0') {
    fprintf(stderr, "[num_cons] must be a valid integer\n");
    exit(1);
  } else if (num_cons <= 0) {
    fprintf(stderr, "[num_cons] must be a greater than 0\n");
    exit(1);
  }

  // Read in sleep_time
  char *end_ptr3;
  sleep_time = (int)strtol(argv[3], &end_ptr3, 10);
  if (*argv[3] == '\0' || *end_ptr3 != '\0') {
    fprintf(stderr, "[sleep_time] must be a valid integer\n");
    exit(1);
  } else if (sleep_time <= 0) {
    fprintf(stderr, "[sleep_time] must be a greater than 0\n");
    exit(1);
  }
  
  // initialize buffer
  circular_list_create(&mylist, 1);
  
  // create producer thread(s)
  pthread_t prods[num_prod];
  for (int i = 0; i < num_prod; i++) {
    // Need to allocate memory to create argument to pass into producer fxn
    int *arg = calloc(1, sizeof(int));
    *arg = i;
    pthread_create(&prods[i], NULL, producer, (void *)arg);
  }
  
  // create consumer thread(s)
  pthread_t cons[num_cons];
  for (int i = 0; i < num_cons; i++) {
    // Need to allocate memory to create argument to pass into consumer fxn
    int *arg = calloc(1, sizeof(int));
    *arg = i;
    pthread_create(&cons[i], NULL, consumer, (void *)arg);
  }
  
  // sleep to give time for threads to run
  sleep(sleep_time);

  // Clean up (join threads)
  for (int i = 0; i < num_prod; i++) {
    pthread_join(prods[i], NULL);
    printf("prod%d joined\n", i);
  }
  for (int i = 0; i < num_cons; i++) {
    pthread_join(cons[i], NULL);
    printf("cons%d joined\n", i);
  }

  // Destroy buffer
  circular_list_destroy(&mylist);
  
  // exit
  return (0);
}
