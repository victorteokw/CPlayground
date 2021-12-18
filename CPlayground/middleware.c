//
//  middleware.c
//  CPlayground
//
//  Created by Victor Teo on 2021/12/18.
//

#include "middleware.h"

void Middleware_type_c_init(Middleware *self, void (*middleware)(Context *, PyObject *)) {
    self->type = MiddlewareTypeC;
    self->c_fun = middleware;
    self->py_fun = NULL;
}

void Middleware_type_py_init(Middleware *self, PyObject *middleware) {
    self->type = MiddlewareTypePython;
    self->c_fun = NULL;
    self->py_fun = middleware;
    Py_INCREF(middleware);
}

void Middleware_dealloc(Middleware *self) {
    Py_DECREF(self->py_fun);
}
