//这个写的是除余留数法、开放定址法
#ifndef HASH_TABLE_LINEAR_H_
#define HASH_TABLE_LINEAR_H_
#include <stddef.h>
typedef struct HT {
    int val;
    unsigned int flag  : 2; //对应三种状态，空，有值且存在，之前有值但被删除
}*HashTable;
typedef enum status{
    EMPTY = 0, HAS_VALUE = 1, DELETED = 2
}status;
typedef enum res {
    SUCCESS, FAILURE
}res;
HashTable hash_table_linear_container_create(size_t n_size);
res hash_table_linear_insert(HashTable* n, const int* ele, size_t n_size, size_t elenum);
int hash_table_linear_find(const HashTable n, int ele, size_t n_size);
res hash_table_linear_delete(HashTable* n, int ele, size_t n_size);
res hash_table_linear_destroy(HashTable* n);
#endif