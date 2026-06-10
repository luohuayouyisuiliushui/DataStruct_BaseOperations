#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "hash_table_linear.h"
#define INSERT_VALUE(n, ele, j, i) do {(*(n))[(j)].flag = HAS_VALUE; \
(*(n))[(j)].val = ele[(i)]; \
} while(0)

static res isprime(int x) {
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
HashTable hash_table_linear_container_create(size_t n) {
    if(n <= 0){  
        fprintf(stderr, "CONTAINER IS EMPTY.\n");
        return NULL;
    }
    HashTable res = (HashTable)malloc(n * sizeof(struct HT));
    if(!res){
        fprintf(stderr, "Malloc Error.\n");
        return NULL;
    }
    for(int i = 0; i < n; i++) {
        res[i].val = 0;
        res[i].flag = EMPTY;
    }
    return res;
}

//线性探测法
res hash_table_linear_insert(HashTable* n, const int* ele, size_t n_size, size_t elenum) {
    if(!n || !(*n)){
        fprintf(stderr, "Table Is NULL\n");
        return FAILURE;
    }
    if(elenum > n_size) {
        fprintf(stderr, "Data number overs table.\n");
        return FAILURE;
    }
    int p, idx, flag;
    p = find_max_prime(n_size);
    for(int i = 0; i < elenum;i++) {
        idx = ((ele[i] % p) + p) % p;
        flag = 0;
        int j = idx;
        do {
            if((*n)[j].flag == EMPTY || (*n)[j].flag == DELETED){
                INSERT_VALUE(n, ele, j, i);
                flag = 1;
                break;
            }
            j = (j + 1) % n_size;
        } while((j - idx + n_size) % n_size != 0);
        if(flag == 0) {
            fprintf(stderr, "Insert %d Failed, Hash Table is full.\n", ele[i]);
            return FAILURE;
        }
    }
    return SUCCESS;
}

//返回被查找的元素的下表
int hash_table_linear_find(const HashTable n, int ele, size_t n_size) {
    if(!n ){
        fprintf(stderr, "Table Is NULL\n");
        return -1;
    }
    int p = find_max_prime(n_size);
    int idx = ((ele % p) + p) % p;
    int i = idx;
    do {
        if(n[i].flag == EMPTY) {
            fprintf(stderr, "ERROR VALUE.\n");
            return -1;
        }
        else if(n[i].flag == DELETED){  
            i = (i + 1) % n_size;
            continue;
        }
        else
            if(n[i].val == ele)
                return i;
        i = (i + 1) % n_size;
    } while((i - idx + n_size) % n_size != 0);
    return -1;
}

res hash_table_linear_delete(HashTable* n, int ele, size_t n_size) {
    int pos = hash_table_linear_find(*n, ele, n_size);
    if(pos == -1)   return FAILURE;
    (*n)[pos].flag = DELETED;
    return SUCCESS;
}

res hash_table_linear_destroy(HashTable* n){
    if(!(*n)){
        fprintf(stderr, "Table is empty.\n");
        return FAILURE;
    }
    free(*n);
    *n = NULL;
    return SUCCESS;
}