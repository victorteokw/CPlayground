#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdbool.h>


#define HEADER_MAP_INITIAL_SIZE 16

typedef struct {
    char *key;
    uint32_t key_hash;
    bool free_key;
    char *value;
    bool free_value;
} HeaderItem;

typedef struct {
    HeaderItem *buffer;
    HeaderItem inline_buffer[HEADER_MAP_INITIAL_SIZE];
    size_t len;
    size_t capacity;
} HeaderMap;

HeaderMap *HeaderMap_new(void);

void HeaderMap_init(HeaderMap *self);

void HeaderMap_dealloc(HeaderMap *self);

void HeaderMap_set(HeaderMap *self, char *key, void *value, bool free_key, bool free_value);

char *HeaderMap_get(HeaderMap *self, char *key);

#ifdef __cplusplus
}
#endif
