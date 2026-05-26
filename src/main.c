#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

int main(void) {
    printf("Hello Keystore\n");
    hashtable_t *ht = ht_create(100);

    // ht_set(ht, "foo", "bar");
    // printf("get foo: %s (expected bar)\n", ht_get(ht, "foo"));
    //
    // ht_set(ht, "hello", "world");
    // ht_set(ht, "foo", "BAZ");
    // printf("get foo: %s (expected BAZ)\n", ht_get(ht, "foo"));
    //
    // printf("size: %zu (expected 2)\n", ht_size(ht));
    //
    // ht_delete(ht, "foo");
    // printf("get foo after delete: %p (expected (nil))\n", (void*)ht_get(ht, "foo"));
    // printf("size: %zu (expected 1)\n", ht_size(ht));
    //

    char key[32], val[32];
    for (int i = 0; i < 100; i++) {
        snprintf(key, sizeof(key), "key_%d", i);
        snprintf(val, sizeof(val), "val_%d", i);
        ht_set(ht, key, val);
    }

    ht_destroy(ht);
    return 0;
}