#pragma once
/********************************************/
/*   list.h                                 */
/*   a dynamic  linked list with a header   */
/********************************************/


#ifndef _LIST_
#define _LIST_

#include "def.h"


/*** Definitions ***/

// Node
typedef struct node
{
	DATA			key;
	struct node*	next;
}NODE;

// List
typedef struct
{
	NODE head;
}LIST;


/*** Function prototypes ***/

BOOL L_init(LIST* pList);					// create new list

NODE* L_insert(NODE* pNode, DATA Value);	// add new node after *pNode

BOOL L_deleteAndFreeNode(NODE* pNode);					// erase node after *pNode

NODE* L_find(NODE* pNode, DATA Value);		// return a pointer to the node 

BOOL L_free(LIST* pList);					// free list memory

int L_print(LIST* pList, void(*print)(void *));		// print the list content

#endif
