#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main() {
    pid_t child1, child2;

    // Parent forks child1
    child1 = fork();
    if (child1 < 0) {
        perror("Fork failed for child1\n");
        exit(1);
    } else if (child1 == 0) { // child1's counter code
        int counter = 0;
        while (1) {
            printf("child1: %d\n", counter);
            counter++;
        }
    } else { 
        // Parent forks child2
        child2 = fork(); 
        if (child2 < 0) {
            perror("Fork failed for child2\n");
            exit(1);
        } else if (child2 == 0) { // child2's counter code
            int counter = 0;
            while (1) {
                printf("child2: %d\n", counter);
                counter++;
            }
        } else { // parent's counter code
            int counter = 0;
            while (1) {
                printf("parent: %d\n", counter);
                counter++;
            }
        }
    }

    return 0;
}