#include "queue_op.h"
#include <stdio.h>
status binary_tree_traverse_lever(BT T) {
    if(!T)  return TREE_IS_EMPTY;
    Queue q;
    if((queue_init(&q, 100)) != OK ) {
        fprintf(stderr, "Queue malloc error.\n");
        return MALLOC_ERROR;
    }
    queue_push(&q, T);
    while(queue_isempty(q) == NO) {
        BT tmp = queue_get_front(&q);
        if(tmp->left)
            queue_push(&q, tmp->left);
        if(tmp->right)
            queue_push(&q, tmp->right);
        BT curr = queue_get_front(&q);
        printf("%d",curr->val);
        if(queue_pop( &q) != OK)    break;
    }
    free(q);
    return OK;
}     