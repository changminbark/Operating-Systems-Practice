/*
 * server.c - main
 * This server can service one request at a time as it doesn't fork a 
 * separate process.
 * Xiannong Meng
 * 2020-07-16
 * 2022-08-05
 *  -- added a default port in services.h
 */
#include <stdio.h>
#include <stdlib.h>
#include "tcplib-v1.h"
#include "services.h"

int main(int argc,char *argv[])    {

  int s, t;
  int MYPORT = DEFAULT_PORT;

  if (argc == 2) {
	 MYPORT = atoi(argv[1]);  // port to use
  }
  s = socketServer(MYPORT);
  while (1)    {
    if (s > 0)
      t = acceptConn(s);
    else	{
      fprintf(stderr," socket error\n");
      exit(1);
    }
    if (t > 0)  {
      sleep(10);
      dispatch(t);
    }  else {
      fprintf(stderr," connection error\n");
      exit(2);
    }
  } /* while(1) */
  close(s);
  return 0;
}

