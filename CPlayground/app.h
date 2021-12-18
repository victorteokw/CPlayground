#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <Python.h>
#include "matcher.h"
#include "context.h"


typedef struct {
    PyObject_HEAD
    MatcherList gets;
    MatcherList posts;
    MatcherList patches;
    MatcherList deletes;
//    MiddlewareList middlewares;
} App;

static PyObject *App_new(PyTypeObject *type, PyObject *args, PyObject *kwds);

void App_init(App* self);

void App_get(App *self, char *route, void (*handle)(Context *));
void App_post(App *self, char *route, void (*handle)(Context *));
void App_patch(App *self, char *route, void (*handle)(Context *));
void App_delete(App *self, char *route, void (*handle)(Context *));

void App_use(App *self, void (*middleware)(Context *, PyObject *));

#ifdef __cplusplus
}
#endif
