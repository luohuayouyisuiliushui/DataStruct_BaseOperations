#ifndef _DL_H_
#define _DL_H_
#include<stdlib.h>
typedef int ElemType;
typedef struct ListNode {
	struct ListNode* pre;
	struct ListNode* next;
	ElemType val;
}*DL;
DL DL_init(void);
DL DL_insert(DL L, ElemType e);
DL DL_delete(DL L, size_t idx);
DL DL_reverse(DL L);
void DL_printf(DL L);
DL DL_destroy(DL L);
#endif
