#include <stdio.h>
#include <stdlib.h>
#include "hash_table_linear.h"

static int passed = 0;
static int failed = 0;

#define TEST(name)  printf("  %-40s ", name)
#define OK()        do { printf("[PASS]\n"); passed++; } while(0)
#define FAIL(msg)   do { printf("[FAIL] %s\n", msg); failed++; } while(0)

int main(void) {
    printf("========================================\n");
    printf("  Hash Table (Linear Probing) Test\n");
    printf("========================================\n\n");

    // -------------------------------------------------------
    // 1. create & destroy
    // -------------------------------------------------------
    printf("[1] Create / Destroy\n");
    {
        TEST("create table size=10");
        HashTable t = hash_table_linear_container_create(10);
        if (t == NULL) { FAIL("returned NULL"); }
        else           { OK(); }

        TEST("destroy table");
        res r = hash_table_linear_destroy(&t);
        if (r != SUCCESS) { FAIL("destroy failed"); }
        else if (t != NULL) { FAIL("pointer not NULL after destroy"); }
        else { OK(); }
    }

    // -------------------------------------------------------
    // 2. basic insert & find
    // -------------------------------------------------------
    printf("\n[2] Basic Insert / Find\n");
    {
        HashTable t = hash_table_linear_container_create(10);
        int ele[] = {15, 25, 35, 5, 55};

        TEST("insert 5 elements");
        res r = hash_table_linear_insert(&t, ele, 10, 5);
        if (r != SUCCESS) { FAIL("insert returned FAILURE"); }
        else { OK(); }

        TEST("find 15");
        int pos = hash_table_linear_find(t, 15, 10);
        if (pos < 0) { FAIL("not found"); }
        else if (t[pos].val != 15) { FAIL("wrong value"); }
        else { OK(); }

        TEST("find 25");
        pos = hash_table_linear_find(t, 25, 10);
        if (pos < 0 || t[pos].val != 25) { FAIL("not found"); }
        else { OK(); }

        TEST("find 35");
        pos = hash_table_linear_find(t, 35, 10);
        if (pos < 0 || t[pos].val != 35) { FAIL("not found"); }
        else { OK(); }

        TEST("find 5");
        pos = hash_table_linear_find(t, 5, 10);
        if (pos < 0 || t[pos].val != 5) { FAIL("not found"); }
        else { OK(); }

        TEST("find 55");
        pos = hash_table_linear_find(t, 55, 10);
        if (pos < 0 || t[pos].val != 55) { FAIL("not found"); }
        else { OK(); }

        TEST("find non-existent 99");
        pos = hash_table_linear_find(t, 99, 10);
        if (pos != -1) { FAIL("should return -1"); }
        else { OK(); }

        hash_table_linear_destroy(&t);
    }

    // -------------------------------------------------------
    // 3. collision resolution (linear probing)
    // -------------------------------------------------------
    printf("\n[3] Collision Resolution\n");
    {
        HashTable t = hash_table_linear_container_create(10);
        int ele[] = {7, 17, 27, 37, 47};  /* all mod 7 == prime */

        TEST("insert colliding keys 7,17,27,37,47");
        res r = hash_table_linear_insert(&t, ele, 10, 5);
        if (r != SUCCESS) { FAIL("insert failed"); }
        else { OK(); }

        TEST("find all after collision");
        int ok = 1;
        for (int i = 0; i < 5; i++) {
            int pos = hash_table_linear_find(t, ele[i], 10);
            if (pos < 0 || t[pos].val != ele[i]) { ok = 0; break; }
        }
        if (!ok) { FAIL("some keys not found"); }
        else { OK(); }

        hash_table_linear_destroy(&t);
    }

    // -------------------------------------------------------
    // 4. delete & re-insert (DELETED tombstone)
    // -------------------------------------------------------
    printf("\n[4] Delete / Re-insert\n");
    {
        HashTable t = hash_table_linear_container_create(10);
        int ele[] = {10, 20, 30, 40, 50};

        hash_table_linear_insert(&t, ele, 10, 5);

        TEST("delete 20");
        res r = hash_table_linear_delete(&t, 20, 10);
        if (r != SUCCESS) { FAIL("delete failed"); }
        else { OK(); }

        TEST("find 20 after delete (should fail)");
        int pos = hash_table_linear_find(t, 20, 10);
        if (pos != -1) { FAIL("still found deleted element"); }
        else { OK(); }

        TEST("re-insert 20 into tombstone slot");
        int newval = 20;
        r = hash_table_linear_insert(&t, &newval, 10, 1);
        if (r != SUCCESS) { FAIL("re-insert failed"); }
        else { OK(); }

        TEST("find 20 after re-insert");
        pos = hash_table_linear_find(t, 20, 10);
        if (pos < 0 || t[pos].val != 20) { FAIL("not found"); }
        else { OK(); }

        TEST("other keys still intact");
        int ok = 1;
        int keep[] = {10, 30, 40, 50};
        for (int i = 0; i < 4; i++) {
            pos = hash_table_linear_find(t, keep[i], 10);
            if (pos < 0 || t[pos].val != keep[i]) { ok = 0; break; }
        }
        if (!ok) { FAIL("existing keys lost"); }
        else { OK(); }

        hash_table_linear_destroy(&t);
    }

    // -------------------------------------------------------
    // 5. negative keys
    // -------------------------------------------------------
    printf("\n[5] Negative Keys\n");
    {
        HashTable t = hash_table_linear_container_create(10);
        int ele[] = {-7, -17, 3, -27};

        TEST("insert negative keys -7,-17,3,-27");
        res r = hash_table_linear_insert(&t, ele, 10, 4);
        if (r != SUCCESS) { FAIL("insert failed"); }
        else { OK(); }

        TEST("find -7");
        int pos = hash_table_linear_find(t, -7, 10);
        if (pos < 0 || t[pos].val != -7) { FAIL("not found"); }
        else { OK(); }

        TEST("find -17");
        pos = hash_table_linear_find(t, -17, 10);
        if (pos < 0 || t[pos].val != -17) { FAIL("not found"); }
        else { OK(); }

        TEST("find -27");
        pos = hash_table_linear_find(t, -27, 10);
        if (pos < 0 || t[pos].val != -27) { FAIL("not found"); }
        else { OK(); }

        TEST("find 3");
        pos = hash_table_linear_find(t, 3, 10);
        if (pos < 0 || t[pos].val != 3) { FAIL("not found"); }
        else { OK(); }

        hash_table_linear_destroy(&t);
    }

    // -------------------------------------------------------
    // 6. edge cases
    // -------------------------------------------------------
    printf("\n[6] Edge Cases\n");
    {
        TEST("create size=0 returns NULL");
        HashTable t = hash_table_linear_container_create(0);
        if (t != NULL) { FAIL("should return NULL"); hash_table_linear_destroy(&t); }
        else { OK(); }

        TEST("find on NULL table returns -1");
        int pos = hash_table_linear_find(NULL, 5, 10);
        if (pos != -1) { FAIL("should return -1"); }
        else { OK(); }

        TEST("delete non-existent element");
        t = hash_table_linear_container_create(10);
        int ele = 42;
        hash_table_linear_insert(&t, &ele, 10, 1);
        res r = hash_table_linear_delete(&t, 999, 10);
        if (r != FAILURE) { FAIL("should return FAILURE"); }
        else { OK(); }

        hash_table_linear_destroy(&t);
    }

    // -------------------------------------------------------
    // 7. full table
    // -------------------------------------------------------
    printf("\n[7] Full Table Insert\n");
    {
        HashTable t = hash_table_linear_container_create(5);
        int ele[] = {1, 2, 3, 4, 5};

        TEST("fill table with 5 elements");
        res r = hash_table_linear_insert(&t, ele, 5, 5);
        if (r != SUCCESS) { FAIL("insert failed"); }
        else { OK(); }

        TEST("insert into full table");
        int extra = 6;
        r = hash_table_linear_insert(&t, &extra, 5, 1);
        if (r != FAILURE) { FAIL("should return FAILURE"); }
        else { OK(); }

        hash_table_linear_destroy(&t);
    }

    // -------------------------------------------------------
    // Report
    // -------------------------------------------------------
    printf("\n========================================\n");
    printf("  Total: %d passed, %d failed\n", passed, failed);
    printf("========================================\n");

    return failed > 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}