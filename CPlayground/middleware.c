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
    Py_XINCREF(middleware);
}

void Middleware_dealloc(Middleware *self) {
    Py_XDECREF(self->py_fun);
}

void MiddlewareList_init(MiddlewareList *self) {
    self->capacity = INLINE_MIDDLEWARE_LIST_SIZE;
    self->buffer = self->inline_buffer;
    self->length = 0;
}

void MatcherList_dealloc(MiddlewareList *self) {
    if (self->buffer != self->inline_buffer) {
        free(self->buffer);
    }
}

void MiddlewareList_append(MiddlewareList *self, Middleware middleware) {
    size_t index = self->length;
    if (index > self->capacity) { // TODO: unlikely
        self->capacity += 32;
        if (self->buffer == self->inline_buffer) {
            self->buffer = malloc(self->capacity * sizeof(Middleware));
            memcpy(self->buffer, self->inline_buffer, INLINE_MIDDLEWARE_LIST_SIZE * sizeof(Middleware));
        } else {
            self->buffer = realloc(self->buffer, self->capacity * sizeof(Middleware));
        }
    }
    self->buffer[index] = middleware;
    self->length++;
}
