#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

pid_t Fork(void) {
  pid_t pid = fork();
  if (pid == -1) {
    perror("fork() failed");
    exit(-1);
  }

  return pid;
}

void print_environment(void) {
    char **arr = environ;
    while (*arr != NULL) {
        printf("%s\n", *arr);
        arr++;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("wrong number of arguments, need 2\n");
        exit(1);
    }

    print_environment();

    pid_t pid = Fork();
    int status;

    if (pid == 0) { // child process -> no need check if fork failed cuz using wrapper
        // Run cat on the command line argument
        execlp("/bin/cat", "cat", argv[1], (char *)NULL); 
        // No need to exit because binary will be replaced by cat that will exit by itself
    } else { // parent process
        // parent waits for first child
        wait(&status); 
        // child termianted properly
        if (WIFEXITED(status)) {
            pid = Fork();
            if (pid == 0) { // child 2 process
                // Run wc on the command line argument
                execlp("/usr/bin/wc", "wc", argv[1], (char *)NULL);
            } else { // parent process
                wait(&status);
                return 0;
            }
        }
    }
}