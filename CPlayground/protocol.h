#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <Python.h>
#include "app.h"
#include "request.h"


typedef struct {
    PyObject_HEAD
    App *app;
    PyObject *transport;
    PyObject *req;
    Request request;
} Protocol;

#ifdef __cplusplus
}
#endif
