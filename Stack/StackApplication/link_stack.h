#ifndef LINK_STACK_H_
#define LINK_STACK_H_
#include <stdlib.h>
#include <sys/types.h>
typedef char StackElemType;
typedef struct StackNode {
	StackElemType val;
	struct StackNode* next;
}StackNode, *LinkStack;
typedef enum status {
	OK, 
	ERROR, 
	MALLOC_ERROR, 
	STACK_IS_EMPTY
}status;
status link_stack_init(LinkStack* s);
status link_stack_push(LinkStack* s, StackElemType e);
status link_stack_pop(LinkStack* s);
status link_stack_top(const LinkStack s, StackElemType* e);
ssize_t link_stack_get_length(const LinkStack s);
void link_stack_print(LinkStack s, char*format);
#endif