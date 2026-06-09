#include "BinaryTree_op.h"
#include <stdio.h>

/* ==================== 基础操作 ==================== */

/**
 * 初始化二叉树（置空）
 */
Status BinaryTree_init(Tree* T) {
    if (T == NULL) {
        return ERROR;
    }
    *T = NULL;
    return OK;
}

/**
 * 插入元素（BST 规则：左小右大）
 */
Status BinaryTree_insert(Tree* T, ElementType e) {
    if (T == NULL) {
        return ERROR;
    }

    /* 找到空位则创建新节点 */
    if (*T == NULL) {
        TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
        if (newNode == NULL) {
            return SPACE_OVERFLOW;
        }
        newNode->Element = e;
        newNode->left    = NULL;
        newNode->right   = NULL;
        *T = newNode;
        return OK;
    }

    if (e < (*T)->Element) {
        return BinaryTree_insert(&((*T)->left), e);
    } else if (e > (*T)->Element) {
        return BinaryTree_insert(&((*T)->right), e);
    } else {
        /* 相等，已存在 */
        return NODE_ALREADY_EXIST;
    }
}

/* ==================== 删除操作 ==================== */

/**
 * 在以 T 为根的树中找最小节点并返回其指针的指针
 * 用于删除时找后继
 */
static TreeNode** find_min_ptr(Tree* T) {
    if (T == NULL || *T == NULL) {
        return NULL;
    }
    if ((*T)->left == NULL) {
        return T;
    }
    return find_min_ptr(&((*T)->left));
}

/**
 * 删除元素 e
 * parent: 父节点（首次调用传 NULL）
 *
 * 删除逻辑：
 *   1. 叶子节点：直接删除
 *   2. 单子节点：用子节点替换
 *   3. 双子节点：用右子树最小值（后继）替换元素值，递归删除后继
 */
Status BinaryTree_delete(Tree* T, ElementType e, Tree parent) {
    (void)parent; /* 通过 Tree*（指针的指针）直接操作，无需显式使用 parent */
    if (T == NULL || *T == NULL) {
        return BINARY_TREE_NULL;
    }

    /* 查找要删除的节点 */
    if (e < (*T)->Element) {
        return BinaryTree_delete(&((*T)->left), e, *T);
    } else if (e > (*T)->Element) {
        return BinaryTree_delete(&((*T)->right), e, *T);
    }

    /* 找到目标节点 (*T) */
    TreeNode* target = *T;

    /* 情况1 + 情况2：叶子 或 单子节点 */
    if (target->left == NULL || target->right == NULL) {
        TreeNode* child = (target->left != NULL) ? target->left : target->right;
        *T = child;          /* 用子节点（或 NULL）替换 */
        free(target);
        return OK;
    }

    /* 情况3：双子节点 —— 找后继替换 */
    TreeNode** succPtr = find_min_ptr(&(target->right));
    TreeNode*  succ    = *succPtr;

    /* 将后继的值赋给目标节点 */
    target->Element = succ->Element;

    /* 删除后继节点（后继一定没有左子节点） */
    *succPtr = succ->right;
    free(succ);

    return OK;
}

/* ==================== 查找最值 ==================== */

Status BinaryTree_FindMin(Tree* T) {
    if (T == NULL || *T == NULL) {
        return BINARY_TREE_NULL;
    }
    Tree p = *T;
    while (p->left != NULL) {
        p = p->left;
    }
    printf("Min: %d\n", p->Element);
    return OK;
}

Status BinaryTree_FindMax(Tree* T) {
    if (T == NULL || *T == NULL) {
        return BINARY_TREE_NULL;
    }
    Tree p = *T;
    while (p->right != NULL) {
        p = p->right;
    }
    printf("Max: %d\n", p->Element);
    return OK;
}

/* ==================== 查找元素 ==================== */

Status BinaryTree_search(Tree T, ElementType e) {
    if (T == NULL) {
        return BINARY_TREE_NULL;
    }
    if (e < T->Element) {
        return BinaryTree_search(T->left, e);
    } else if (e > T->Element) {
        return BinaryTree_search(T->right, e);
    } else {
        printf("Found: %d\n", T->Element);
        return OK;
    }
}

/* ==================== 遍历 ==================== */

void BinaryTree_preorder_print(Tree T) {
    if (T == NULL) return;
    printf("%d ", T->Element);
    BinaryTree_preorder_print(T->left);
    BinaryTree_preorder_print(T->right);
}

void BinaryTree_inorder_print(Tree T) {
    if (T == NULL) return;
    BinaryTree_inorder_print(T->left);
    printf("%d ", T->Element);
    BinaryTree_inorder_print(T->right);
}

void BinaryTree_postorder_print(Tree T) {
    if (T == NULL) return;
    BinaryTree_postorder_print(T->left);
    BinaryTree_postorder_print(T->right);
    printf("%d ", T->Element);
}

/* ==================== 深度与节点数 ==================== */

size_t BinaryTree_get_depth(Tree T) {
    if (T == NULL) return 0;
    size_t leftDepth  = BinaryTree_get_depth(T->left);
    size_t rightDepth = BinaryTree_get_depth(T->right);
    return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
}

size_t BinaryTree_get_node_count(Tree T) {
    if (T == NULL) return 0;
    return BinaryTree_get_node_count(T->left)
         + BinaryTree_get_node_count(T->right) + 1;
}

/* =================================================================
 *                   函数指针版本（新增）
 * =================================================================
 *
 * 设计思路：
 *   通过函数指针将"比较规则"和"替换策略"从算法中解耦出来。
 *   基础版的删除函数内部硬编码了 < > == 运算符和"后继替换"策略，
 *   函数指针版允许调用者注入自定义行为，无需改动算法本身。
 *
 * 对比要点：
 *   - 基础版:  if (e < (*T)->Element)   // 硬编码 int 比较
 *   - 指针版:  if (cmp(e, (*T)->Element) < 0)  // 可注入任意比较
 *
 *   - 基础版删除双子节点: 固定用后继
 *   - 指针版删除双子节点: 可注入前驱/后继策略
 * ================================================================= */

/* ==================== 默认比较函数 ==================== */

/**
 * 默认的 int 比较，供 _ex 系列函数默认使用
 * 使用者可以仿照此签名写自己的比较函数（如字符串比较、结构体比较）
 */
int default_compare(ElementType a, ElementType b) {
    if (a < b) return -1;
    if (a > b) return  1;
    return 0;
}

/* ==================== 前驱 / 后继策略 ==================== */

/**
 * 找左子树最大节点 —— 前驱策略
 * 返回该节点指针的指针，方便直接修改父节点的指针
 */
struct TreeNode** find_predecessor(Tree* subtree) {
    if (subtree == NULL || *subtree == NULL) return NULL;
    if ((*subtree)->right == NULL) return subtree;
    return find_predecessor(&((*subtree)->right));
}

/**
 * 找右子树最小节点 —— 后继策略（与基础版内部相同）
 */
struct TreeNode** find_successor(Tree* subtree) {
    if (subtree == NULL || *subtree == NULL) return NULL;
    if ((*subtree)->left == NULL) return subtree;
    return find_successor(&((*subtree)->left));
}

/* ==================== 带函数指针的插入 ==================== */

/**
 * 用自定义比较函数插入
 *
 * 对比基础版 BinaryTree_insert：
 *   - 基础版:  if (e < (*T)->Element)          ← 硬编码 <
 *   - 指针版:  if (cmp(e, (*T)->Element) < 0)  ← 通过函数指针调用
 */
Status BinaryTree_insert_ex(Tree* T, ElementType e, CompareFunc cmp) {
    if (T == NULL || cmp == NULL) return ERROR;

    if (*T == NULL) {
        TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
        if (newNode == NULL) return SPACE_OVERFLOW;
        newNode->Element = e;
        newNode->left    = NULL;
        newNode->right   = NULL;
        *T = newNode;
        return OK;
    }

    int result = cmp(e, (*T)->Element);
    if (result < 0) {
        return BinaryTree_insert_ex(&((*T)->left), e, cmp);
    } else if (result > 0) {
        return BinaryTree_insert_ex(&((*T)->right), e, cmp);
    } else {
        return NODE_ALREADY_EXIST;
    }
}

/* ==================== 带函数指针的删除（后继策略） ==================== */

/**
 * 用自定义比较函数删除（默认后继替换策略）
 *
 * 对比基础版 BinaryTree_delete：
 *   基础版用 e < (*T)->Element 做比较，
 *   这里用 cmp(e, (*T)->Element) < 0。
 *   其余删除逻辑完全一致。
 */
Status BinaryTree_delete_ex(Tree* T, ElementType e, CompareFunc cmp) {
    if (T == NULL || *T == NULL || cmp == NULL) return BINARY_TREE_NULL;

    int result = cmp(e, (*T)->Element);

    if (result < 0) {
        return BinaryTree_delete_ex(&((*T)->left), e, cmp);
    } else if (result > 0) {
        return BinaryTree_delete_ex(&((*T)->right), e, cmp);
    }

    /* 找到目标 */
    TreeNode* target = *T;

    /* 叶子或单子 */
    if (target->left == NULL || target->right == NULL) {
        TreeNode* child = (target->left != NULL) ? target->left : target->right;
        *T = child;
        free(target);
        return OK;
    }

    /* 双子：用后继替换 */
    TreeNode** succPtr = find_successor(&(target->right));
    TreeNode*  succ    = *succPtr;
    target->Element    = succ->Element;
    *succPtr           = succ->right;
    free(succ);
    return OK;
}

/* ==================== 带函数指针的删除（可指定策略） ==================== */

/**
 * 终极版：自定义比较 + 自定义替换策略
 *
 * 第三个参数 strategy 决定了删除双子节点时用前驱还是后继。
 *   传 find_successor    → 后继替换（同基础版行为）
 *   传 find_predecessor  → 前驱替换
 *
 * 这就是函数指针的核心优势：算法骨架不变，具体策略可插拔。
 */
Status BinaryTree_delete_with_strategy(
        Tree* T, ElementType e,
        CompareFunc cmp,
        FindReplacementFunc strategy)
{
    if (T == NULL || *T == NULL || cmp == NULL || strategy == NULL) {
        return BINARY_TREE_NULL;
    }

    int result = cmp(e, (*T)->Element);

    if (result < 0) {
        return BinaryTree_delete_with_strategy(
                   &((*T)->left), e, cmp, strategy);
    } else if (result > 0) {
        return BinaryTree_delete_with_strategy(
                   &((*T)->right), e, cmp, strategy);
    }

    /* 找到目标 */
    TreeNode* target = *T;

    /* 叶子或单子 */
    if (target->left == NULL || target->right == NULL) {
        TreeNode* child = (target->left != NULL) ? target->left : target->right;
        *T = child;
        free(target);
        return OK;
    }

    /* 双子：用 strategy 函数指针决定替换策略
     *   - find_successor:   在右子树找最小节点
     *   - find_predecessor: 在左子树找最大节点
     */
    TreeNode** replPtr;
    if (strategy == find_successor) {
        replPtr = find_successor(&(target->right));
    } else {
        replPtr = find_predecessor(&(target->left));
    }

    TreeNode* replNode = *replPtr;
    target->Element    = replNode->Element;

    /* 替换节点最多有一个子节点，用其子节点替代 */
    TreeNode* replChild = (replNode->left != NULL)
                            ? replNode->left : replNode->right;
    *replPtr = replChild;
    free(replNode);
    return OK;
}

/* ==================== 带函数指针的查找 ==================== */

/**
 * 用自定义比较函数查找
 */
Status BinaryTree_search_ex(Tree T, ElementType e, CompareFunc cmp) {
    if (T == NULL) return BINARY_TREE_NULL;
    if (cmp == NULL) return ERROR;

    int result = cmp(e, T->Element);
    if (result < 0) {
        return BinaryTree_search_ex(T->left, e, cmp);
    } else if (result > 0) {
        return BinaryTree_search_ex(T->right, e, cmp);
    } else {
        printf("Found: %d\n", T->Element);
        return OK;
    }
}
