#include <stdio.h>
#include <list.h>

List* newList(void(*cleanNode)(void*),void(*printNode)(void*)){
	List* list = malloc(sizeof(List));
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	list->cleanNode = cleanNode;
	list->printNode = printNode;
	return list;
}

listNode* newNode(void* data){
	listNode* node = malloc(sizeof(listNode));
	node->data = data;
	node->next = NULL;
	node->prev = NULL;
	return node;
}

void addList(List* list,void* data){
	if(list == NULL){
		printf("Error: NULL list passed to addList\n");
		return;
	}

	if(list->head == NULL){
		list->head = newNode(data);
		list->tail = list->head;
		return;
	}
	
	listNode* ins = newNode(data);
	list->tail->next = ins;
	ins->prev = list->tail;
	list->tail = ins;

}

void addNodeList(List* list,listNode* node){
	if(list == NULL){
		printf("Error: NULL list passed to addNodeList\n");
		return;
	}
	if(node == NULL){
		printf("Error: NULL node passed to addNodeList\n");
		return;
	}
	if(list->head == NULL){
		list->head = node;
		list->tail = node;
		return;
	}

	list->tail->next = node;
	node->prev = list->tail;
	list->tail = node;
}

listNode* searchList(List* list,void* data,int(*cmp)(void*,void*)){
	listNode* n = list->head;
	do {
		if(cmp(n->data,data))
			return n;
	}while((n = n->next) != NULL);
	return NULL;
}

void removeNode(List* list,void* data,int(*cmp)(void*,void*)){
	//TODO implement
}

void deleteList(List* list){
	listNode* n = list->tail;
	do {
		list->cleanNode(n->data);
		listNode* tbf = n;
		n = n->prev;
		free(tbf);
	}while(n != NULL);
}
