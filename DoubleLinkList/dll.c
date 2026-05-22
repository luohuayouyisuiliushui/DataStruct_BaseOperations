#include "dll.h"
#include <stdio.h>
#define MALLOCERROR do { printf("分配内存失败\n");\
return NULL; } while(0)
DLL DLL_init(void) {
	DLL L = (DLL)malloc(sizeof(DLN));
	if(!L) MALLOCERROR;
	L->val = 0;
	L->prev = L;
	L->next = L;
	return L;
}

static DLL DLL_creat_node(ElemType e) {
	DLL node = (DLL)malloc(sizeof(DLN));
	if(!node)	MALLOCERROR;
	node->val = e;
	node->next = NULL;
	node->prev = NULL;
	return node;
}

enum status DLL_insert(DLL* L, ElemType e) {
	if(!L)	return ERROR;
	if(!*L)	*L = DLL_init();
	if(!*L)	return ERROR;
	DLL node = DLL_creat_node(e);
	if(node == NULL)	return ERROR;
	DLL p = *L;
	if(p->next == p) {
		p->next = node;
		p->prev = node;
		node->next = p;
		node->prev = p;
		return OK;
	}
	while(p->next != *L && p->next->val < e) 
		p = p->next;	
	DLL next  = p->next;
	p->next = node;
	node->next = next;
	node->prev = p;
	next->prev = node;
	return OK;
}

enum status DLL_delete(DLL* L, size_t idx) {
	if(idx < 0)
		return ERROR;
	if(!L || !*L || (*L)->next == *L) 
		return ERROR;

	DLL p = *L;
	for(size_t i = 0; i < idx && p->next != *L; i++) {
		p = p->next;
	}
	if(p->next == *L) 
		return ERROR;
	DLL tmp = p->next;
	p->next = tmp->next;
	tmp->next->prev = p;
	free(tmp);
	tmp = NULL;
	return OK;
}
enum status DLL_reverse(DLL* L) {
	if(!L || !*L || (*L)->next == *L)	return ERROR;
	DLL head = *L;
	DLL p = head;
	do {
		DLL tmp = p->next;
		p->next = p->prev;
		p->prev = tmp;
		p = tmp;
	} while(p != head);
	return OK;
}
enum status DLL_free(DLL L) {
	DLL pre = L;
	DLL p = NULL;
	do {
		p = pre->next;
		free(pre);
		pre = p;
	} while(p != L);
	pre = NULL;
	return OK;
}
void DLL_print(DLL L) {
	DLL p = L->next;
	while(p != L) {
		printf("%d-->", p->val);
		p = p->next;
	}
	printf("NULL\n");
}