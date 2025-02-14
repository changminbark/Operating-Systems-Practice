/*
 * tcplib.c: this file contains necessary functions to establish TCP
 * connection using socket interface under Solaris.
 * Xiannong Meng
 * apr-22-1999
 * modified dec-15-2000, make socket reusable, call setsockopt();
 * revised 2021-09-16 to work with the newer version of gcc
 * gcc version 4.8.5 20150623 (Red Hat 4.8.5-44) (GCC)
 */

#include "tcplib-v1.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * int socketClient(char *host, int port)
 *  socketClient returns to the calling function a socket descriptor, it
 * returns a negative value if failed.
 *  host : Internet host name of the remote server
 *  port : the port number on which the server is listening
 */
int socketClient(char *host, int port)
{
   int sockfd;
   struct sockaddr_in sa;
   struct addrinfo *ptrh;


   // socket create and varification
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd == -1) {
	  printf("socket creation failed...\n");
	  exit(0);
   }
   else
	  printf("Socket successfully created..\n");

   /*
	* Get server host information
	*/
   getaddrinfo(host, NULL, NULL, &ptrh);

   /*
    * Set up socket address data for the server
    */
   memset((char *)&sa, 0, sizeof(sa));
   memcpy(&sa, (struct sockaddr_in *)(ptrh->ai_addr), ptrh->ai_addrlen);
   sa.sin_family = AF_INET;
   sa.sin_port   = htons(port);

   // connect the client socket to server socket
   if (connect(sockfd, (const struct sockaddr *)(&sa), sizeof(struct sockaddr)) < 0) {
	  printf("connection with the server failed...\n");
	  exit(0);
   }
   else
	  printf("connected to the server..\n");
   
   return sockfd;
}


/*
 * int socketServer(int port)
 * socketServer returns to the calling function a socket descriptor, it
 * returns a negative value if failed.
 *  port : the port number on which the server is listening
 * return code:
 *   -1  host does not exist
 *   -2  socket creation failed
 */
int socketServer(int port)
{
   int s;
  struct sockaddr_in  sa;  /* socket addr. structure           */

   /*
    * Allocate an open socket.
    */
   if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
     perror("TCP socket error.");
     exit(1);
   }

   /*
    * Set up socket address data for the server
    */
   memset((char *)&sa, 0, sizeof(sa));
   sa.sin_family      = AF_INET;
   sa.sin_addr.s_addr = htonl(INADDR_ANY);
   sa.sin_port        = htons(port);

   /*
    * Bind the socket to the service
    */
   if (bind(s, (struct sockaddr *)(&sa), sizeof sa) < 0) {
     perror("TCP bind error.");
     exit(1);
   }

   /*
    * Set maximum connections we will fall behind
    */
   listen(s, BACKLOG);
      
   return s;
}


/*
 * int acceptConn(int s)
 *  accepts connection from a client and returns a socket ready for
 *  communications.
 */
int acceptConn(int s)
{
   struct sockaddr_in sa;      /* internet socket structure  */
   int i, t;

   i = sizeof sa;
   /*
    * We hang in accept() while waiting for new customers
    */
   if ((t = accept(s,(struct sockaddr *)(&sa),(socklen_t*)&i)) < 0)
       return ACPTFAIL;
   return t;
}

/*
 * Wrapper for sys call write
 */
int Write(int s, char * buf, int len) {

   int bytes_written = write(s, buf, len);
	if (bytes_written != len)  {
	  perror("write");
	  exit(1);
	}
	return bytes_written;
}

/*
 * Wrapper for sys call read
 */
int Read(int s, char * buf, int len) {

   int bytes_read = read(s, buf, len);
   if (bytes_read < 0) {
	  perror("read");
	  exit(1);
   }
   return bytes_read;
}
