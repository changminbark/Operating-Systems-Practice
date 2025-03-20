#ifndef _PROBLEM1_H_
#define _PROBLEM1_H_

#include <pthread.h>

typedef struct {
    pthread_mutex_t *chopsticks;
    int id;
} thread_param;

void napping(int t, unsigned int seed);

void *philosopher(void *param);

#endif