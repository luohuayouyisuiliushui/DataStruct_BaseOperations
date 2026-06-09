#include "queue_op.h"
#include <stdio.h>

//n = q队列中元素个数，每间隔m个数删除一个元素
//这个函数实现的是约瑟夫环问题，返回最后剩下的元素在原来队列中的位置
size_t fun(size_t m, size_t n) {
    if(n == 1)   return 0;
    return (fun(m, n-1)+ m ) % n;
}

size_t josephus(Queue* q, size_t m) {
    size_t size;
    if(queue_size(*q, &size) == QUEUE_IS_NULL || size == 0) {
        fprintf(stderr, "Queue is null.\n");
        exit(EXIT_FAILURE);
    }
    if(size == 1)
        return 0;
    if(queue_pop(q) == QUEUE_IS_EMPTY) {
        fprintf(stderr, "Queue is empty.\n");
        exit(EXIT_FAILURE);
    }
    return (josephus(q, m) + m ) % size;
}