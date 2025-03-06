/*
 * Copyright (c) 2013 Bucknell University
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: L. Felipe Perrone (perrone@bucknell.edu)
 */

#ifndef _CIRCULAR_LIST_H_
#define _CIRCULAR_LIST_H_

#include <pthread.h>
#include <semaphore.h>

typedef double item;

/** Circular list ADT. This circular list is implemented as a
 * bounded buffer for use in multi-threaded applications.
 */
struct circular_list {
  int start; /// index of the first occupied position in buffer
  int end; /// index of the last occupied position in buffer
  int elems; /// number of elements currently held in buffer
  int size; /// capacity of the buffer 
  item *buffer; /// array of buffer items
  pthread_mutex_t mutex;
  sem_t empty;
  sem_t full;
}; 

/**
 * Create a circular list with a pre-defined buffer size.
 * @param l pointer to a circular list ADT
 * @param size number of items to allocate in circular list
 * @return 0 if successful, -1 if any error condition is found
 */
int circular_list_create(struct circular_list *l, int size);

/**                                                                       
 * Insert item into the circular list.
 * @param l pointer to a circular list ADT
 * @param i item to copy into a position of the circular list 
 * @return 0 if successful, -1 if any error condition is found
 */
int circular_list_insert(struct circular_list *l, item i);

/**                                                                       
 * Remove item from the circular list.
 * @param l pointer to a circular list ADT
 * @param i pointer to an item onto which the removed item is copied 
 * @return 0 if successful, -1 if any error condition is found
 */
int circular_list_remove(struct circular_list *l, item *i);

int circular_list_destroy(struct circular_list *l);

#endif  /* _CIRCULAR_LIST_H_ */
