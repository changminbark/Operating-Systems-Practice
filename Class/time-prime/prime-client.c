/*
 * client.c - main 
 */

#include <stdio.h>
#include <unistd.h>
#include "tcplib-v1.h"
#include "services.h"

int main(int argc, char *argv[])   {

  int s;                   /* socket descriptor */
  int n;                   /* number to check */
  int ret_value;           /* ret_value */
  int MYPORT = DEFAULT_PORT;

  
  if (argc != 3 && argc != 2)   {
    fprintf(stderr,"usage %s hostname port-num\n",argv[0]);
    exit(1);
  }
  if (argc == 3) {
	 MYPORT = atoi(argv[2]);
  }
  s = socketClient(argv[1], MYPORT);

  int prime_srv = 3; // according to our protocol, send in a type first
  write(s, &prime_srv, sizeof(int));

  /*
   * which integer you'd like to check?
   */
  while (1) {
	 printf("Enter an integer to see if it is a prime (-1 to stop) : ");
	scanf("%d", &n);
	write(s, &n, sizeof(int)); // send the value over anyway
	if (n < 0)  // stop
	  break;
	/*
	 * Read the reply and put to user's output
	 */
	read(s, &ret_value, sizeof(int));
	printf("%7d %7s a prime\n", n, (ret_value == 1) ? "is ": "isn't");
  }

  close(s);
  return 0;
}
