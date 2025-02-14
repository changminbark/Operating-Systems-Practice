/*
 * server.c - main
 * This server can service multiple requests at a time, each by
 * a forked child process.
 *
 * Xiannong Meng
 * 2020-07-16
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "tcplib-v1.h"
#include "services.h"

int main(int argc,char *argv[])    {

  int s, t;
  pid_t pid;
  void doEcho(int);

  int MYPORT = DEFAULT_PORT;
  if (argc == 2) {
	 MYPORT = atoi(argv[1]);  // port to use
  }
  s = socketServer(MYPORT);
  while (1) {
	if (s > 0)
		t = acceptConn(s);
    else {
      fprintf(stderr," socket error\n");
      exit(1);
    }
    if (t > 0)  {
	  if ((pid = fork()) < 0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	  } else if (pid == 0) { // child process
		dispatch(t);
		shutdown(t, SHUT_RDWR);
		exit(0);
	  }  // parent doesn't do anything, just let it go
    }  else {
      fprintf(stderr," connection error\n");
      exit(2);
    }
  } /* while(1) */
  close(s);
  return 0;
}

