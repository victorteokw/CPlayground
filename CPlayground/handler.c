#include "handler.h"

void Handler_type_c_init(Handler *self, void (*handle)(Context *)) {
    self->type = HandlerTypeC;
    self->c_fun = handle;
    self->py_fun = NULL;
}
void Handler_type_py_init(Handler *self, PyObject *handle) {
    self->type = HandlerTypePython;
    self->c_fun = NULL;
    self->py_fun = handle;
    Py_INCREF(handle);
}

void Handler_dealloc(Handler *self) {
    Py_DECREF(self->py_fun);
}
