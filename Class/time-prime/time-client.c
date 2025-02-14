/*
 * time-cclient.c - main 
 * Request the server for local time.
 *
 * Xiannong Meng
 * 2020-07-17
 * For CSCI 315 class demonstration.
 */

#include <stdio.h>
#include <unistd.h>
#include "tcplib-v1.h"
#include "services.h"

int main(int argc, char *argv[])   {

  int s;                   /* socket descriptor                */
  int len;                 /* length of received data          */
  char buf[MAX];           /* buffer to read time info        */
  int MYPORT = DEFAULT_PORT;
  
  if (argc != 3 && argc != 2)   {
    fprintf(stderr,"usage %s hostname [port-num]\n",argv[0]);
    exit(1);
  }

  if (argc == 3) {
	 MYPORT = atoi(argv[2]);
  }
  s = socketClient(argv[1], MYPORT);

  int time_srv = 2; // according to our protocol, send in a type first
  write(s, &time_srv, sizeof(int));

  /*
   * Read the reply and put to user's output
   */
  len = read(s,buf,MAX);
  buf[len] = 0;
  write(1,buf,len);

  close(s);
  return 0;
}
