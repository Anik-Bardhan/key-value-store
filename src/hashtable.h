#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stddef.h>

typedef struct hashtable hashtable_t;

hashtable_t *ht_create(size_t initial_capacity);
void ht_destroy(hashtable_t *ht);
int ht_set(hashtable_t *ht, const char *key, const char *value);
const char *ht_get(const hashtable_t *ht, const char *key);
int ht_delete(hashtable_t *ht, const char *key);
size_t ht_size(const hashtable_t *ht);

#endif