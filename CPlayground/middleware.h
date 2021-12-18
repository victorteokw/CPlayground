#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <Python.h>
#include "context.h"


#define INLINE_MIDDLEWARE_LIST_SIZE 16

typedef enum {
    MiddlewareTypeC,
    MiddlewareTypePython
} MiddlewareType;

typedef struct {
    MiddlewareType type;
    void (*c_fun)(Context *, PyObject *);
    PyObject *py_fun;
} Middleware;

typedef struct {
    Middleware *buffer;
    Middleware inline_buffer[INLINE_MIDDLEWARE_LIST_SIZE];
    size_t length;
    size_t capacity;
} MiddlewareList;

void Middleware_type_c_init(Middleware *self, void (*middleware)(Context *, PyObject *));

void Middleware_type_py_init(Middleware *self, PyObject *middleware);

void Middleware_dealloc(Middleware *self);

void MiddlewareList_init(MiddlewareList *self);

void MiddlewareList_append(MiddlewareList *self, Middleware middleware);

void MiddlewareList_dealloc(MiddlewareList *self);

#ifdef __cplusplus
}
#endif
