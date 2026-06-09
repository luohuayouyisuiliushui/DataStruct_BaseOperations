#include "queue_op.h"
#define QUEUE_IDXADD(idx, max_size) do { (idx) = ((idx) + 1) % max_size; } while(0)
#define QUEUE_CHECK_ISNULL(q) do { if(!q || !(*q)->data) return QUEUE_IS_NULL; } while(0)
status queue_init(Queue* q, size_t max_size) {
    *q = (QueueNode*)malloc(sizeof(QueueNode));
    if(!*q) return MALLOC_ERROR;
    max_size = max_size > 0 ? max_size : QUEUE_MAX_SIZE;
    (*q)->data = (QueueElemType*)malloc(max_size * sizeof(QueueElemType));
    if((*q)->data == NULL){   
        free(*q);
        *q = NULL;
        return MALLOC_ERROR;
    }
    (*q)->front = (*q)->rear = 0;
    (*q)->max_size = max_size;
    return OK;
}
status queue_push(Queue*q, QueueElemType e) {
    QUEUE_CHECK_ISNULL(q);
    if(((*q)->rear + 1) % (*q)->max_size == (*q)->front)    return QUEUE_IS_FULL;
    (*q)->data[(*q)->rear] = e;
    QUEUE_IDXADD((*q)->rear, (*q)->max_size);
    return OK;
}
status queue_pop(Queue* q) {
    QUEUE_CHECK_ISNULL(q);  
    if((*q)->front == (*q)->rear)   return QUEUE_IS_EMPTY;
    QUEUE_IDXADD((*q)->front, (*q)->max_size);
    return OK;
}
QueueElemType queue_get_front(Queue* q) {
    QUEUE_CHECK_ISNULL(q);
    if((*q)->front == (*q)->rear)  {
        free(*q);
        *q = NULL;
        exit(EXIT_FAILURE);
    }
    return (*q)->data[(*q)->front];
}
status queue_destroy(Queue* q) {
    QUEUE_CHECK_ISNULL(q);
    if((*q)->data) {
        free((*q)->data);
        (*q)->data = NULL;
    }
    free(*q);
    *q = NULL;
    return OK;   
}
status queue_size(Queue q, size_t* size) {
    if(q == NULL || q->max_size == 0) return QUEUE_IS_NULL;
    *size = (q->rear + q->max_size - q->front) % q->max_size;
    return OK;
}