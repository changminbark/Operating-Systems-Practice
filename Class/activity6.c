/**
 * primepipe.c Activity
 * Author: Alexander Fuchsberger
 * Creates a child process that indefinately finds new prime numbers, time-complexity: O(sqrt(n))
 * and sends them back to the parent process via a pipe.
 * Objective: Complete the piping part of this activity.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

bool is_prime(int n)
{
  // Handle special cases
  if (n <= 1) {
    return false;
  }
  if (n == 2 || n == 3) {
    return true;
  }
  if (n % 2 == 0 || n % 3 == 0) {
    return false;
  }

  // Check for factors from 5 up to sqrt(n)
  for (int i = 5; i * i <= n; i += 6) {
    if (n % i == 0 || n % (i + 2) == 0) {
      return false;
    }
  }

  return true;
}

int main(int argc, char * argv[]){

  // TODO: set up unidirectional pipe
  int p2c[2];

  int pipe_ret = pipe(p2c);
  if (pipe_ret == -1) {
    perror("couldn't create pipe");
    exit(1);
  }

  pid_t pid = fork();

  if (-1 == pid) {
	  printf("error creating child process...\n");
	  exit(1);
  } else if (0 != pid) {  // parent process

    // indefinitely listen for child process to send primes

    int buf[1]; // could use pointer too -> malloc/calloc
    close(p2c[1]); // close write end

    while(1){
      // Check for read and see how many bytes are being read
        if (read(p2c[0], buf, sizeof(int)) == 0) { // read buffer into pipe
            close(p2c[0]);
            break; // close read end and break out of loop if reading 0 bytes.
        }
        printf("%d\n", buf[0]);
    }

  } else {  // pid == 0, child process
    int i = 0;
    bool prime;

    int buf[1]; // could use pointer too
    close(p2c[0]); // close read end

    while(1){
      // stop to not show more than primes > 1000
      if(i >= 1000){
        close(p2c[1]); // close write end
        exit(0);
      }

      prime = is_prime(i);

      if(prime) {
        buf[0] = i; // Save integer in buffer
        write(p2c[1], buf, sizeof(int)); // Write buffer into pipe
      }
      i++;
    }
  }

  wait(NULL);
  return 0;
}
