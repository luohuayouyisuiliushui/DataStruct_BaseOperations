#include"dl.h"
#include<assert.h>
#include<stdio.h>
DL DL_init(DL L){
	assert(L == NULL);
	L = (DL)malloc(sizeof(struct ListNode));
	if(!L)	return NULL;
	L->pre = L;
	L->next = L;
	L->val = 0;
	return L;
}
static DL DL_creat_node(ElemType e){
	DL node = (DL)malloc(sizeof(struct ListNode));
	node->val = e;
	node->next = node;
	node->pre = node;
	return node;
}
DL DL_insert(DL L, ElemType e){
	DL p = L->next;
	DL node = DL_creat_node(e);
	while(p && e > p->val){
		p = p->next;
	}
	node->pre = p->pre;
	p->pre->next = node;
	node->next = p;
	return L;
}
DL DL_delete(DL L, size_t idx){
	DL p = L->next;
	for(int i = 0; i < idx; i++){
		if(p->next == L)	return NULL;
		p = p->next;
	}
	p->pre->next = p->next;
	p->next->pre = p->pre;
	free(p);
	return L;
}
DL DL_reverse(DL L){
	if(L->next == L || L->next->next == L)	return L;
	DL curr = L->next;
	L->pre = L->next;
	while(curr != L){
		DL tmp = curr->pre;
		curr->pre = curr->next;
		curr->next = tmp;
		curr = curr->pre;
	}
	DL tmp = L->pre;
	L->pre = L->next;
	L->next = tmp;
	return L;
}
void DL_printf(DL L){
	DL p = L->next;
	while(p != L){
		printf("%d-->",p->val);
		p = p->next;
	}
	printf("NULL\n");
	return;
}
