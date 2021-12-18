#include <Python.h>
#include "app.h"


static PyObject *App_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
    App *self = NULL;
    self = (App *)type->tp_alloc(type, 0);
    App_init(self);
    return (PyObject *)self;
}

void App_init(App *self) {
    MatcherList_init(&(self->gets));
    MatcherList_init(&(self->posts));
    MatcherList_init(&(self->patches));
    MatcherList_init(&(self->deletes));
}

void _App_route(App *self, char *route, void (*handle)(Context *), MatcherList *matcher_list) {
    Handler handler;
    Handler_type_c_init(&handler, handle);
    Matcher matcher;
    Matcher_init(&matcher, route, handler);
    MatcherList_append(matcher_list, matcher);
}

void App_get(App *self, char *route, void (*handle)(Context *)) {
    _App_route(self, route, handle, &(self->gets));
}

void App_post(App *self, char *route, void (*handle)(Context *)) {
    _App_route(self, route, handle, &(self->posts));
}

void App_patch(App *self, char *route, void (*handle)(Context *)) {
    _App_route(self, route, handle, &(self->patches));
}

void App_delete(App *self, char *route, void (*handle)(Context *)) {
    _App_route(self, route, handle, &(self->deletes));
}


