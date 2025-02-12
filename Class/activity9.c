/* cc thisfile.c -lpthread */
#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define NUM_THREADS 3

static void *show_stats(pthread_t tid);
void get_show_stack(pthread_attr_t *attr);

void *work(void *);   /* thread routine */

int v = 0;  /* Global variable (Data Segment) */
char *str;  /* Global pointer for heap allocation (Data Segment) */

int main(int argc, char *argv[]) {
    int i;  /* Stack variable */
    str = (char *)malloc(10 * sizeof(char));  /* Heap variable */
    snprintf(str, 11, "Hello, world!");

    pthread_t tid[NUM_THREADS];  /* Stack variable (Array of thread IDs) */

    /* Print memory addresses in the main thread */
    printf("Main Thread:\n");
    printf("  Address of global variable v (Data Segment): %p\n", (void*)&v);
    printf("  Address of heap variable str (Heap Segment): %p\n", (void*)str);
    printf("  Address of stack variable i (Stack Segment): %p\n", (void*)&i);
    printf("  Address of stack variable tid (Stack Segment): %p\n", (void*)tid);

    for (i = 0; i < NUM_THREADS; i++) {
        int *arg = malloc(sizeof(int));  // Allocate memory for each thread's argument
        *arg = i;
        pthread_create(&tid[i], NULL, work, arg);
    }

    for (i = 0; i < NUM_THREADS; i++)
        pthread_join(tid[i], NULL);

    printf("main() reporting that all %d threads have terminated\n", NUM_THREADS);
    printf("v should be %d, it is %d\n", NUM_THREADS, v);

    free(str);  /* Free allocated heap memory */
    return (0);
}

void *work(void *arg) {
    int local_var = 42;  /* Stack variable */
    v++;  /* Accessing global variable (Data Segment) */

    printf("Thread %lu:\n", pthread_self());
    printf("  Address of global variable v (Data Segment): %p\n", (void*)&v);
    printf("  Address of heap variable str (Heap Segment): %p\n", (void*)str);
    printf("  Address of stack variable arg (Stack Segment): %p\n", (void*)arg);
    printf("  Address of stack variable local_var (Stack Segment): %p\n", (void*)&local_var);

    show_stats(pthread_self());  // Show stack stats

    free(arg);  // Free dynamically allocated memory
    return (NULL);
}

void get_show_stack(pthread_attr_t *attr) {
    int s;
    size_t v;
    void *stkaddr;

    s = pthread_attr_getstack(attr, &stkaddr, &v);
    if (s != 0) {
        fprintf(stderr, "pthread get attr error\n");
        exit(1);
    }

    printf("=== Retrieval stack parameters ===\n");
    printf("Stack address       = %p\n", stkaddr);
    printf("Stack size          = 0x%x bytes\n", (unsigned int)v);
}

static void *show_stats(pthread_t tid) {
    int s;
    pthread_attr_t attr;

    s = pthread_getattr_np(tid, &attr);
    if (s != 0) {
        fprintf(stderr, "pthread_get_attr error\n");
        exit(1);
    }
    get_show_stack(&attr);

    return (NULL);
}
