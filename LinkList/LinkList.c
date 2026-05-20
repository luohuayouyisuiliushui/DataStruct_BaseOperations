#include "LinkList.h"
#include <stdio.h>
LinkList LinkList_init(void){
	LinkList L = (LinkList)malloc(sizeof(ListNode));
	L->next = NULL;
	L->data = 0;
	return L;
}
static LinkList LinkList_creat_node(ElemType data){
	LinkList p = (LinkList)malloc(sizeof(ListNode));
	p->next = NULL;
	p->data = data;
	return p;
}
LinkList LinkList_insert(LinkList L, ElemType data){
	LinkList node = LinkList_creat_node(data);
	LinkList p = L;
	while(p->next && p->next->data < data){
		p = p->next;
	}
	node->next = p->next;
	p->next = node;
	return L;
}
LinkList LinkList_delete(LinkList L, size_t idx){
	LinkList p = L;
	if(!p || !p->next)	return L;
	for(int i = 0; i < idx && p->next; i++){
		p = p->next;
		if(!p)	return NULL;
	}
	if(!p->next)	return L;
	LinkList tmp = p->next;
	p->next = p->next->next;
	free(tmp);
	return L;
}
LinkList LinkList_reverse(LinkList L){
	LinkList p = L->next, head = NULL;
	while(p){
		LinkList next = p->next;
		p->next = head;
		head = p;
		p = next;
	}
	L->next = head;
	return L;
}
const status LinkList_free(LinkList L){
	LinkList p = L, pre = NULL;
	while(p){
		pre = p;
		p = p->next;
		free(pre);
	}
	return OK;
}
void LinkList_print(const LinkList L){
	LinkList p = L->next;
	while(p){
		printf("%d-->",p->data);
		p = p->next;
	}
	printf("NULL\n");
}
