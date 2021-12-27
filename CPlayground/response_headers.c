#include <stdlib.h>
#include <string.h>
#include "response_headers.h"
#include "hash.h"


HeaderMap *HeaderMap_new(void) {
    HeaderMap *header_map = malloc(sizeof(HeaderMap));
    return header_map;
}

void HeaderMap_init(HeaderMap *self) {
    self->buffer = self->inline_buffer;
    self->capacity = HEADER_MAP_INITIAL_SIZE;
    self->len = 0;
}

void HeaderMap_dealloc(HeaderMap *self) {
    if (self->buffer != self->inline_buffer) {
        free(self->buffer);
    }
    free(self);
}

void HeaderMap_set(HeaderMap *self, char *key, void *value, bool free_key, bool free_value) {
    uint32_t hash = fast_hash(key, (int)strlen(key));
    HeaderItem *pos = NULL;
    for (size_t i = 0; i < self->len; i++) {
        if (self->buffer[i].key_hash == hash) {
            pos = &(self->buffer[i]);
        }
    }
    if (pos != NULL) {
        if (pos->free_key) {
            free(pos->key);
        }
        if (pos->free_value) {
            free(pos->value);
        }
        pos->free_key = free_key;
        pos->free_value = free_value;
        pos->value = value;
    } else {
        if (self->len == self->capacity) {
            size_t copy_size = self->capacity * sizeof(HeaderItem);
            self->capacity = self->capacity + HEADER_MAP_INITIAL_SIZE;
            self->buffer = malloc(self->capacity * sizeof(HeaderItem));
            memcpy(self->buffer, self->inline_buffer, copy_size);
        }
        size_t index = self->len;
        self->len++;
        self->buffer[index].key = key;
        self->buffer[index].value = value;
        self->buffer[index].key_hash = hash;
        self->buffer[index].free_key = free_key;
        self->buffer[index].free_value = free_value;
    }
}

char *HeaderMap_get(HeaderMap *self, char *key) {
    uint32_t hash = fast_hash(key, (int)strlen(key));
    for (size_t i = 0; i < self->len; i++) {
        if (self->buffer[i].key_hash == hash) {
            return self->buffer[i].value;
        }
    }
    return NULL;
}
