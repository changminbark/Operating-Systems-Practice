#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define BUFFER_SIZE 25
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

int main(void) {
    char write_msg[BUFFER_SIZE] = "Greetings";
    char read_msg[BUFFER_SIZE];
    char read_msg2[BUFFER_SIZE];
    int ptoc[2];
    int ctop[2];
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

        // Write each character individually to the pipe
        for (int i = 0; i < strlen(write_msg) + 1; i++) {
            Write(ptoc[WRITE_END], &write_msg[i], 1);
        }

        // Alternative (using sentinel value and while loop)
        // // Pointer to traverse the message
        // char *ptr = write_msg;

        // // Use while loop to write characters until '\0' (sentinel)
        // while (*ptr != '\0') {
        //     Write(ptoc[WRITE_END], ptr, 1);
        //     ptr++; // Move to the next character
        // }
        // Write(ptoc[WRITE_END], ptr, 1); // write sentinel value

        // Close the write end of the p2c pipe
        close(ptoc[WRITE_END]);

        printf("Parent printing\n");
        int j = 0;
        // Start reading from other pipe
        while (Read(ctop[READ_END], (void *)(read_msg2 + j), 1) > 0) {
            printf("%c\n", read_msg2[j]);
            j++;
        }

        // Close read end
        close(ctop[READ_END]);

    } else { // Child process
        // Close the unused end of the pipe
        close(ptoc[WRITE_END]);
        close(ctop[READ_END]);

        int j = 0;
        // Read one character at a time, capitalize, and store in read_msg 
        while (Read(ptoc[READ_END], (void *)(read_msg + j), 1) > 0) {
            read_msg[j] = toupper(read_msg[j]);
            j++;
        }

        // Close the read end of the pipe
        close(ptoc[READ_END]);

        // Start sending to parent
        // Write each character individually to the pipe
        for (int i = 0; i < strlen(read_msg) + 1; i++) {
            Write(ctop[WRITE_END], &read_msg[i], 1);
        }

        // Close pipe and send EOF signal
        close(ctop[WRITE_END]);
    }

    return 0;
}
