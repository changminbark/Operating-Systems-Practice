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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  int pid; int num;
  if ((pid = fork()) == -1) {
    perror("something went wrong in fork");
    exit(-1);
  } else if (pid == 0) {
    printf("child's PID val: %d\n", pid);
    printf("child's getpid: %d\n", getpid());
    printf("child's getppid: %d\n", getppid());
    for (num=0; num < 20; num++) {
      printf("child: %d\n", num); fflush(stdout);
      sleep(1);
    }
    exit(0); // child exit when done
  } else {
    printf("parent's PID val: %d\n", pid); // This will be child's PID
    for (num=0; num < 20; num+=3) {
       printf("parent: %d\n", num); fflush(stdout);
       sleep(1);
    }
  }
  wait(NULL); // parent waits for child to exit
  return 0;
}
