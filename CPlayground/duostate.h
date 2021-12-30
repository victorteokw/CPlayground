#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <Python.h>


#define DUOSTATE_INITIAL_CAPACITY 8

typedef void (*to_py_value)(void *);

typedef struct {
    const char *key;
    uint32_t key_hash;
    void *value;
    PyObject *py_value;
    to_py_value to_py_value;
} DuostateItem;

typedef struct {
    size_t len;
    size_t capacity;
    DuostateItem *buffer;
    DuostateItem inline_buffer[DUOSTATE_INITIAL_CAPACITY];
} Duostate;

Duostate *Duostate_alloc(void);

void Duostate_init(Duostate *self);

void Duostate_dealloc(Duostate *self);

#ifdef __cplusplus
}
#endif
