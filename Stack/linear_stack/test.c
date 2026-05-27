#include "linear_stack.h"
#include <stdio.h>
#include <sys/types.h>
/*
1. 初始化
1.1 失败（分配空间太多）
1.2 传入NULL

2. 清空stack
2.1 传入NULL
2.2 s->base == NULL

3. 判空
3.1 传入NULL

4.释放stack

*/

/**
 * 测试程序：顺序栈（线性栈）功能验证
 * 编译：gcc -o test_stack linear_stack.c test_stack.c
 * 运行：./test_stack
 */

// 打印栈内所有元素（从栈底到栈顶）
void print_stack(stack* s) {
	if (!s || !s->base) {
		printf("栈未初始化或已释放\n");
		return;
	}
	ssize_t len = linear_stack_get_length(s);
	if (len <= 0) {
		printf("栈为空\n");
		return;
	}
	printf("栈内容（底 -> 顶）：");
	for (ElemType* p = s->base; p < s->top; p++) {
		printf("%d ", *p);
	}
	printf("\n");
}

int main() {
	stack st;          // 定义栈结构
	enum status ret;
	ssize_t len;
	
	// 1. 初始化栈（容量为5）
	printf("=== 初始化栈，容量=5 ===\n");
	ret = linear_stack_init(&st, 5);
	if (ret != OK) {
		printf("初始化失败，错误码：%d\n", ret);
		return -1;
	}
	printf("初始化成功\n");
	
	// 2. 检查是否为空
	printf("\n=== 检查是否为空 ===\n");
	ret = linear_stack_isempty(&st);
	printf("栈是否为空？%s\n", (ret == YES) ? "是" : "否");
	
	// 3. 入栈元素 10, 20, 30, 40, 50
	printf("\n=== 入栈 10,20,30,40,50 ===\n");
	for (int i = 1; i <= 5; i++) {
		ret = linear_stack_push(&st, i * 10);
		if (ret != OK) {
			printf("入栈 %d 失败，错误码：%d\n", i * 10, ret);
		} else {
			printf("入栈 %d 成功\n", i * 10);
		}
	}
	
	// 尝试压入第6个元素（应失败）
	printf("\n=== 尝试入栈 60（超出容量）===\n");
	ret = linear_stack_push(&st, 60);
	if (ret == STACK_OVER_SIZE)
		printf("预期错误：栈已满，无法入栈\n");
	else
		printf("意外返回值：%d\n", ret);
	
	// 4. 获取栈顶元素
	printf("\n=== 获取栈顶元素 ===\n");
	ElemType top_val = linear_stack_get_top(&st);
	printf("栈顶元素为：%d\n", top_val);
	
	// 5. 获取栈长度
	printf("\n=== 获取栈长度 ===\n");
	len = linear_stack_get_length(&st);
	printf("当前栈长度：%zd\n", len);
	
	// 6. 打印全部元素
	printf("\n=== 打印栈内容 ===\n");
	print_stack(&st);
	
	// 7. 弹出一个元素
	printf("\n=== 弹出栈顶元素 ===\n");
	ret = linear_stack_pop(&st);
	if (ret == OK) {
		printf("弹出成功\n");
		printf("新的栈顶元素：%d\n", linear_stack_get_top(&st));
		printf("栈长度变为：%zd\n", linear_stack_get_length(&st));
		print_stack(&st);
	} else {
		printf("弹出失败，错误码：%d\n", ret);
	}
	
	// 8. 连续弹出所有元素
	printf("\n=== 连续弹出至空栈 ===\n");
	while (linear_stack_isempty(&st) != YES) {
		linear_stack_pop(&st);
	}
	printf("栈已空，长度：%zd\n", linear_stack_get_length(&st));
	print_stack(&st);
	
	// 9. 尝试从空栈弹出（应失败）
	printf("\n=== 尝试从空栈弹出 ===\n");
	ret = linear_stack_pop(&st);
	if (ret == STACK_IS_EMPTY)
		printf("预期错误：栈为空，无法弹出\n");
	
	// 10. 清空栈（空栈清空依然成功）
	printf("\n=== 清空栈 ===\n");
	ret = linear_stack_clear(&st);
	printf("清空结果：%s\n", (ret == OK) ? "成功" : "失败");
	
	// 11. 释放栈内存
	printf("\n=== 释放栈 ===\n");
	ret = linear_stack_free(&st);
	if (ret == OK) {
		printf("释放成功，栈结构已置空\n");
	}
	
	// 12. 测试释放后操作（应返回 INVALID_VALUE）
	printf("\n=== 释放后再调用函数 ===\n");
	ret = linear_stack_isempty(&st);
	printf("isempty 返回值：%d (预期 %d)\n", ret, INVALID_VALUE);
#ifdef _WIN64
	system("pause");
#else
	printf("exit by enter\n");
	getchar();
#endif
	return 0;
}
