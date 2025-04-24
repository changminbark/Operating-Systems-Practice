#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/inotify.h>

#define SEM_NAME "/sem_changmin_channel"
#define CHANNEL_FILE "channel.txt"
#define MAX_LINE 1024
#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUF_LEN (1024 * (EVENT_SIZE + 16))

int main() {
    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);

    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    int fd_inotify = inotify_init();
    if (fd_inotify < 0) {
        perror("inotify_init");
        exit(EXIT_FAILURE);
    }

    int wd = inotify_add_watch(fd_inotify, CHANNEL_FILE, IN_MODIFY);
    if (wd < 0) {
        perror("inotify_add_watch");
        exit(EXIT_FAILURE);
    }

    char buffer[BUF_LEN];
    long last_offset = 0;

    while(1) {
        int length = read(fd_inotify, buffer, BUF_LEN);
        if (length < 0) {
            perror("read inotify");
            continue;
        }

        // Enter critical region of reading from file
        sem_wait(sem);
        FILE *fp = fopen(CHANNEL_FILE, "r");
        if (!fp) {
            perror("fopen");
            sem_post(sem);
            continue;
        }

        // Go seek the last_offset position in the file
        fseek(fp, last_offset, SEEK_SET);
        char line[MAX_LINE];
        // Have a while loop just in case there are multiple line messages sent by a single sender
        while (fgets(line, sizeof(line), fp)) {
            line[strcspn(line, "\n")] = '\0';
            printf("receiver [msg arrival]: \"%s\"\n", line);
            fflush(stdout);
        }
        // Move pointer up to where fp is pointing too
        last_offset = ftell(fp);
        fclose(fp);
        sem_post(sem);
    }

    // cleanup
    inotify_rm_watch(fd_inotify, wd);
    close(fd_inotify);
    sem_close(sem);
    return 0;
}