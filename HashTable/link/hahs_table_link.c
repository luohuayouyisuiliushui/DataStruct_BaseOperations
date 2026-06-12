#include "hahs_table_link.h"
#include <stdio.h>
HT* hash_table_link_create(size_t n_size) {
    if(n_size <= 0) {
        // fprintf(stderr, "Table is empty./n");  // [修复] /n 应为 \n
        fprintf(stderr, "Table is empty.\n");
        return NULL;
    }
    HT* n = (HT*)(malloc(sizeof(HT) * n_size));
    for(int i = 0;i < n_size; i++) {
        n[i] = (HT)malloc(sizeof(HashEle));
        n[i]->next = NULL;
    }
    return n;
}

static status isprime(int x) {
    if(x <= 1)  return FAILURE;
    if(x == 2)  return SUCCESS;
    for(int i = 2; i * i <= x; i++) {
        if(x % i == 0)  return FAILURE;
    }
    return SUCCESS;
}
static int find_max_prime(int x) {
    int res = 0;
    if(x == 1)  return 1;
    for(int i = 2;i <= x;i++){
        if(isprime(i) == SUCCESS)  res = i;
    }
    return res;
}

status hash_table_link_insert(HT** n, size_t n_size, ElemType* ele, size_t ele_num) {
    if(n_size <= 0 || !n || !(*n)) {
        fprintf(stderr, "Table is null\n");
        return FAILURE;
    }
    int p = find_max_prime(n_size);
    if(ele_num <= 0){
        fprintf(stderr, "No value insert.\n");
        return FAILURE;
    }
    for(int i = 0;i < ele_num; i++) {
        int idx = ((ele[i] % p) + p ) % p;
        HT node = (HT)malloc(sizeof(HashEle));
        HT tmp = NULL;
        node->val = ele[i];
        if((*n)[idx]->next != NULL)
            tmp = (*n)[idx]->next;
        (*n)[idx]->next = node;
        node->next = tmp;
    }
    return SUCCESS;
}

int hash_table_link_find(const HT* n, size_t n_size, ElemType e) {
    int res = -1;
    if(n_size <= 0 || !n){
        fprintf(stderr, "Table is null\n");
        return res;
    }
    int p = find_max_prime(n_size);
    // int idx = ((idx % p) + p) % p;  // [修复] idx 未初始化，应使用参数 e
    int idx = ((e % p) + p) % p;
    if(n[idx]->next == NULL)    return res;
    else{
        HT ptr = n[idx]->next;
        while(ptr) {
            if(ptr->val == e){
                // return res;  // [修复] res 始终为 -1，应返回 idx 表示找到
                return idx;
            }
            ptr = ptr->next;
        }
    }
    return res;
}
status hash_table_link_destroy(HT** n, size_t n_size){
    for(int i = 0; i < n_size; i++) {
        HT p = (*n)[i] ->next;
        HT pre = (*n)[i];
        while(p) {
            free(pre);
            pre = p;
            p = p->next;
        }
        // [修复] 循环结束时 pre 指向最后一个节点，需释放
        free(pre);
        // pre = p = NULL;  // pre 和 p 都已为 NULL，无需再置空
        pre = NULL;
    }
    free(*n);
    *n = NULL;
    return SUCCESS;
}