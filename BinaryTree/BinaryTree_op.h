#ifndef BinaryTree_H_
#define BinaryTree_H_
#include <stdlib.h>

typedef int ElementType;

typedef struct TreeNode {
    ElementType Element;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode, *Tree;

typedef enum {
    OK, ERROR, SPACE_OVERFLOW, BINARY_TREE_NULL,
    NODE_ALREADY_EXIST, VALUE_DONT_EXIT
} Status;

/* ========== 函数指针类型定义 ========== */

/**
 * 比较函数指针
 * 返回值: <0 表示 a < b, 0 表示 a == b, >0 表示 a > b
 */
typedef int (*CompareFunc)(ElementType a, ElementType b);

/**
 * 替换策略函数指针
 * 删除双子节点时，选择"前驱"或"后继"来替换
 * 参数为子树根指针的指针，返回被选中节点的指针的指针
 */
typedef struct TreeNode** (*FindReplacementFunc)(Tree* subtree);

/* ========== 默认比较函数 ========== */
int default_compare(ElementType a, ElementType b);

/* ========== 基础版（兼容旧接口） ========== */
Status BinaryTree_init(Tree* T);
Status BinaryTree_insert(Tree* T, ElementType e);
Status BinaryTree_delete(Tree* T, ElementType e, Tree parent);
Status BinaryTree_FindMin(Tree* T);
Status BinaryTree_FindMax(Tree* T);
Status BinaryTree_search(Tree T, ElementType e);
void   BinaryTree_preorder_print(Tree T);
void   BinaryTree_inorder_print(Tree T);
void   BinaryTree_postorder_print(Tree T);
size_t BinaryTree_get_depth(Tree T);
size_t BinaryTree_get_node_count(Tree T);

/* ========== 函数指针版（新增） ========== */

/* 使用自定义比较函数的插入 */
Status BinaryTree_insert_ex(Tree* T, ElementType e, CompareFunc cmp);

/* 使用自定义比较函数的删除 */
Status BinaryTree_delete_ex(Tree* T, ElementType e, CompareFunc cmp);

/* 使用自定义替换策略的删除（同时支持自定义比较） */
Status BinaryTree_delete_with_strategy(
    Tree* T, ElementType e,
    CompareFunc cmp,
    FindReplacementFunc strategy);

/* 使用自定义比较函数的查找 */
Status BinaryTree_search_ex(Tree T, ElementType e, CompareFunc cmp);

/* 前驱策略：找左子树中最大节点 */
struct TreeNode** find_predecessor(Tree* subtree);

/* 后继策略：找右子树中最小节点 */
struct TreeNode** find_successor(Tree* subtree);

#endif
