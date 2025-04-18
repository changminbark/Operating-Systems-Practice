#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/* standard input/output devices */
#define STDIN  0
#define STDOUT 1
#define STDERR 2

/* message length */
#define MSGLEN 128

int main(int argc, char* argv[]) {

  int f;
  char byte;
  int count;
  int status;
  char message[MSGLEN + 1] = "open file 'hello.txt' failed.\n";

  f = open("hello.txt", O_RDONLY);

  if (f < 0) {
    write(STDERR, message, strlen(message));
    exit(2);
  }

  count = 0;
  status = read(f, &byte, 1);
  while (status > 0)   { /* if not end of the file, continue */
    /* reading one char at a time */
    write(STDOUT, &byte, 1);
    count += status;
    status = read(f, &byte, 1);
  }

  sprintf(message, "%d\n", count);
  write(STDOUT, message, strlen(message));
  close(f);

  return 0;
}
