#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <errno.h>

#define SEM_NAME "/sem_changmin_channel"
#define CHANNEL_FILE "channel.txt"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"message\"\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);

    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    FILE *fp = NULL;
    // Start of critical region
    sem_wait(sem); 
    fp = fopen(CHANNEL_FILE, "a"); // append to file
    if (fp == NULL) {
        perror("fopen");
        sem_post(sem);
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "%s\n", argv[1]);
    fflush(fp);
    fclose(fp);

    sem_post(sem);
    sem_close(sem);

    return 0;
}