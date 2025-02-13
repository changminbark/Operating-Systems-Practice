#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
    char read_char;
    int fd[2];
    pid_t pid;

    // Create the pipe
    Pipe(fd);

    // Fork a child process
    pid = fork();
    if (pid < 0) { // Error occurred
        fprintf(stderr, "Fork Failed\n");
        return 1;
    }

    if (pid > 0) { // Parent process
        // Close the unused end of the pipe
        close(fd[READ_END]);

        // Write each character individually to the pipe
        for (int i = 0; i < strlen(write_msg); i++) {
            Write(fd[WRITE_END], &write_msg[i], 1);
        }

        // Alternative (using sentinel value and while loop)
        // // Pointer to traverse the message
        // char *ptr = write_msg;

        // // Use while loop to write characters until '\0' (sentinel)
        // while (*ptr != '\0') {
        //     Write(fd[WRITE_END], ptr, 1);
        //     ptr++; // Move to the next character
        // }
        // Write(fd[WRITE_END], ptr, 1); // write sentinel value

        // Close the write end of the pipe
        close(fd[WRITE_END]);

    } else { // Child process
        // Close the unused end of the pipe
        close(fd[WRITE_END]);

        // Read one character at a time and print to standard output
        while (Read(fd[READ_END], &read_char, 1) > 0) {
            printf("%c\n", read_char);
            fflush(stdout); // Ensure immediate output
        }

        // Close the read end of the pipe
        close(fd[READ_END]);
    }

    return 0;
}
