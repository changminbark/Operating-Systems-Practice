#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <readline/readline.h>
#include <readline/history.h>


#define BUFFER_SIZE 256
#define READ_END 0
#define WRITE_END 1

int Pipe(int pipefd[2]) {
    if (pipe(pipefd) == -1) {
        perror("pipe() failed");
        exit(-1);
    }
    return 0;
}

int Read(int fd, void *buf, size_t count) {
    int bytes_read = read(fd, buf, count);
    if (bytes_read == -1) {
        perror("read() failed");
        exit(-1);
    }
    return bytes_read;
}

int Write(int fd, const void *buf, size_t count) {
    int bytes_written = write(fd, buf, count);
    if (bytes_written == -1) {
        perror("write() failed");
        exit(-1);
    }
    return bytes_written;
}

void process_string(char *input, char *output) {
    char *token;
    output[0] = '\0';

    token = strtok(input, " "); // tokenize and delimit by space
    // Scan tokens until reach end of string
    while (token != NULL) {
        strcat(output, token);
        strcat(output, " ");
        token = strtok(NULL, " "); // retrieve next word in string
    } 

    // Remove last manually added space
    if (strlen(output) > 0) {
        output[strlen(output) - 1] = '\0';
    }
}

int main(void) {
    char read_msg[BUFFER_SIZE];
    char processed_msg[BUFFER_SIZE];
    int ptoc[2];
    int ctop[2];
    int len;
    pid_t pid;

    // Create the pipe
    Pipe(ptoc);
    Pipe(ctop);

    // Fork a child process
    pid = fork();
    if (pid < 0) { // Error occurred
        fprintf(stderr, "Fork Failed\n");
        return 1;
    }

    if (pid > 0) { // Parent process
        // Close the unused end of the pipe
        close(ptoc[READ_END]);
        close(ctop[WRITE_END]);
        while (1) {
            // ask for user input
            char *input = readline("INPUT: ");
            if (!input) break;
            
            // Write int 
            len = strlen(input) + 1;
            Write(ptoc[WRITE_END], &len, sizeof(int));
            // Write string
            Write(ptoc[WRITE_END], input, len);

            free(input); // free input afterwards


            // Start reading from other pipe
            printf("Parent printing\n");
            // Read int 
            Read(ctop[READ_END], &len, 4);
            // Read string
            Read(ctop[READ_END], read_msg, len);
            printf("%s\n", read_msg);
        }

        // Close write/read end (NOT NEEDED)
        close(ptoc[WRITE_END]);
        close(ctop[READ_END]);

    } else { // Child process
        // Close the unused end of the pipe
        close(ptoc[WRITE_END]);
        close(ctop[READ_END]);

        while (1) {
            // Read int 
            Read(ptoc[READ_END], &len, 4);
            // Read string
            Read(ptoc[READ_END], read_msg, len);

            // Process string into tok and concatenate it
            process_string(read_msg, processed_msg);
            len = strlen(processed_msg) + 1;

            // Start sending to parent
            // Write int 
            Write(ctop[WRITE_END], &len, sizeof(int));
            // Write string
            Write(ctop[WRITE_END], processed_msg, len);
            
        }

        // Close pipe and send EOF signal (NOT NEEDED)
        close(ctop[WRITE_END]);
        close(ptoc[READ_END]);
    }

    return 0;
}
