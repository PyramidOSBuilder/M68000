#ifndef __M68_LIST_H__
#define __M68_LIST_H__
#include <stdlib.h>
#include <string.h>

/* Simple doubly linked list
 *
 */

typedef struct listNode {
	void *data;
	struct listNode* next;
	struct listNode* prev;
}listNode;

typedef struct List {
	listNode* head;
	listNode* tail;
	int size;
	void (*cleanNode)(void*); //free routine funcptr
	void (*printNode)(void*); //print routine funcptr
}List;

//Create a new list
List* newList(void(*cleanNode)(void*),void(*printNode)(void*));
//New node
listNode* newNode(void* data);
//Add data to list
void addList(List* list,void* data);
//Add a node to list
void addNodeList(List* list,listNode* node);
//Search list using a simple comparator func
listNode* searchList(List* list,void* data,int(*cmp)(void*,void*));
//Remove from list using a comparator func
void removeNode(List* list,void* data,int(*cmp)(void*,void*));
//Destroy list
void deleteList(List* list);

#endif

