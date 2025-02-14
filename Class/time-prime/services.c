/*
 * This file contains a number of services provided by the server.
 *
 * 2020-07-17
 * Xiannong Meng
 * For CSCI 315 classroom demonstration
 * Revised 2021-09-14
 * Removed the getuent() service
 * Added is_prime() service
 */

/*
 * Accepts the client request and decide what service was requested.
 * Read an integer "service" from the client which represents the 
 * service request.
 *
 * //If "service" == 1, do rwho service  // removed
 * If "service" == 2, do time service
 * If "service" == 3, do is_prime service
 *
 * In a real application, one'd use select() to choose different services. 
 * We assume the service request is correct to simplify the code.
 * 
 * Params
 * int t: the client socket connection
 */
#include "services.h"


/*
 * Thread version of dispatch
 */
void *dispatch_t(void * sock_desc) {

  //Get the socket descriptor
  int sock = *(int*)sock_desc;

  dispatch(sock); // call the real dispatcher

  return NULL;
}

void dispatch(int t) {

  int type;
  
  if (read(t, &type, sizeof(int)) != sizeof(int)) {
	fprintf(stderr, "service request error\n");
	exit(4);
  }

  printf("DEBUG: service request value %d\n", type);
  if (type == 2) {
	fprintf(stderr, "time service\n");
	doTime(t);
  } else if (type == 3) {
	 fprintf(stderr, "is_prime service\n");
	 doPrime(t);
  } else {
	 fprintf(stderr, "wrong request\n");
  }
}

/*
 * Return local time to the client.
 */
void doTime(int t) {

#include <time.h>

  time_t ltime;
  char buf[50];
 
  time(&ltime);
  ctime_r(&ltime, buf);
  if (write(t, buf, strlen(buf)) != strlen(buf)) {
	fprintf(stderr, "time error\n");
	exit(4);
  }
}

/*
 * Check if an integer is a prime
 */
void doPrime(int t) {

   int value;
   int ret_check = 0;

   // read an int from the client
   read(t, &value, sizeof(int));
   while (value != -1) {
	  ret_check = is_prime(value);
	  write(t, &ret_check, sizeof(int));
	  read(t, &value, sizeof(int));
   }

}

int is_prime(int n)
{
  // return 1 if n is prime, 0 otherwise
  int i = 2;
  int yes = 1;  // true

  while (i < n && yes == 1) {
    if (n % i == 0)
      yes = 0;
    i ++;
  }
  return yes;
}
