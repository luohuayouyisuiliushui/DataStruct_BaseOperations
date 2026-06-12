#include "BST.h"
#include <stdio.h>

// 中序遍历：验证 BST 性质（升序输出即正确）
static void inorder(BST T) {
    if (!T) return;
    inorder(T->left);
    printf("%d ", T->val);
    inorder(T->right);
}

// 打印树的信息
static void printTree(BST T, const char* msg) {
    printf("%-30s [", msg);
    inorder(T);
    printf("]\n");
}

// 测试查找
static void testFind(BST T, ElemType e) {
    BST result = BST_find(T, e);
    printf("  查找 %d: %s\n", e, result ? "找到" : "未找到");
}

int main(void) {
    BST root = NULL;

    printf("========== BST 测试程序 ==========\n\n");

    // ---- 1. 插入测试 ----
    printf("--- 1. 插入测试 ---\n");
    int vals[] = {50, 30, 70, 20, 40, 60, 80, 35, 45};
    int n = sizeof(vals) / sizeof(vals[0]);
    for (int i = 0; i < n; i++) {
        printf("  插入 %d: %s\n", vals[i],
               BST_intsert(&root, vals[i]) == SUCCESS ? "成功" : "失败");
    }
    printTree(root, "构建的 BST (中序):");
    // 期望: 20 30 35 40 45 50 60 70 80

    // ---- 2. 插入重复值 ---
    printf("\n--- 2. 插入重复值测试 ---\n");
    printf("  插入重复值 50: %s\n",
           BST_intsert(&root, 50) == SUCCESS ? "成功" : "失败(预期)");

    // ---- 3. 查找测试 ----
    printf("\n--- 3. 查找测试 ---\n");
    testFind(root, 50);
    testFind(root, 20);
    testFind(root, 80);
    testFind(root, 35);
    testFind(root, 99);   // 不存在的值
    testFind(root, -1);   // 不存在的值

    // ---- 4. 删除叶子节点 ----
    printf("\n--- 4. 删除叶子节点 (20) ---\n");
    printf("  删除 20: %s\n",
           BST_delete(&root, 20) == SUCCESS ? "成功" : "失败");
    printTree(root, "删除后 (中序):");
    // 期望: 30 35 40 45 50 60 70 80

    // ---- 5. 删除只有一个孩子的节点 ----
    // 先插入 15，让 30 的右子树经删除后…这里用 60 为例
    // 删除 70 后，70 有右孩子 80，属于单孩子节点
    printf("\n--- 5. 删除只有一个孩子的节点 (70) ---\n");
    printf("  删除 70: %s\n",
           BST_delete(&root, 70) == SUCCESS ? "成功" : "失败");
    printTree(root, "删除后 (中序):");
    // 期望: 30 35 40 45 50 60 80

    // ---- 6. 删除有两个孩子的节点 ----
    printf("\n--- 6. 删除有两个孩子的节点 (30) ---\n");
    printf("  删除 30: %s\n",
           BST_delete(&root, 30) == SUCCESS ? "成功" : "失败");
    printTree(root, "删除后 (中序):");
    // 期望: 35 40 45 50 60 80

    // ---- 7. 删除根节点 ----
    printf("\n--- 7. 删除根节点 (50) ---\n");
    printf("  删除 50: %s\n",
           BST_delete(&root, 50) == SUCCESS ? "成功" : "失败");
    printTree(root, "删除后 (中序):");
    // 期望: 35 40 45 60 80

    // ---- 8. 删除不存在的值 ----
    printf("\n--- 8. 删除不存在的值 ---\n");
    printf("  删除 999: %s\n",
           BST_delete(&root, 999) == SUCCESS ? "成功" : "失败(预期)");

    // ---- 9. 连续删除直到空树 ----
    printf("\n--- 9. 连续删除直到空树 ---\n");
    int del_order[] = {35, 40, 45, 60, 80};
    n = sizeof(del_order) / sizeof(del_order[0]);
    for (int i = 0; i < n; i++) {
        printf("  删除 %d: %s\n", del_order[i],
               BST_delete(&root, del_order[i]) == SUCCESS ? "成功" : "失败");
        printTree(root, "  当前树:");
    }

    // ---- 10. 空树边界测试 ----
    printf("\n--- 10. 空树边界测试 ---\n");
    printf("  空树查找 50:\n");
    testFind(root, 50);
    printf("  空树删除 50: %s\n",
           BST_delete(&root, 50) == SUCCESS ? "成功" : "失败(预期)");
    // 空树再插入
    printf("  空树插入 100: %s\n",
           BST_intsert(&root, 100) == SUCCESS ? "成功" : "失败");
    printTree(root, "  当前树:");
    printf("  删除唯一节点 100: %s\n",
           BST_delete(&root, 100) == SUCCESS ? "成功" : "失败");
    printTree(root, "  当前树:");

    printf("\n========== 测试完毕 ==========\n");
    return 0;
}