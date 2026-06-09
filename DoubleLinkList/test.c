#include <stdio.h>
#include "dll.h"

// 辅助函数：打印测试标题
static void test_header(const char* msg) {
    printf("\n========== %s ==========\n", msg);
}

// 测试1：空链表操作
void test_empty_list() {
    test_header("空链表测试");
    DLL list = NULL;

    printf("尝试删除索引0 (应失败): ");
    DLL_delete(&list, 0);

    printf("尝试反转: ");
    DLL_reverse(&list);
    DLL_print(list);  // 应打印 NULL（空）

    printf("释放空链表: ");
    DLL_free(list);
    list = NULL;
    printf("完成\n");
}

// 测试2：插入元素（有序）
void test_insert_ordered() {
    test_header("插入测试（保持升序）");
    DLL list = NULL;

    int nums[] = {5, 2, 8, 1, 9, 3};
    for (int i = 0; i < 6; i++) {
        DLL_insert(&list, nums[i]);
        printf("插入 %d 后: ", nums[i]);
        DLL_print(list);
    }

    // 释放
    DLL_free(list);
}

// 测试3：删除元素（按索引）
void test_delete_by_index() {
    test_header("删除测试（按索引）");
    DLL list = NULL;

    // 先插入 1 2 3 4 5
    for (int i = 1; i <= 5; i++) {
        DLL_insert(&list, i);
    }
    printf("初始链表: ");
    DLL_print(list);  // 应为 1 2 3 4 5

    // 删除头索引0
    printf("删除索引0: ");
    DLL_delete(&list, 0);
    DLL_print(list);  // 2 3 4 5

    // 删除尾索引3（此时长度4，最大索引3）
    printf("删除索引3: ");
    DLL_delete(&list, 3);
    DLL_print(list);  // 2 3 4

    // 删除中间索引1
    printf("删除索引1: ");
    DLL_delete(&list, 1);
    DLL_print(list);  // 2 4

    // 尝试越界删除
    printf("尝试删除索引5 (越界): ");
    DLL_delete(&list, 5);
    DLL_print(list);  // 2 4

    // 删除所有元素
    printf("删除索引0: ");
    DLL_delete(&list, 0);
    DLL_print(list);  // 4
    printf("删除索引0: ");
    DLL_delete(&list, 0);
    DLL_print(list);  // 空

    DLL_free(list);
}

// 测试4：反转链表
void test_reverse() {
    test_header("反转测试");
    DLL list = NULL;

    // 空链表反转
    printf("空链表反转: ");
    DLL_reverse(&list);
    DLL_print(list);

    // 单元素链表反转
    DLL_insert(&list, 10);
    printf("原链表(单元素): ");
    DLL_print(list);
    DLL_reverse(&list);
    printf("反转后: ");
    DLL_print(list);  // 仍为 10

    // 多元素链表反转
    DLL_insert(&list, 20);
    DLL_insert(&list, 30);
    DLL_insert(&list, 5);
    // 当前有序: 5 10 20 30
    printf("原链表(有序): ");
    DLL_print(list);
    DLL_reverse(&list);
    printf("反转后: ");
    DLL_print(list);  // 应为 30 20 10 5

    // 再次反转应恢复原序
    DLL_reverse(&list);
    printf("再次反转: ");
    DLL_print(list);  // 5 10 20 30

    DLL_free(list);
}

// 测试5：混合操作（插入、删除、反转交叉）
void test_mixed_operations() {
    test_header("混合操作测试");
    DLL list = NULL;

    DLL_insert(&list, 3);
    DLL_insert(&list, 1);
    DLL_insert(&list, 4);
    DLL_insert(&list, 2);
    printf("插入1,2,3,4后: ");
    DLL_print(list);  // 1 2 3 4

    DLL_reverse(&list);
    printf("反转: ");
    DLL_print(list);  // 4 3 2 1

    DLL_delete(&list, 1);  // 删除索引1（原3）
    printf("删除索引1: ");
    DLL_print(list);  // 4 2 1

    DLL_insert(&list, 5);
    printf("插入5: ");
    DLL_print(list);  // 插入后有序应为 1 2 4 5? 注意插入函数保持升序，所以插入5后链表变为 1 2 4 5
    // 但当前链表是4 2 1（无序？实际上反转后链表是逆序，插入函数遍历时按值比较，仍会插入到正确位置）
    // 插入5后：遍历p从哨兵开始，p->next->val 依次为4,2,1，找到大于5的没有，则插入尾部，即4 2 1 5？不对，哨兵循环，实际顺序是4 2 1 5
    // 因为插入时 while(p->next != *L && p->next->val < e) 对于逆序的链表，p->next->val 依次为4,2,1,都比5小，所以最终插入到1之后，即顺序为4 2 1 5
    // 所以打印结果应为 4 2 1 5 (并非升序整体)。这是符合实现的：插入保持升序是基于当前链表顺序的，链表本身可能无序（反转后），但插入依然维持有序性质。
    // 为了清晰，我们只观察结果。
    DLL_print(list);

    DLL_reverse(&list);
    printf("再次反转: ");
    DLL_print(list);  // 5 1 2 4

    DLL_free(list);
}

// 测试6：多次创建释放（验证内存泄漏，手动检查或借助工具）
void test_create_free_many() {
    test_header("多次创建释放测试");
    for (int i = 0; i < 3; i++) {
        DLL list = NULL;
        for (int j = 0; j < 100; j++) {
            DLL_insert(&list, j % 10);
        }
        DLL_print(list);  // 只打印最后一次的短链表，避免输出过长
        DLL_free(list);
        printf("第%d轮创建释放完成\n", i+1);
    }
}

int main() {
    test_empty_list();
    test_insert_ordered();
    test_delete_by_index();
    test_reverse();
    test_mixed_operations();
    test_create_free_many();

    printf("\n========== 所有测试执行完毕 ==========\n");
    return 0;
}
