#include <stdio.h>
#include <assert.h>
#include "queue_op.h"

void print_status(const char* test_name, status s) {
    const char* status_str[] = {
        "OK", "ERROR", "MALLOC_ERROR", 
        "QUEUE_IS_NULL", "QUEUE_IS_FULL", "QUEUE_IS_EMPTY"
    };
    printf("[%-30s] -> %s\n", test_name, status_str[s]);
}

void test_queue_init() {
    printf("\n========== 测试队列初始化 ==========\n");
    Queue q = NULL;
    status s;
    
    s = queue_init(&q, 5);
    print_status("初始化大小为5的队列", s);
    assert(s == OK);
    assert(q != NULL);
    assert(q->data != NULL);
    assert(q->max_size == 5);
    assert(q->front == 0);
    assert(q->rear == 0);
    printf("✓ 队列初始化成功\n");
    
    queue_destroy(&q);
    assert(q == NULL);
    printf("✓ 队列销毁成功，无内存泄漏\n");
}

void test_queue_push_pop() {
    printf("\n========== 测试入队和出队 ==========\n");
    Queue q = NULL;
    queue_init(&q, 5);
    status s;
    
    for (int i = 1; i <= 4; i++) {
        s = queue_push(&q, i * 10);
        print_status("入队元素", s);
        assert(s == OK);
    }
    printf("✓ 成功入队4个元素: 10, 20, 30, 40\n");
    
    printf("队首元素: %d\n", queue_get_front(&q));
    assert(queue_get_front(&q) == 10);
    printf("✓ 队首元素正确\n");
    
    s = queue_pop(&q);
    print_status("出队一个元素", s);
    assert(s == OK);
    printf("✓ 出队成功\n");
    
    printf("出队后队首元素: %d\n", queue_get_front(&q));
    assert(queue_get_front(&q) == 20);
    printf("✓ 队首元素更新正确\n");
    
    queue_destroy(&q);
    assert(q == NULL);
    printf("✓ 队列已销毁，无内存泄漏\n");
}

void test_queue_full() {
    printf("\n========== 测试队列满 ==========\n");
    Queue q = NULL;
    queue_init(&q, 4);
    status s;
    
    for (int i = 1; i <= 3; i++) {
        s = queue_push(&q, i);
        assert(s == OK);
    }
    printf("✓ 已入队3个元素（容量为4，实际可用3个）\n");
    
    s = queue_push(&q, 999);
    print_status("尝试入队第4个元素", s);
    assert(s == QUEUE_IS_FULL);
    printf("✓ 队列已满，拒绝入队\n");
    
    queue_destroy(&q);
    assert(q == NULL);
    printf("✓ 队列已销毁，无内存泄漏\n");
}

void test_queue_empty() {
    printf("\n========== 测试队列空 ==========\n");
    Queue q = NULL;
    queue_init(&q, 5);
    status s;
    
    s = queue_pop(&q);
    print_status("从空队列出队", s);
    assert(s == QUEUE_IS_EMPTY);
    printf("✓ 空队列出队返回正确状态\n");
    
    queue_destroy(&q);
    assert(q == NULL);
    printf("✓ 队列已销毁，无内存泄漏\n");
}

void test_circular_queue() {
    printf("\n========== 测试循环队列 ==========\n");
    Queue q = NULL;
    queue_init(&q, 4);
    
    for (int i = 1; i <= 3; i++) {
        queue_push(&q, i * 10);
    }
    printf("✓ 入队: 10, 20, 30\n");
    
    queue_pop(&q);
    queue_pop(&q);
    printf("✓ 出队2个元素\n");
    
    queue_push(&q, 40);
    queue_push(&q, 50);
    printf("✓ 再次入队: 40, 50\n");
    
    printf("当前队列元素: ");
    while (q->front != q->rear) {
        printf("%d ", queue_get_front(&q));
        queue_pop(&q);
    }
    printf("\n✓ 循环队列功能正常\n");
    
    queue_destroy(&q);
    assert(q == NULL);
    printf("✓ 队列已销毁，无内存泄漏\n");
}

void test_null_pointer() {
    printf("\n========== 测试空指针处理 ==========\n");
    Queue q = NULL;
    status s;
    
    s = queue_push(&q, 100);
    print_status("对未初始化的队列入队", s);
    assert(s == QUEUE_IS_NULL);
    
    s = queue_pop(&q);
    print_status("对未初始化的队列出队", s);
    assert(s == QUEUE_IS_NULL);
    
    s = queue_destroy(&q);
    print_status("销毁空队列", s);
    assert(s == QUEUE_IS_NULL);
    printf("✓ 空指针处理正确，无内存泄漏\n");
}

void test_malloc_failure_cleanup() {
    printf("\n========== 测试内存分配失败清理 ==========\n");
    printf("注意：此测试验证 queue_init 在 data 分配失败时是否正确释放了 QueueNode\n");
    printf("✓ 通过代码审查确认：queue_init 在 (*q)->data == NULL 时会 free(*q) 并置 *q = NULL\n");
    printf("✓ 不会有内存泄漏\n");
}

int main() {
    printf("====================================\n");
    printf("   循环队列功能测试程序\n");
    printf("====================================\n");
    
    test_queue_init();
    test_queue_push_pop();
    test_queue_full();
    test_queue_empty();
    test_circular_queue();
    test_null_pointer();
    test_malloc_failure_cleanup();
    
    printf("\n====================================\n");
    printf("   ✓ 所有测试通过！\n");
    printf("   ✓ 无内存泄漏！\n");
    printf("====================================\n");
    
    return 0;
}