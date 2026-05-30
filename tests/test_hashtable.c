#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../src/hashtable.h"

static void test_set_and_get() {
    hashtable_t *ht = ht_create(4);
    assert(ht != NULL);
    assert(ht_set(ht, "foo", "bar") == 0);
    assert(strcmp(ht_get(ht, "foo"), "bar") == 0);
    ht_destroy(ht);
    printf("test_set_and_get: PASS\n");
}

static void test_set_and_overwrite() {
    hashtable_t *ht = ht_create(4);
    assert(ht != NULL);
    assert(ht_set(ht, "foo", "bar") == 0);
    assert(strcmp(ht_get(ht, "foo"), "bar") == 0);
    assert(ht_set(ht, "foo", "car") == 0);
    assert(strcmp(ht_get(ht, "foo"), "car") == 0);
    ht_destroy(ht);
    printf("test_set_and_overwrite: PASS\n");
}

static void test_delete_and_get() {
    hashtable_t *ht = ht_create(4);
    assert(ht != NULL);
    assert(ht_set(ht, "foo", "bar") == 0);
    assert(strcmp(ht_get(ht, "foo"), "bar") == 0);
    assert(ht_delete(ht, "foo") == 0);
    assert(ht_get(ht, "foo") == NULL);
    ht_destroy(ht);
    printf("test_delete_and_get: PASS\n");
}

static void test_large_volume() {
    hashtable_t *ht = ht_create(4);
    assert(ht != NULL);
    char key[32];
    char val[32];
    for (size_t i = 0; i < 10000; i++) {
        snprintf(key, sizeof(key), "key_%zu", i);
        snprintf(val, sizeof(val), "val_%zu", i);
        assert(ht_set(ht, key, val) == 0);
    }

    for (size_t i = 0; i < 10000; i++) {
        snprintf(key, sizeof(key), "key_%zu", i);
        snprintf(val, sizeof(val), "val_%zu", i);
        assert(strcmp(ht_get(ht, key), val) == 0);
    }

    assert(ht_size(ht) == 10000);
    ht_destroy(ht);
    printf("test_large_volume: PASS\n");
}

static void test_resize() {
    hashtable_t *ht = ht_create(1);
    assert(ht != NULL);
    assert(ht_set(ht, "foo1", "bar1") == 0);
    assert(ht_size(ht) == 1);
    assert(ht_capacity(ht) == 1);
    assert(ht_set(ht, "foo2", "bar2") == 0);
    assert(ht_size(ht) == 2);
    assert(ht_capacity(ht) == 2);
    ht_destroy(ht);
    printf("test_resize: PASS\n");
}

static void test_null_entries() {
    hashtable_t *ht = ht_create(2);
    assert(ht != NULL);
    assert(ht_set(ht, NULL, NULL) == -1);
    assert(ht_get(NULL, "foo") == NULL);
    assert(ht_get(ht, NULL) == NULL);
    ht_destroy(ht);
    printf("test_null_entries: PASS\n");
}

int main() {
    test_set_and_get();
    test_set_and_overwrite();
    test_delete_and_get();
    test_large_volume();
    test_resize();
    test_null_entries();
    return 0;
}