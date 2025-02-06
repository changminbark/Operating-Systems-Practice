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

#include <unistd.h> // need this for fork
#include <stdio.h> // need this for printf and fflush

int i = 7;
double x = 3.1415926;
int pid;

int main (int argc, char* argv[]) {

  int j = 2;
  double y = 0.12345;

  if (pid = fork()) {
    // parent code
    printf("parent process -- pid= %d\n", pid); fflush(stdout);
    printf("parent sees: i= %d, x= %lf\n", i, x); fflush(stdout);
    printf("parent sees: j= %d, y= %lf\n", j, y); fflush(stdout);
  } else {
    // child code
    printf("child process -- pid= %d\n", pid); fflush(stdout);
    printf("child sees: i= %d, x= %lf\n", i, x); fflush(stdout);
    printf("child sees: j= %d, y= %lf\n", j, y); fflush(stdout);
  }   

  return(0);
}
