#ifndef SRV_H
#define SRV_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX             512        /* a predefined string length */
#define DEFAULT_PORT    3344       /* a default port if none is given */


void dispatch(int);  // accepts connection, decides the type of request
void doRwho(int);    // service 1: return the list of users on server
void doTime(int);    // service 2: return local time
void doPrime(int);   // service 3: check if prime

int is_prime(int);   // check to see if a value is a prime
//the thread function
void *dispatch_t(void *);

#endif
