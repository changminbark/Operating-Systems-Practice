/*
 * Copyright (c) 2012 Bucknell University
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
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "dnode.h"
#include "dlist.h"

struct dlist *
dlist_create() {
	return calloc(1, sizeof(struct dlist));
}

void 
dlist_destroy(struct dlist *l) {
	struct dnode *p = l->front;

	do {
		l->front = l->front->next;
		free(p->mem->data);
		free(p->mem);
		free(p);
		p = l->front;
	} while (l->front != NULL);

	l->front = l->back = NULL;
	l->counter = 0;
}


void 
dlist_obliterate(struct dlist *l) {
	dlist_destroy(l);
	free(l);
}

void 
dlist_add_front(struct dlist *l, void *ptr, size_t size) {
	struct dnode *n = dnode_create();
	dnode_setdata(n, ptr, size);

	if (0 == l->counter) {
		l->front = l->back = n;	
		l->counter = 1;
	} else {
		n->next = l->front;
		l->front->prev = n;
		l->front = n;
		(l->counter)++;
	}

#ifdef DEBUG
	printf("counter= %d, %s\n", l->counter, (char *) ptr);
	printf("front= %s\n", (char *) l->front->mem->data);
	printf("back= %s\n\n", (char *) l->back->mem->data);
#endif /* DEBUG */
}

void 
dlist_add_back(struct dlist *l, void *ptr, size_t size) {
	struct dnode *n = dnode_create();
	dnode_setdata(n, ptr, size);

	if (0 == l->counter) {
		l->front = l->back = n;	
		l->counter = 1;
	} else {
		n->prev = l->back;
		l->back->next = n;
		l->back = n;
		(l->counter)++;
	}

#ifdef DEBUG
	printf("counter= %d, %s\n", l->counter, (char *) ptr);
	printf("front= %s\n", (char *) l->front->mem->data);
	printf("back= %s\n\n", (char *) l->back->mem->data);
#endif /* DEBUG */
}

void
dlist_add_iter_prev(struct dlist *l, void *ptr, size_t size) {
	struct dnode *n = dnode_create();
	dnode_setdata(n, ptr, size);

	if (0 == l->counter) { // If implemented correctly, this shouldn't run
		l->front = l->back = n;	
		l->counter = 1;
	} else {
		n->next = l->iter;
		n->prev = l->iter->prev;
		l->iter->prev->next = n;
		l->iter->prev = n;
		(l->counter)++;
	}
}

void *
dlist_remove_front(struct dlist *l) {
	struct dnode *n = l->front;
	void* ptr = n->mem;

	if (1 == l->counter) {
		l->front = l->back = NULL;
	} else {
		l->front = l->front->next;
		l->front->prev = NULL;
	}

	(l->counter)--;
	free(n);
	return ptr;
}

void *
dlist_remove_back(struct dlist *l) {
	struct dnode *n = l->back;
	void *ptr = n->mem;

	if (1 == l->counter) {
		l->front = l->back = NULL;
	} else {
		l->back = l->back->prev;
		l->back->next = NULL;
	}

	(l->counter)--;
	free(n);
	return ptr;
}

// Find and removes/frees node (but not data in node)
void *
dlist_find_remove(struct dlist *l, void *ptr) {
	struct dnode *n = l->front;
	void *ret_ptr = NULL;

	while ((n != NULL) && (n->mem->data != ptr)) {
	  n = n->next;
	}

	if (n != NULL) {
	  if (l->front == n) {
	    return dlist_remove_front(l);
	  } else if (l->back == n) {
	    return dlist_remove_back(l);
	  } else {
	    if (1 == l->counter) {
	      l->front = l->back = NULL;
	    } else {
	      n->prev->next = n->next;
	      n->next->prev = n->prev;
	    }
	    (l->counter)--;
	  }
	  
	  ret_ptr = n->mem;
	  free(n);
	}
	
	return ret_ptr;
}

uint32_t 
dlist_num_elems(struct dlist *l) {
	return l->counter;
}

void *
dlist_iter_begin(struct dlist *l) {
	void *ret_val = NULL;

	l->iter = l->front;
	if (l->iter != NULL) {
		ret_val = l->iter->mem; 
	}

	return ret_val;
}

void *
dlist_iter_next(struct dlist *l) {
	void *ret_val = NULL;

	if (l->iter != NULL) {
		l->iter = l->iter->next;
		if (l->iter != NULL) {
			ret_val = l->iter->mem;
		}
	}

	return ret_val;
}

bool 
dlist_iter_has_next(struct dlist *l) {
	bool ret_val = false;

	if (l->iter != NULL) {
		ret_val = (l->iter->next != NULL);
	}

#ifdef DEBUG
	if (ret_val) {
		printf("dlist_has_next: current is %s\n", (char *) l->iter->mem->data);
		printf("dlist_has_next: returning %d\n\n", ret_val);
	}
#endif /* DEBUG */

	return ret_val;
}


void *
dlist_iter_end(struct dlist *l) {
	void *ret_val = NULL;

	l->iter = l->back;
	if (l->iter != NULL) {
		ret_val = l->iter->mem;
	}

	return ret_val;
}

void *
dlist_iter_prev(struct dlist *l) {
	void *ret_val = NULL;

	if (l->iter != NULL) {
		l->iter = l->iter->prev;
		if (l->iter != NULL) {
			ret_val = l->iter->mem;
		}
	}

	return ret_val;
}

bool 
dlist_iter_has_prev(struct dlist *l) {
	bool ret_val = false;

	if (l->iter != NULL) {
		ret_val = (l->iter->prev != NULL);
	}

	return ret_val;
}

void
traverse_forward(struct dlist *l) {
  char *str;
  struct memory *mem;
  printf("forward traversal\n");
  for (mem = (struct memory *)dlist_iter_begin(l); mem != NULL;
    mem = (struct memory *)dlist_iter_next(l))	{ 
		str = (char *) mem->data;
    	printf("string = %s\n", str);
  }
}

void
traverse_backward(struct dlist *l) {
  char *str;
  struct memory *mem;
  printf("backward traversal\n");
  for (mem = (struct memory *)dlist_iter_end(l); mem != NULL;
  	mem = (struct memory *)dlist_iter_prev(l))	{ 
    	str = (char *) mem->data;
		printf("string = %s\n", str);
  }
}

void
dlist_print(struct dlist *l) {
	struct dnode *n = l->front;

	while (n) {
		printf("-[%ld, %p]-", n->mem->size, n->mem->data);

		n = n->next;
	}
	printf("\n");
}