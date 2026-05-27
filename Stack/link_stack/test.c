// test_link_stack.c
#include <stdio.h>
#include "link_stack.h"

void print_separator(const char* msg) {
    printf("\n========== %s ==========\n", msg);
}

int main() {
    LinkStack stack;
    status ret;
    ssize_t len;
    int top_val;

    // 1. 初始化栈
    print_separator("初始化栈");
    ret = link_stack_init(&stack);
    if (ret == OK) {
        printf("栈初始化成功。\n");
    } else {
        printf("栈初始化失败！\n");
        return -1;
    }

    // 2. 获取空栈长度
    len = link_stack_get_length(stack);
    printf("空栈长度 = %zd\n", len);  // 预期 -1 (按当前实现)

    // 3. 入栈若干元素
    print_separator("入栈 10, 20, 30");
    ret = link_stack_push(&stack, 10);
    ret = link_stack_push(&stack, 20);
    ret = link_stack_push(&stack, 30);
    if (ret == OK) {
        printf("入栈成功。\n");
    } else {
        printf("入栈失败！\n");
    }

    // 4. 打印栈内容（从栈顶到栈底）
    print_separator("打印栈（栈顶 -> 栈底）");
    link_stack_print(stack, "栈中元素: %d");

    // 5. 获取栈长度
    len = link_stack_get_length(stack);
    printf("当前栈长度 = %zd\n", len);  // 按当前实现预期为 2? 实际应为3，但实现有bug

    // 6. 取栈顶元素
    top_val = link_stack_top(stack);
    printf("栈顶元素 = %d\n", top_val);  // 预期 30

    // 7. 弹出一个元素
    print_separator("弹出栈顶元素");
    ret = link_stack_pop(&stack);
    if (ret == OK) {
        printf("弹出成功。\n");
    } else if (ret == STACK_IS_EMPTY) {
        printf("栈为空，无法弹出。\n");
    } else {
        printf("弹出失败。\n");
    }

    // 8. 再次打印和取栈顶
    printf("\n弹出后的栈内容:\n");
    link_stack_print(stack, "%d");
    top_val = link_stack_top(stack);
    printf("新的栈顶元素 = %d\n", top_val);  // 预期 20

    // 9. 继续弹出所有元素
    print_separator("弹出所有剩余元素");
    while (stack != NULL) {
        ret = link_stack_pop(&stack);
        if (ret == OK) {
            printf("弹出成功，当前栈%s空\n", stack == NULL ? "已" : "未");
        }
    }

    // 10. 尝试从空栈弹出
    ret = link_stack_pop(&stack);
    if (ret == STACK_IS_EMPTY) {
        printf("尝试从空栈弹出：正确返回 STACK_IS_EMPTY\n");
    }

    // 11. 尝试取空栈栈顶（会触发 exit，所以注释掉演示）
    // printf("试图取空栈栈顶...\n");
    // top_val = link_stack_top(stack);  // 程序会退出

    // 12. 释放栈（实际上所有节点已弹出，无需额外释放）
    printf("\n测试结束。\n");
    return 0;
}
