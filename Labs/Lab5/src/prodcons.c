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

// global variables -----------------------

struct circular_list mylist;

// end of global variables ----------------

void *producer (void *param) {
  item i;
  unsigned int seed = 1234;

  for (;;) {
	/* The following solution to compute the amount of time to sleep
	 * is incorrect. You MUST fix it. See the "SCALE_FACTOR ..." comment
	 * section above.
	 */ 
    // sleep for random period of time
    usleep(SCALE_FACTOR * rand_r(&seed) / RAND_MAX); 
    
    // generate a random number
    i = (item) (((double) rand_r(&seed)) / RAND_MAX);

    if (circular_list_insert(&mylist, i) == -1) {
      printf("PRODUCER: error condition\n");
    } else {
      printf("PRODUCER: produced value %lf\n", i);
    }
    fflush(stdout);
  }
}

void *consumer (void *param) {
  item i;
  unsigned int seed = 999;

  for (;;) {
    // sleep for random period of time
    usleep(SCALE_FACTOR * rand_r(&seed) / RAND_MAX);

    if (circular_list_remove(&mylist, &i) == -1) {
      printf("CONSUMER: error condition\n");
    } else {
      printf("CONSUMER: consumed value %lf\n", i);
    }
    fflush(stdout);
  }
}

int main (int argc, char *argv[]) {

  // get command line arguments
  
  // if error in command line argument usage, terminate with helpful
  // message
  
  // initialize buffer
  circular_list_create(&mylist, 20);
  
  // create producer thread(s)
  
  // create consumer thread(s)
  
  // sleep to give time for threads to run
  
  // exit
  return (0);
}
