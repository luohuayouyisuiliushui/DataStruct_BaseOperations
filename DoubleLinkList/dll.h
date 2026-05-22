#ifndef DLL_H_
#define DLL_H_
#include<stdlib.h>
typedef int ElemType;
typedef enum status{
	OK,
	ERROR
}status;
typedef struct DoubleLinkList {
	struct DoubleLinkList* prev;
	struct DoubleLinkList* next;
	ElemType val;
}DLN,*DLL;
/*
1.初始化双链表
2.插入元素
3.删除元素
4.反转双链表
5.释放双链表
6.打印双链表
*/
DLL DLL_init(void);
status DLL_insert(DLL* L, ElemType data);
status DLL_delete(DLL* L, size_t idx);
status DLL_reverse(DLL* L);
status DLL_free(DLL L);
void DLL_print(DLL L);
#endif 
