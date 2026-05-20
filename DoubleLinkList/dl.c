#include "dl.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h> // 确保包含 malloc 和 free 的头文件
#include <stddef.h>
// 1. 初始化双链表
DL DL_init(void) {
    DL L = (DL)malloc(sizeof(struct ListNode));
    if (!L) return NULL; // 增加内存分配失败检查
    L->next = L->pre = NULL; // 修改 prev 为 pre
    return L;
}

// 2. 插入节点
DL DL_insert(DL L, ElemType e) {
    DL p = (DL)malloc(sizeof(struct ListNode));
    if (!p) return L; // 增加内存分配失败检查
    p->val = e;       // 修改 data 为 val
    p->next = L->next;
    p->pre = L;       // 修改 prev 为 pre
    if (L->next) {    // 如果原链表不为空，需要更新原第一个节点的 pre 指针
        L->next->pre = p; // 修改 prev 为 pre
    }
    L->next = p;
    return L;
}

// 3. 删除节点
DL DL_delete(DL L, size_t idx) {
    if (!L || !L->next) return L;
    
    DL p = L->next;
    size_t current_idx = 0;
    
    while (p && current_idx < idx) {
        p = p->next;
        current_idx++;
    }
    
    if (!p) {
        return L; // 索引超出范围
    }
    
    p->pre->next = p->next;
    if (p->next) {
        p->next->pre = p->pre;
    }
    free(p);
    return L;
}

// 4. 反转双链表
DL DL_reverse(DL L) {
    if (!L || !L->next) return L;
    
    DL p = L->next, q = NULL, r = NULL;
    DL tail = p; // 记录原第一个节点（反转后成为尾节点）
    
    while (p) {
        r = p->next;
        p->next = q;
        p->pre = r;
        q = p;
        p = r;
    }
    
    L->next = q;
    if (q) {
        q->pre = L;
    }
    
    // 修正尾节点的 pre 指针
    if (tail) {
        tail->pre = NULL;
    }
    
    return L;
}

// 5. 打印双链表
void DL_printf(DL L) {
    DL p = L->next;
    while (p) {
        printf("%d ", p->val); // 修改 data 为 val
        p = p->next;
    }
    printf("\n");
}

// 6. 销毁双链表
DL DL_destroy(DL L) {
    DL p = L->next, q = NULL;
    while (p) {
        q = p->next;
        free(p);
        p = q;
    }
    free(L);
    return NULL;
}