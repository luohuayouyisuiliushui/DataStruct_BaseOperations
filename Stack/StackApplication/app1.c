#include <stdio.h>
#include <stdlib.h>
#include "link_stack.h"
#include <string.h>
#define IF_EQUAL(a, b)  do { if((a) != (b)) {\
        fprintf(stderr, "Error: expected '%c', got '%c'.\n", (b), (a));\
        return ERROR;\
} } while(0)

static void link_stack_destroy(LinkStack* s) {
    while(*s) {
        LinkStack tmp = (*s)->next;
        free(*s);
        *s = tmp;
    }
}
status str_init(char** str, const size_t size) {
    *str = (char*)malloc(size * sizeof(char));
    if(!(*str))
        return MALLOC_ERROR;
    scanf("%s", *str);
    return OK;
}
status match(const char* str) {
    LinkStack s;
    if((link_stack_init(&s) != OK)) {
        fprintf(stderr, "Failed to initialize stack.\n");
        return MALLOC_ERROR;
    }
    for(int i = 0; i < strlen(str); i++) {
        if(str[i] == '(' || str[i] == '[' || str[i] == '{') {
            if(link_stack_push(&s, str[i]) != OK) {
                fprintf(stderr, "Failed to push to stack.\n");
                return MALLOC_ERROR;
            }
        }
        else{
            //先判断栈是否为空
            if(link_stack_get_length(s) == 0) {
                fprintf(stderr, "Stack is empty when trying to pop.\n");
                return STACK_IS_EMPTY;
            }
            char curr_str = str[i], top;
            if(link_stack_top(s, &top) != OK) {
                fprintf(stderr, "Failed to get top element from stack.\n");
                return ERROR;
            }
            switch(curr_str) {
                case ')':
                    IF_EQUAL(top, '(');
                    link_stack_pop(&s);
                    break;
                case ']':
                    IF_EQUAL(top, '[');
                    link_stack_pop(&s); 
                    break;
                case '}':
                    IF_EQUAL(top, '{');
                    link_stack_pop(&s);
                    break;
                default:
                    fprintf(stderr, "Invalid character '%c' in input string.\n", curr_str);
                    return ERROR;
            }
        }
    }
    if(link_stack_get_length(s) != 0) {
        fprintf(stderr, "Stack is not empty after processing all characters.\n");
        return ERROR;
    }
    return OK;
}

// 测试函数
void run_test(const char* test_name, const char* str, int expected_result) {
    printf("测试: %s\n", test_name);
    printf("输入: \"%s\"\n", str);
    status result = match(str);
    if(result == expected_result) {
        printf("✓ 通过 - 结果: %s\n\n", result == OK ? "匹配成功" : "匹配失败");
    } else {
        printf("✗ 失败 - 期望: %s, 实际: %s\n\n", 
               expected_result == OK ? "匹配成功" : "匹配失败",
               result == OK ? "匹配成功" : "匹配失败");
    }
    free(str);
}

int main(void) {
    printf("===== 括号匹配测试集 =====\n\n");
    
    // 测试集1: 正确的括号匹配
    printf("--- 正确匹配的测试 ---\n");
    run_test("简单圆括号", "()", OK);
    run_test("简单方括号", "[]", OK);
    run_test("简单花括号", "{}", OK);
    run_test("嵌套括号", "([{}])", OK);
    run_test("多层嵌套", "((()))", OK);
    run_test("复杂嵌套", "{[()()]}", OK);
    run_test("多个独立组", "()[]{}", OK);
    run_test("长字符串", "({[()]}{[()]})", OK);
    
    printf("\n--- 错误匹配的测试 ---\n");
    // 测试集2: 括号不匹配
    run_test("缺少右括号", "(", ERROR);
    run_test("缺少左括号", ")", ERROR);
    run_test("括号类型不匹配", "(]", ERROR);
    run_test("括号类型不匹配2", "{)", ERROR);
    run_test("顺序错误", "([)]", ERROR);
    run_test("多余右括号", "())", ERROR);
    run_test("多余左括号", "(()", ERROR);
    run_test("复杂不匹配", "{[(])}", ERROR);
    
    printf("\n--- 边界情况测试 ---\n");
    // 测试集3: 边界情况
    run_test("空字符串", "", OK);
    
    printf("\n===== 测试完成 =====\n");
    return 0;
}