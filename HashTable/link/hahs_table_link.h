#ifndef HASH_TABLE_LINEAR_H_
#define HASH_TABLE_LINEAR_H_
#include <stdlib.h>
typedef int ElemType;
typedef struct HashTable {
    ElemType val;
    struct HashTable* next;

}*HT,HashEle;
typedef enum status{
    SUCCESS, FAILURE
}status;

HT* hash_table_link_create(size_t n_size);
status hash_table_link_insert(HT** n, size_t n_size, ElemType* eles, size_t ele_num);
int hash_table_link_find(const HT* n, size_t n_size, ElemType e);
status hash_table_link_destroy(HT** n, size_t n_size);


#endif