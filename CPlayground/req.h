#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <Python.h>
#include "request.h"


typedef struct {
    PyObject_HEAD
    Request *request;
    PyObject *method;
    PyObject *path;
    PyObject *query;
    PyObject *version;
} Req;

#ifdef __cplusplus
}
#endif
