#ifndef LINEAR_STACK_H_
#define LINEAR_STACK_H_
#include <stdlib.h>
#define INIT_ELE_NUM 16 
typedef int ElemType;
typedef struct {
	ElemType* base;
	ElemType* top;
	size_t stack_size;
}stack;
enum status {
	OK,
	ERROR,
	MALLOC_FALIURE,
	INVALID_VALUE,
	YES,
	NO,
	STACK_OVER_SIZE,
	STACK_IS_EMPTY
};
enum status linear_stack_init(stack* s, size_t num);
enum status linear_stack_isempty(const stack* s);
enum status linear_stack_clear(stack* s);
enum status linear_stack_free(stack* s);
enum status linear_stack_push(stack* s, ElemType e);
enum status linear_stack_pop(stack* s);
ssize_t linear_stack_get_length(stack* s);
ElemType linear_stack_get_top(stack* s);
#endif
