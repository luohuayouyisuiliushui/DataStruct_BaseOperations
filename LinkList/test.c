#include "LinkList.h"
#include <stdio.h>

void test_init_and_print() {
    printf("=== 测试1: 初始化和打印 ===\n");
    LinkList L = LinkList_init();
    printf("空链表: ");
    LinkList_print(L);
    LinkList_free(L);
    printf("\n");
}

void test_insert() {
    printf("=== 测试2: 插入操作（有序插入）===\n");
    LinkList L = LinkList_init();
    
    // 乱序插入，应该自动排序
    LinkList_insert(L, 5);
    LinkList_insert(L, 3);
    LinkList_insert(L, 8);
    LinkList_insert(L, 1);
    LinkList_insert(L, 6);
    
    printf("插入 5,3,8,1,6 后: ");
    LinkList_print(L);
    printf("期望结果: 1-->3-->5-->6-->8-->NULL\n\n");
    
    LinkList_free(L);
}

void test_delete() {
    printf("=== 测试3: 删除操作 ===\n");
    LinkList L = LinkList_init();
    
    // 先插入一些数据
    for (int i = 1; i <= 5; i++) {
        LinkList_insert(L, i * 10);
    }
    
    printf("初始链表: ");
    LinkList_print(L);
    
    // 删除第一个节点 (idx=0)
    LinkList_delete(L, 0);
    printf("删除 idx=0 后: ");
    LinkList_print(L);
    printf("期望: 20-->30-->40-->50-->NULL\n");
    
    // 删除中间节点 (idx=1)
    LinkList_delete(L, 1);
    printf("删除 idx=1 后: ");
    LinkList_print(L);
    printf("期望: 20-->40-->50-->NULL\n");
    
    // 删除最后一个节点 (idx=2)
    LinkList_delete(L, 2);
    printf("删除 idx=2 后: ");
    LinkList_print(L);
    printf("期望: 20-->40-->NULL\n");
    
    // 删除越界索引 (应该不改变链表)
    LinkList_delete(L, 100);
    printf("删除 idx=100(越界)后: ");
    LinkList_print(L);
    printf("期望: 20-->40-->NULL\n\n");
    
    LinkList_free(L);
}

void test_delete_empty() {
    printf("=== 测试4: 删除空链表 ===\n");
    LinkList L = LinkList_init();
    
    printf("空链表: ");
    LinkList_print(L);
    
    LinkList_delete(L, 0);
    printf("删除 idx=0 后: ");
    LinkList_print(L);
    printf("期望: NULL\n\n");
    
    LinkList_free(L);
}

void test_reverse() {
    printf("=== 测试5: 反转链表 ===\n");
    LinkList L = LinkList_init();
    
    // 插入数据
    LinkList_insert(L, 1);
    LinkList_insert(L, 2);
    LinkList_insert(L, 3);
    LinkList_insert(L, 4);
    LinkList_insert(L, 5);
    
    printf("反转前: ");
    LinkList_print(L);
    printf("期望: 1-->2-->3-->4-->5-->NULL\n");
    
    LinkList_reverse(L);
    printf("反转后: ");
    LinkList_print(L);
    printf("期望: 5-->4-->3-->2-->1-->NULL\n\n");
    
    LinkList_free(L);
}

void test_reverse_empty() {
    printf("=== 测试6: 反转空链表 ===\n");
    LinkList L = LinkList_init();
    
    printf("反转前: ");
    LinkList_print(L);
    
    LinkList_reverse(L);
    printf("反转后: ");
    LinkList_print(L);
    printf("期望: NULL\n\n");
    
    LinkList_free(L);
}

void test_single_node() {
    printf("=== 测试7: 单节点操作 ===\n");
    LinkList L = LinkList_init();
    
    LinkList_insert(L, 42);
    printf("插入单个节点后: ");
    LinkList_print(L);
    printf("期望: 42-->NULL\n");
    
    LinkList_delete(L, 0);
    printf("删除后: ");
    LinkList_print(L);
    printf("期望: NULL\n\n");
    
    LinkList_free(L);
}

void test_multiple_operations() {
    printf("=== 测试8: 综合操作 ===\n");
    LinkList L = LinkList_init();
    
    // 插入
    LinkList_insert(L, 10);
    LinkList_insert(L, 20);
    LinkList_insert(L, 30);
    printf("插入 10,20,30: ");
    LinkList_print(L);
    
    // 删除
    LinkList_delete(L, 1);
    printf("删除 idx=1: ");
    LinkList_print(L);
    
    // 再插入
    LinkList_insert(L, 15);
    LinkList_insert(L, 25);
    printf("插入 15,25: ");
    LinkList_print(L);
    
    // 反转
    LinkList_reverse(L);
    printf("反转后: ");
    LinkList_print(L);
    printf("\n");
    
    LinkList_free(L);
}

void test_large_list() {
    printf("=== 测试9: 大规模链表 ===\n");
    LinkList L = LinkList_init();
    
    // 插入100个元素
    for (int i = 100; i >= 1; i--) {
        LinkList_insert(L, i);
    }
    
    printf("插入100个元素后的前10个: ");
    LinkList p = L->next;
    for (int i = 0; i < 10 && p; i++) {
        printf("%d-->", p->data);
        p = p->next;
    }
    printf("...\n");
    printf("期望: 1-->2-->3-->...-->100-->NULL\n");
    
    // 删除一半
    for (int i = 0; i < 50; i++) {
        LinkList_delete(L, 0);
    }
    
    printf("删除前50个后: ");
    p = L->next;
    for (int i = 0; i < 10 && p; i++) {
        printf("%d-->", p->data);
        p = p->next;
    }
    printf("...\n");
    printf("期望: 51-->52-->53-->...-->100-->NULL\n\n");
    
    LinkList_free(L);
}

int main() {
    test_init_and_print();
    test_insert();
    test_delete();
    test_delete_empty();
    test_reverse();
    test_reverse_empty();
    test_single_node();
    test_multiple_operations();
    test_large_list();
    
    printf("所有测试完成！\n");
    return 0;
}
