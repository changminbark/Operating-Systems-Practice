/*
 * CSCI 315 Operating Systems Design
 * Date: 2014-09-02
 * Copyright (c) 2014 Bucknell University
 *
 * Permission is hereby granted, free of charge, to any individual or
 * institution obtaining a copy of this software and associated
 * documentation files (the "Software"), to use, copy, modify, and
 * distribute without restriction, provided that this copyright and
 * permission notice is maintained, intact, in all copies and supporting
 * documentation.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL BUCKNELL UNIVERSITY BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Compile with
 * gcc -Werror -Wall -std=c99 fork-data.c -o fork-data
 */

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int i = 7;
double x = 3.14;

pid_t Fork(void) {
  pid_t pid = fork();
  if (pid == -1) {
    perror("fork() failed");
    exit(-1);
  }

  return pid;
}

int main(int argc, char* argv[]) {

  int pid;
  //  int j = 6;
  double y = 2.18;

  //  char buf_parent[6];
  //  char buf_child[6]; 
  int status; // exit status to be filled by wait

  // create and open a file called data.txt
  // use open (file descriptors)
  int fd = open("data.txt", O_WRONLY | O_CREAT, 0644);

  // write into data.txt the following string:
  // "this is a test for processes created with fork\nthis is another line"
  const char *buf = "this is a test for processes created with fork\nthis is another line";
  ssize_t bytes_written = write(fd, buf, strlen(buf)); // No need to null terminate as working with raw bytes
  if (bytes_written == -1) {
    perror("write");
    close(fd);
    return 1;
  }

  // close the file so the writing can complete
  close(fd);

  // re-open the file for reading
  fd = open("data.txt", O_RDONLY); // Shared between child and parent

  if ((pid = Fork()) == 0) {
    // child process
    
    // read 5 characters from file into buf_child
    // print the characters in buf_child to terminal
    char buf_child[6];
    read(fd, buf_child, 5);
    buf_child[5] = '\0'; // Need to null terminate in C string
    printf("buf_child: %s\n", buf_child);

    printf("pid= %d -- initially, child sees x= %lf, y=%lf\n", pid, x, y);
    x = 0;
    y = 0;
    printf("pid= %d -- child sees x= %lf, y=%lf\n", pid, x, y);
    printf("child is terminating\n");

    // close the file
    close(fd);

    exit(0);

  } else {

    // parent process

    // read 5 characters from file into buf_parent
    // print the characters in buf_parent to terminal
    char buf_parent[6];
    read(fd, buf_parent, 5);
    buf_parent[5] = '\0'; // Need to null terminate in C string
    printf("buf_parent: %s\n", buf_parent);

    printf("pid= %d -- parent waits for child to terminate\n", pid);
    printf("pid= %d -- before wait parent sees x= %lf, y=%lf\n", pid, x, y);

    wait(&status); // note we are not catching the return value of wait!
    printf("parent got termination status= %d from child\n", status);
    printf("pid= %d -- after wait sees x= %lf, y=%lf\n", pid, x, y);

    // read another 5 characters from file into buf_parent
    // print the characters in buf_parent to terminal
    read(fd, buf_parent, 5);
    buf_parent[5] = '\0'; // Need to null terminate in C string
    printf("buf_parent: %s\n", buf_parent);

    // close the file
    close(fd);

    printf("parent is terminating\n");
    exit(0);
  }

}
