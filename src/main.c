#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashtable.h"

static int parse(hashtable_t *ht, char *input);

int main(void) {
    printf("Hello Keystore\n");
    hashtable_t *ht = ht_create(100);
    if (ht == NULL) {
        return -1;
    }
    char input[100];
    while (1) {
        printf(">> ");
        if (fgets(input, sizeof(input), stdin) == NULL) break;
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }
        if (parse(ht, input) == -1) break;
    }

    ht_destroy(ht);
    return 0;
}

static int parse(hashtable_t *ht, char *input) {
    char *command = strtok(input, " ");
    if (command == NULL) {
        printf("Usage: set get del keys size help\n");
        return 1;
    }
    if (strcmp(command, "set") == 0) {
        char *key = strtok(NULL, " ");
        char *value = strtok(NULL, "");
        if (ht_set(ht, key, value) == -1) {
            printf("Usage: set <key> <value>\n");
        } else {
            printf("OK\n");
        }
        return 0;
    }
    if (strcmp(command, "get") == 0) {
        char *key = strtok(NULL, " ");
        if (key == NULL) {
            printf("Usage: get <key>\n");
            return 1;
        }
        const char *value = ht_get(ht, key);
        printf("%s\n", value ? value : "nil");
        return 0;
    }
    if (strcmp(command, "del") == 0) {
        char *key = strtok(NULL, " ");
        if (key == NULL) {
            printf("Usage: del <key>\n");
            return 1;
        }
        if (ht_delete(ht, key) == -1) {
            printf("Key not found\n");
        } else {
            printf("%s Deleted\n", key);
        }
        return 0;
    }
    if (strcmp(command, "keys") == 0) {
        char **keys = ht_keys(ht);
        size_t size = ht_size(ht);
        for (size_t i = 0; i < size; i++) {
            printf("%s\n", keys[i]);
            free(keys[i]);
        }
        free(keys);
        return 0;
    }
    if (strcmp(command, "size") == 0) {
        printf("size: %zu\n", ht_size(ht));
        return 0;
    }
    if (strcmp(command, "help") == 0) {
        printf("set, get, del, keys and size are the known commands\n");
        return 0;
    }
    if (strcmp(command, "exit") == 0) {
        printf("Bye bye\n");
        return -1;
    }
    printf("Unknown command, retry...\n");
    return 1;
}
