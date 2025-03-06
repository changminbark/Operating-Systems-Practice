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

 #include <stdlib.h>

 #include "circular_list.h"


 // The reason we make the sync primitives a member of the struct is because in case we make multiple circular lists
 int circular_list_create(struct circular_list *l, int size) {
    // Create mutex (second param is attr)
    pthread_mutex_init(&l->mutex, NULL);
    // Create semaphore for empty and full
    // Empty will be initialized to size (number of slots in c_list)
    sem_init(&l->empty, 0, size);
    // Full will be initialized to 0 (and go up to size as it will only increment when empty is decremented)
    sem_init(&l->full, 0, 0);
     l->buffer = calloc(size, sizeof(item));
     l->start = -1;
     l->end = -1;
     l->elems = 0;
     l->size = size;
     return 0;
 }
 
 // Called by producer
 int circular_list_insert(struct circular_list *l, item i) {
    // CR starts here
    sem_wait(&l->empty); // decrease empty sem by 1
    pthread_mutex_lock(&l->mutex); // acquire mutex lock 

    // No need for this as the semaphore already takes care of this situation
    //  if (l->elems == l->size) {
    //      // List is full
    //      return -1;
    //  }

     // List is empty (initialize end to 0)
     if (l->elems == 0) {
         l->start = 0;
         l->end = 0;
     } else {
        // List is not empty -> so move end
         l->end = (l->end + 1) % l->size;
     }
     l->buffer[l->end] = i;
     l->elems++;

     pthread_mutex_unlock(&l->mutex); // release mutex lock
     sem_post(&l->full); // increase full sem by 1
     // CR ends here

     return 0;
 }
 
 // Called by consumer
 int circular_list_remove(struct circular_list *l, item *i) {
    // CR starts here 
    sem_wait(&l->full); // decrease full sem by 1
    pthread_mutex_lock(&l->mutex); // acquire mutex lock 

    // No need for this as the semaphore already takes care of this situation
    //  if (l->elems == 0) {
    //      // List is empty
    //      return -1;
    //  }

     // Save item at start pointer to i
     *i = l->buffer[l->start];
     if (l->elems == 1) {
         // List will be empty after removal.
         l->start = -1;
         l->end = -1;
     } else {
        // Move start by 1
         l->start = (l->start + 1) % l->size;
     }
     // Technically element is still in array, but we cannot access it using start/end
     l->elems--;

     pthread_mutex_unlock(&l->mutex); // release mutex lock
     sem_post(&l->empty); // increase empty sem by 1
     // CR ends here

     return 0;
 }

 int circular_list_destroy(struct circular_list *l) {
    // Destroy sync primitives
    pthread_mutex_destroy(&l->mutex);
    sem_destroy(&l->empty);
    sem_destroy(&l->full);

    // Free up calloc
    free(l->buffer);

    return 0;
 }
 
