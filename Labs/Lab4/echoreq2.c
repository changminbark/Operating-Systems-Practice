/*
 * CSCI 315 Operating Systems Design
 * Author: L. Felipe Perrone
 * Date: 2014-09-21
 * Copyright (c) 2014 Bucknell University
 *
 * Permission is hereby granted, free of charge, to any individual
 * or institution obtaining a copy of this software and associated
 * documentation files (the "Software"), to use, copy, modify, and
 * distribute without restriction, provided that this copyright
 * and permission notice is maintained, intact, in all copies and
 * supporting documentation.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL BUCKNELL UNIVERSITY BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "wrappers.h"

#define BUFFER_SIZE 512
#define TRUE 1
#define FALSE 0

/*------------------------------------------------------------------------
 * Program:   echoreq
 *
 * Purpose:  allocate a socket, connect to a server, transfer requested
 *            file to local host, and print file contents to stdout
 *
 * Usage:    echoreq [ host ] [ port ] [ string ] 
 *
 *		 host  - name of a computer on which server is executing
 *		 port  - protocol port number server is using
 *     string - a string in double quotes
 *     
 *------------------------------------------------------------------------
 */

int
main(int argc, char* argv[]) {

	struct	addrinfo hints, *res, *p;		

	int	sd;		                 // socket descriptor			
	char *port;		               // protocol port number		
	char *host;                // pointer to host name		
	char  in_msg[BUFFER_SIZE]; // buffer for incoming message

	// verify usage

	if (argc < 4) {
		printf("Usage: %s [ host ] [ port ] [ string ]\n", argv[0]);
		exit(-1);
	}

	host = argv[1];		
	port = argv[2];	

	if (port <= 0) {				
		// print error message and exit	
		printf("ECHOREQ: bad port number %s\n", argv[2]);
		exit(-1);
	}

	// Set hints to specifications
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC; // both ipv4 and ipv6
	hints.ai_socktype = SOCK_STREAM;

	if (getaddrinfo(host, port, &hints, &res) != 0) {
		perror("Could not get address info\n");
		exit(-1);
	}

	// Loop through all possible search results
	for (p = res; p != NULL; p = p->ai_next) {
		// create socket 
		sd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		// connect the socket to the specified server 
		if (connect(sd, p->ai_addr, p->ai_addrlen) == 0) {
			break;
		}
	}

	if (p == NULL) { // No valid connection
		fprintf(stderr, "ECHOREQ: Could not connect to server\n");
		freeaddrinfo(res);
		exit(-1);
	}

	// send message to server
	Send(sd, argv[3], strlen(argv[3]), 0);


	// receive message echoed back by server
	Recv(sd, in_msg, sizeof(in_msg), 0);

	printf("ECHOREQ: from server= %s\n", in_msg);

	// close the socket   
	close(sd);

	// terminate the client program gracefully 
	return(0);
}
