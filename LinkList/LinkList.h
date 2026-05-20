#ifndef LINKLIST_H_
#define LINKLIST_H_
#include <stdlib.h>
typedef int ElemType;
typedef struct ListNode {
	struct ListNode* next;
	ElemType data;
}ListNode, *LinkList;
typedef enum{
	OK,
	ERROR
}status;
LinkList LinkList_init(void);
LinkList LinkList_insert(LinkList L, ElemType data);
LinkList LinkList_delete(LinkList L, size_t idx);
LinkList LinkList_reverse(LinkList L);
void LinkList_print(const LinkList L);
const status LinkList_free(LinkList L);

#endif 
