/* Made by Shenbo Jiang, 1271411 for COMP20003 */

/*-------------------------------------------------------------- 
Project: City of Melbourne
linked.h : the header file of linked.c
----------------------------------------------------------------*/

//

#ifndef _LINKED_H_
#define _LINKED_H_

#include "data.h"

typedef struct node node_t;

struct node {
	data_t data;
	node_t *next;
};

typedef struct {
	node_t *head;
	node_t *foot;
} list_t;

// Create empty linked list for future data appending
list_t *make_empty_list(void);

// Free up the dynamiclly allocated memory for the linked list
void free_list(list_t *list);

// Append one new node to store a new row of data (struct)
list_t *insert_at_foot(list_t *list, data_t d);


#endif
