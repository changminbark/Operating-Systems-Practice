#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

pid_t Fork(void) {
    pid_t pid = fork();
    if (pid == -1) {
      perror("fork() failed");
      exit(-1);
    }
  
    return pid;
  }

int main() {
    int *test = (int *)malloc(sizeof(int));
    *test = 69;

    pid_t pid = Fork();
    if (pid == 0) {
        // child process
        printf("CHILD: %d\n", *test);
        exit(0);
    } else {
        // parent process
        printf("PARENT: %d\n", *test);
    }
    wait(NULL);
    return 0;
}