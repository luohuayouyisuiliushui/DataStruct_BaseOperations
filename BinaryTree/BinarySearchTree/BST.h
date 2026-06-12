#ifndef BST_H
#define BST_H

#include <stdlib.h>

typedef int ElemType;
typedef struct TreeNode {
    ElemType val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode, *BST;

typedef enum {
    SUCCESS = 0,
    FAILURE = -1
} status;

status BST_intsert(BST* T, ElemType e);
BST BST_find(const BST T, ElemType e);
status BST_delete(BST* T, ElemType e);

#endif