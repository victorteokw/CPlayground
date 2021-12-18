#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <Python.h>
#include "context.h"


typedef enum {
    HandlerTypeC,
    HandlerTypePython
} HandlerType;

typedef struct {
    HandlerType type;
    void (*c_fun)(Context *);
    PyObject *py_fun;
} Handler;

void Handler_type_c_init(Handler *self, void (*handle)(Context *));
void Handler_type_py_init(Handler *self, PyObject *handle);
void Handler_dealloc(Handler *self);

#ifdef __cplusplus
}
#endif
