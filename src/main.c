#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

int main(void) {
    printf("Hello Keystore");
    hashtable_t *ht = ht_create(8);
    ht_set(ht, "foo", "bar");
    ht_set(ht, "hello", "world");
    ht_set(ht, "foo", "BAZ");
    ht_delete(ht, "foo");
    ht_destroy(ht);
    return 0;
}