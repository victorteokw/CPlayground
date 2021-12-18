#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <Python.h>
#include "context.h"


typedef enum {
    MiddlewareTypeC,
    MiddlewareTypePython
} MiddlewareType;

typedef struct {
    MiddlewareType type;
    void (*c_fun)(Context *, PyObject *);
    PyObject *py_fun;
} Middleware;

void Middleware_type_c_init(Middleware *self, void (*middleware)(Context *, PyObject *));
void Middleware_type_py_init(Middleware *self, PyObject *middleware);
void Middleware_dealloc(Middleware *self);

#ifdef __cplusplus
}
#endif
