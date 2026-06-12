#include "BST.h"
#include <stdio.h>
static BST creatNode(BST node, ElemType e) {
    node = (BST)malloc(sizeof(TreeNode));
    node->val = e;
    node->left = node->right = NULL;
    return node;
}
static BST findMin(BST* T) {
    if(!T || !(*T)) {
        fprintf(stderr, "Tree is empty.\n");
        return NULL;
    }
    BST next = (*T)->left;
    BST curr = (*T);
    BST pre = NULL;
    while(next) {
        pre = curr;
        curr = next;
        next = next->left;
    }
    // [修改] 原: pre->left = NULL;
    // 问题1: pre 可能为 NULL (当 (*T) 即最小节点时) 导致空指针崩溃
    // 问题2: 丢失了最小节点的右子树 curr->right
    // pre->left = NULL;
    if(pre) {
        pre->left = curr->right;
    } else {
        (*T) = curr->right;
    }
    return curr;
}
static BST findMax(BST* T) {
    if(!T || !(*T)) {
        fprintf(stderr, "Tree is empty.\n");
        return NULL;
    }
    BST next = (*T)->right;
    BST curr = (*T);
    BST pre = NULL;
    while(next) {
        pre = curr;
        curr = next;
        next = next->right;
    }
    // [修改] 原: pre->right = NULL;
    // 问题1: pre 可能为 NULL (当 (*T) 即最大节点时) 导致空指针崩溃
    // 问题2: 丢失了最大节点的左子树 curr->left
    // pre->right = NULL;
    if(pre) {
        pre->right = curr->left;
    } else {
        (*T) = curr->left;
    }
    return curr;
}
typedef enum flag{
    L, R
}flag;
status BST_intsert(BST* T, ElemType e) {
    BST node;
    int flag;
    node = creatNode(node, e);
    if(!T || !(*T)) {
        (*T) = node;
        return SUCCESS;
    }
    BST p = *T, pre = NULL;
    while(p) {
        if(p->val < e) {
            flag = R;
            pre = p;
            p = p->right;
        }
        else if(p->val > e) {
            flag = L;
            pre = p;
            p = p->left;
        }
        else{
            free(node);
            fprintf(stderr, "Value already exists.\n");
            return FAILURE;
        }
    }
    // [修改] 原: BST tmp = flag == L ? pre->left : pre->right; tmp = node;
    // 问题: tmp 是局部指针副本，对 tmp 赋值不会修改树结构，新节点实际未挂入树中
    // BST tmp = flag == L ? pre->left : pre->right;
    // tmp = node;
    if(flag == L)
        pre->left = node;
    else
        pre->right = node;
    return SUCCESS;
}
BST BST_find(const BST T, ElemType e) {
    BST p = T;
    while(p) {
        if(p->val < e)
            p = p->right;
        else if(p->val > e)
            p = p->left;
        else
            return p;
    }
    fprintf(stderr, "Value not exists.\n");
    return NULL;
}
status BST_delete(BST* T, ElemType e) {
    if(!T || !(*T)){
        fprintf(stderr, "Tree is empty.\n");
        return FAILURE;
    }
    BST p = (*T);
    BST pre = NULL;
    int flag;
    while(p) {
        if(p->val < e){  
            flag = R;
            pre = p;
            p = p->right;
        }
        else if(p->val > e) {
            flag = L;
            pre = p;
            p = p->left;
        }
        else{
            // ---- 找到目标节点 p ----
            if(!p->left && !p->right){
                // [修改] 原: free(p); p = NULL;
                // 问题: p 是局部指针, p=NULL 不更新父节点, 父节点仍指向已释放内存(悬垂指针)
                // free(p);
                // p = NULL;
                if(pre == NULL)
                    *T = NULL;
                else if(flag == L)
                    pre->left = NULL;
                else
                    pre->right = NULL;
                free(p);
                return SUCCESS;
            }
            if(p->right) {
                BST new_root = findMin(&p->right);
                // [修改] 原: BST tmp = flag == L ? pre->left : pre->right; tmp = new_root;
                // 问题1: 修改局部副本, 新根未挂入树中
                // 问题2: 未将原节点左右子树挂接到新根
                // 问题3: 未 free(p) (内存泄漏)
                new_root->left  = p->left;    // [修改] 挂接左子树
                new_root->right = p->right;   // [修改] 挂接右子树
                if(pre == NULL)
                    *T = new_root;            // [修改] 更新根
                else if(flag == L)
                    pre->left = new_root;     // [修改] 直接修改父节点指针
                else
                    pre->right = new_root;
                // BST new_root = findMin(&p->right);
                // BST tmp = flag == L ? pre->left : pre->right;
                // tmp = new_root;
                free(p);
                return SUCCESS;
            }
            if(p->left) {
                BST new_root = findMax(&p->left);
                // [修改] 原: BST tmp = flag == L ? pre->left : pre->right; tmp = new_root;
                // 问题同上: 局部副本、未挂接子树、内存泄漏
                new_root->left  = p->left;    // [修改] 挂接左子树
                new_root->right = p->right;   // [修改] 挂接右子树
                if(pre == NULL)
                    *T = new_root;            // [修改] 更新根
                else if(flag == L)
                    pre->left = new_root;     // [修改] 直接修改父节点指针
                else
                    pre->right = new_root;
                // BST new_root = finMax(&p->left);
                // BST tmp = flag == L ? pre->left : pre->right;
                // tmp = new_root;
                free(p);
                return SUCCESS;
            }
        }
    }
    fprintf(stderr, "Value not exists.\n");
    return FAILURE;
}