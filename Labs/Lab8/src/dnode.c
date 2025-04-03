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
#include <stddef.h>

#include "dnode.h"

struct dnode *dnode_create() {
	// Allocate memory for dnode struct
	struct dnode *node = calloc(1, sizeof(struct dnode));
	if (!node) return NULL;

	// Allocate memory for memory struct
	node->mem = calloc(1, sizeof(struct memory));
	if (!node->mem) {
		free(node);
		return NULL;
	}
	// Don't allocate mem for node->mem->data as it will be assigned only, never initialized

	return node;
}

void dnode_setdata(struct dnode *n, void *ptr, size_t size) {
	n->mem->data = ptr;
	n->mem->size = size;
}

void *dnode_destroy(struct dnode *n) {
	void *ptr = n->mem->data;
	free(n);
	return ptr;
}

void dnode_obliterate(struct dnode *n) {
	free(n->mem->data);
	free(n);
} 
