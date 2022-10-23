/* Made by Shenbo Jiang, 1271411 for COMP20003 */

/*-------------------------------------------------------------- 
Project: City of Melbourne
linked.c : the implementation of helper function for linked list
----------------------------------------------------------------*/

//make_empty_list, free_list and insert_at_foot are inspired from the Book PPSAA by Alistair Moffat used in COMP10002 workshop.

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "linked.h"

// Create empty linked list for future data appending
list_t
*make_empty_list(void) {
	list_t *list;
	list = (list_t*)malloc(sizeof(*list));
	assert(list!=NULL);
	list->head = list->foot = NULL;
	return list;
}

// Free up the dynamiclly allocated memory for the linked list
void
free_list(list_t *list) {
	node_t *curr, *prev;
	assert(list!=NULL);
	curr = list->head;
	while (curr) {
		prev = curr;
		curr = curr->next;
		freestring(&(prev->data));
		free(prev);
	}
	free(list);
}

// Append one new node to store a new row of data (struct)
list_t
*insert_at_foot(list_t *list, data_t value) {
	node_t *new;
	new = (node_t*)malloc(sizeof(*new));
	assert(list!=NULL && new!=NULL);
	new->data = value;
	new->next = NULL;
	if (list->foot==NULL) {
		// if this is the first insertion into the list
		list->head = list->foot = new;
	} else {
		list->foot->next = new;
		list->foot = new;
	}
	return list;
}
