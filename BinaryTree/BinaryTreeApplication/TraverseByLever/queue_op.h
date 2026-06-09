#ifndef _QUEUE_OP_H_
#define _QUEUE_OP_H_
#define QUEUE_MAX_SIZE 100
#include <stdlib.h>
typedef int  ElemType;
typedef struct BinaryTree {
    ElemType val;
    struct BinaryTree* left;
    struct BinaryTree* right;
}*BT;
typedef BT QueueElemType;
typedef struct QueueNode {
    QueueElemType* data;
    size_t front;
    size_t rear;
    size_t max_size;
} QueueNode, *Queue;
typedef enum {
    OK, ERROR, YES, NO, MALLOC_ERROR,QUEUE_IS_NULL, QUEUE_IS_FULL, QUEUE_IS_EMPTY, TREE_IS_EMPTY
}status;
status queue_init(Queue* q, size_t max_size);
status queue_push(Queue* q, QueueElemType e);
status queue_pop(Queue* q);
QueueElemType queue_get_front(Queue* q);
status queue_destroy(Queue* q);
status queue_isempty(Queue q);
#endif