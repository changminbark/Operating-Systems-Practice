#include "problem1.h"

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

#define NUM_PHIL 5

void *philosopher(void *params) {
    thread_param *data = (thread_param *)params;
    int id = data->id;
    pthread_mutex_t *mutexes = data->chopsticks;
    int left = (id + 4) % NUM_PHIL;
    int right = (id + 1) % NUM_PHIL;

    for ( ; ; ) {
        printf("Philosopher %d is thinking.\n", id);
        fflush(stdout);

        printf("Philosopher %d is hungry.\n", id);
        fflush(stdout);

        pthread_mutex_lock(&mutexes[left]);
        pthread_mutex_lock(&mutexes[right]);
        // START OF CR
        printf("Philosopher %d is starting to eat.\n", id);
        fflush(stdout);

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