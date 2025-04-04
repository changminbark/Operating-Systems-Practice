/*
 * Copyright (c) 2014 Bucknell University
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

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 
 #include "dnode.h"
 #include "dlist.h"
 
 int main(int argc, char *argv[]) {
 
   char *mystr;
   struct memory *mymem;
   struct dlist *mylist = dlist_create();
   
   printf("dlisttest running...\n");
   
   char *str1 = malloc(20);
   strncpy(str1, "animal", 20);
   
   char *str2 = malloc(20);
   strncpy(str2, "barnacle", 20);
   
   char *str3 = malloc(20);
   strncpy(str3, "carnage", 20);
   
   char *str4 = malloc(20);
   strncpy(str4, "demented", 20);
   
   char *str5 = malloc(20);
   strncpy(str5, "error", 20);
   
   printf("\ntesting dlist_add_back\n");
   dlist_add_back(mylist, str1, 20);
   dlist_add_back(mylist, str2, 20);
   dlist_add_back(mylist, str3, 20);
   dlist_add_back(mylist, str4, 20);
   dlist_add_back(mylist, str5, 20);

   printf("\ntesting dlist_print\n");
   dlist_print(mylist);
   printf("\n");
   
   traverse_forward(mylist);
   traverse_backward(mylist);	
   
   dlist_destroy(mylist);
   printf("\nlist destroyed\n");

   printf("\ntesting dlist_print\n");
   dlist_print(mylist);
   printf("\n");

   traverse_forward(mylist);
   traverse_backward(mylist);	
   printf("\ntraversal of empty list completed\n");
   
   str1 = malloc(20);
   strncpy(str1, "folly", 20);
   
   str2 = malloc(20);
   strncpy(str2, "gunk", 20);
   
   str3 = malloc(20);
   strncpy(str3, "hospital", 20);
   
   str4 = malloc(20);
   strncpy(str4, "ignorant", 20);
   
   str5 = malloc(20);
   strncpy(str5, "jelly", 20);
   
   printf("\ntesting dlist_add_front\n");
   dlist_add_front(mylist, str1, 20);
   dlist_add_front(mylist, str2, 20);
   dlist_add_front(mylist, str3, 20);
   dlist_add_front(mylist, str4, 20);
   dlist_add_front(mylist, str5, 20);

   printf("\ntesting dlist_print\n");
   dlist_print(mylist);
   printf("\n");
   
   traverse_forward(mylist);
   traverse_backward(mylist);	
   
   printf("\ntesting remove front\n");
   mymem = dlist_remove_front(mylist);
   mystr = mymem->data;
   printf("removed string = %s\n", mystr);
   free(mystr);
   free(mymem);
   printf("list length= %d\n\n", dlist_num_elems(mylist));
   
   printf("\ntesting dlist_print\n");
   dlist_print(mylist);
   printf("\n");
   
   traverse_forward(mylist);
   traverse_backward(mylist);	
   
   printf("\ntesting remove back\n");
   mymem = dlist_remove_back(mylist);
   mystr = mymem->data;
   printf("removed string = %s\n", mystr);
   free(mystr);
   free(mymem);
   printf("list length= %d\n\n", dlist_num_elems(mylist));
   
   printf("\ntesting dlist_print\n");
   dlist_print(mylist);
   printf("\n");
   
   traverse_forward(mylist);
   traverse_backward(mylist);	
   
   printf("\ntesting find_remove\n");
   mymem = dlist_find_remove(mylist, str3);
   mystr = mymem->data;
   printf("removed string = %s\n", mystr);
   free(mystr);
   free(mymem);
   printf("contents of the list\n");
   
   printf("\ntesting dlist_print\n");
   dlist_print(mylist);
   printf("\n");
   
   traverse_forward(mylist);
   traverse_backward(mylist);
 }
 
 