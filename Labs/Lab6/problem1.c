#include "problem1.h"

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

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

void *philosopher(void *params) {
    thread_param *data = (thread_param *)params;
    int id = data->id;
    pthread_mutex_t *mutexes = data->chopsticks;
    int left = (id + 4) % NUM_PHIL;
    int right = (id + 1) % NUM_PHIL;

    for ( ; ; ) {
        printf("Philosopher %d is thinking.\n", id);
        fflush(stdout);

        // napping(2, id);

        printf("Philosopher %d is hungry.\n", id);
        fflush(stdout);

        pthread_mutex_lock(&mutexes[left]);
        pthread_mutex_lock(&mutexes[right]);
        // START OF CR
        printf("Philosopher %d is starting to eat.\n", id);
        fflush(stdout);

        // napping(1, id);

        printf("Philosopher %d is done eating.\n", id);
        fflush(stdout);
        // END OF CR
        pthread_mutex_unlock(&mutexes[left]);
        pthread_mutex_unlock(&mutexes[right]);
    }
    
    return NULL;
}

int main() {
    pthread_t phils[NUM_PHIL];
    pthread_mutex_t mutexes[NUM_PHIL];
    thread_param params[NUM_PHIL];

    // Initialize mutexes
    for (int i = 0; i < NUM_PHIL; i++) {
        pthread_mutex_init(&mutexes[i], NULL);
    }

    for (int i = 0; i < NUM_PHIL; i++) {
        // Create parameters for pthread
        params[i].chopsticks = mutexes;
        params[i].id = i;

        // Create pthread
        pthread_create(&phils[i], NULL, philosopher, (void *)&params[i]);
    }

    // Join the pthreads
    for (int i = 0; i < NUM_PHIL; i++) {
        pthread_join(phils[i], NULL);
    }

    // Destroy mutexes
    for (int i = 0; i < NUM_PHIL; i++) {
        pthread_mutex_destroy(&mutexes[i]);
    }

    return 0;
}