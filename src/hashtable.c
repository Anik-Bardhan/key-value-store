#include "hashtable.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

static uint64_t fnv1a_hash64(const void *data, size_t len);

typedef struct entry {
    char *key;
    char *value;
    struct entry *next;
} entry_t;

struct hashtable {
    entry_t **buckets;
    size_t   capacity;
    size_t   size;
};

hashtable_t *ht_create(size_t initial_capacity) {
    hashtable_t *ht = malloc(sizeof(hashtable_t));
    if (ht == NULL) {
        return NULL;
    }
    ht->buckets = calloc(initial_capacity, sizeof(entry_t *));
    if (ht->buckets == NULL) {
        free(ht);
        return NULL;
    }
    ht->size = 0;
    ht->capacity = initial_capacity;
    return ht;
}

void ht_destroy(hashtable_t *ht) {
    if (ht == NULL) {
        return;
    }
    for (size_t i = 0; i < ht->capacity; i++) {
        entry_t *cur = ht->buckets[i];
        while (cur != NULL) {
            entry_t *next = cur->next;
            free(cur->key);
            free(cur->value);
            free(cur);
            cur = next;
        }
    }
    free(ht->buckets);
    free(ht);
}

int ht_set(hashtable_t *ht, const char *key, const char *value) {
    if (ht == NULL) {
        return -1;
    }
    uint64_t index = fnv1a_hash64(key, strlen(key)) % ht->capacity;
    entry_t *cur = ht->buckets[index];
    while (cur != NULL) {
        if (strcmp(cur->key, key) == 0) {
            char *new_value = strdup(value);
            if (new_value == NULL) return -1;
            free(cur->value);
            cur->value = new_value;
            return 0;
        }
        cur = cur->next;
    }
    entry_t *new_entry = malloc(sizeof(entry_t));
    if (new_entry == NULL) {
        return -1;
    }
    new_entry->key = strdup(key);
    if (new_entry->key == NULL) {
        free(new_entry);
        return -1;
    }
    new_entry->value = strdup(value);
    if (new_entry->value == NULL) {
        free(new_entry->key);
        free(new_entry);
        return -1;
    }
    new_entry->next = ht->buckets[index];
    ht->buckets[index] = new_entry;
    ht->size++;
    return 0;
}

size_t ht_size(const hashtable_t *ht) {
    if (ht == NULL) {
        return 0;
    }
    return ht->size;
}

static uint64_t fnv1a_hash64(const void *data, size_t len) {
    const uint8_t *bytes = (const uint8_t *)data;
    uint64_t hash = 14695981039346656037ull;  // FNV offset basis
    for (size_t i = 0; i < len; i++) {
        hash ^= bytes[i];
        hash *= 1099511628211ull;              // FNV prime
    }
    return hash;
}