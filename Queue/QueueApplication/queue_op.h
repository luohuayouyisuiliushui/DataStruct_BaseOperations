#ifndef _QUEUE_OP_H_
#define _QUEUE_OP_H_
#define QUEUE_MAX_SIZE 100
#include <stdlib.h>
typedef int QueueElemType;
typedef struct QueueNode {
    QueueElemType* data;
    size_t front;
    size_t rear;
    size_t max_size;
} QueueNode, *Queue;
typedef enum {
    OK, ERROR, MALLOC_ERROR,QUEUE_IS_NULL, QUEUE_IS_FULL, QUEUE_IS_EMPTY
}status;
status queue_init(Queue* q, size_t max_size);
status queue_push(Queue* q, QueueElemType e);
status queue_pop(Queue* q);
QueueElemType queue_get_front(Queue* q);
status queue_destroy(Queue* q);
status queue_size(Queue q, size_t* size);
#endif