#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <Python.h>


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
    DuostateItem *buffer;
    DuostateItem inline_buffer[8];
} Duostate;

#ifdef __cplusplus
}
#endif
