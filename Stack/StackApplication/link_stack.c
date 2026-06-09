#include "link_stack.h"
#include <stdio.h>
status link_stack_init(LinkStack* s) {
	*s = NULL;
	return OK;
}
status link_stack_push(LinkStack* s, StackElemType e) {
	LinkStack node = (LinkStack)malloc(sizeof(StackNode));
	if(!node)	return MALLOC_ERROR;
	node->val = e;
	node->next = *s;
	*s = node;
	return OK;
}
status link_stack_pop(LinkStack* s) {
	if(!(*s))	return STACK_IS_EMPTY;
	LinkStack tmp = (*s)->next;
	free(*s);
	*s = tmp;
	return OK;
}
status link_stack_top(const LinkStack s, StackElemType* e) {
	if(!s)	return STACK_IS_EMPTY;
	*e = s->val;
	return OK;
}
ssize_t link_stack_get_length(const LinkStack s) {
	ssize_t idx = 0;
	if(!s)	return 0;
	LinkStack p = s;
	while(p) {
		idx++;
		p = p->next;
	}
	return idx;
}
void link_stack_print(LinkStack s, char* format) {
	if(!s)	return;
	while(s) {
		printf(format,s->val);
		printf("\n");
		s = s->next;
	}
}