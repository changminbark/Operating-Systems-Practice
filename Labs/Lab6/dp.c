#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>

#define NUM_PHIL 5
#define MIN_SLEEP 0


void napping(int t, unsigned int seed) {
    // Calculate random sleep time
    int sleep = MIN_SLEEP + (int)((t - MIN_SLEEP) * ((double)rand_r(&seed) / RAND_MAX));

    // Create timespec structs to use in nanosleep (required)
    struct timespec req;

    // Set the seconds and nanoseconds for required sleep
    req.tv_sec = (time_t)sleep;
    req.tv_nsec = (time_t)0;

    // Sleep
    nanosleep(&req, NULL);

    return;
}

void *philosopher(void *param) {
    int id = *(int *)param;
    for ( ; ; ) {
        printf("Philosopher %d is thinking.\n", id);
        napping(2, id);
        printf("Philosopher %d is hungry.\n", id);
        printf("Philosopher %d is starting to eat.\n", id);
        napping(1, id);
        printf("Philosopher %d is done eating.\n", id);
    }
    
    free(param);
    return NULL;
}

int main() {
    pthread_t phils[NUM_PHIL];

    for (int i = 0; i < NUM_PHIL; i++) {
        int *arg = calloc(1, sizeof(int));
        *arg = i;
        pthread_create(&phils[i], NULL, philosopher, (void *)arg);
    }

    for (int i = 0; i < NUM_PHIL; i++) {
        pthread_join(phils[i], NULL);
    }

    return 0;
}