#include "linear_stack.h"
#include <sys/types.h>  // ssize_t
#define ERROR_VALUE do { if(!s || !s->base)	return INVALID_VALUE; } while(0)
enum status linear_stack_init(stack* s, size_t num) {
	num = num > 0 ? num : INIT_ELE_NUM;
	s->base = (ElemType*)malloc(num * sizeof(ElemType));
	if(!s->base)	return MALLOC_FALIURE;
	s->top = s->base;
	s->stack_size = num;
	return OK;
}
enum status linear_stack_isempty(const stack* s) {
	ERROR_VALUE;
	if(s->base == s->top)	return YES;
	else	return NO;
}
enum status linear_stack_clear(stack* s) {
	ERROR_VALUE;
	s->top = s->base;
	return	s->top == s->base ? OK : ERROR;
}
enum status linear_stack_free(stack* s) {
	ERROR_VALUE;
	free(s->base);
	s->top = s->base = NULL;
	s->stack_size = 0;
	return OK;
}
enum status linear_stack_push(stack* s, ElemType e) {
	ERROR_VALUE;
	if(s->top - s->base >= s->stack_size)	return STACK_OVER_SIZE;
	*s->top++ = e;
	return OK;
}
enum status linear_stack_pop(stack* s) {
	ERROR_VALUE;
	if(linear_stack_isempty(s) == YES)	return STACK_IS_EMPTY;
	s->top--;
	return OK;
}
ssize_t linear_stack_get_length(stack* s) {
	if(!s || !s->base)	return -1;
	return (ssize_t)(s->top - s->base);
}
ElemType linear_stack_get_top(stack* s) {
	if(!s || !s->base)	exit(EXIT_FAILURE);
	if(linear_stack_isempty(s) == YES)	exit(EXIT_FAILURE);
	return *(s->top - 1);
}
