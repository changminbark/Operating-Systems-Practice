/*
 * Revised based on the code example from:
 * https://gist.github.com/oleksiiBobko/43d33b3c25c03bcc9b2b
 * Xiannong Meng
 * 2020-07-14
 */

/*
  C socket server example, handles multiple clients using threads
  Compile
  gcc server.c -lpthread -o server
*/
 
#include <stdio.h>
#include <unistd.h>
#include "tcplib-v1.h"
#include "services.h"
#include <pthread.h> //for threading , link with lpthread

 
int main(int argc , char *argv[])  {

   int socket_desc , client_sock;
   int MYPORT = DEFAULT_PORT;
   
   if (argc == 2) {
	  MYPORT = atoi(argv[1]);  // port to use
   }
   socket_desc = socketServer(MYPORT);

   if (socket_desc <= 0) {
	  fprintf(stderr, "socket error\n");
	  exit(1);
   }

   fprintf(stderr, "Socket created.\n");
   fprintf(stderr, "Waiting for incoming connections...\n");

   pthread_t thread_id;

   while (1) {
	  if ((client_sock = acceptConn(socket_desc)) < 0)  {
		 perror("couldn't accept connection");
	  }  else {
		 fprintf(stderr, "Connection accepted\n");
         
		 if( pthread_create(&thread_id, NULL,  dispatch_t, 
							(void*) &client_sock) < 0)  {
			perror("could not create thread");
			return 1;
		 }
		
	  }
   }  // while (1)
     
   close(socket_desc);
   return 0;
}
