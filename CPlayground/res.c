#include "res.h"
#include "res_headers.h"


PyObject *Res_new(PyTypeObject *type, Response *response) {
    Res *self = NULL;
    self = (Res *)type->tp_alloc(type, 0);
    self->response = response;
    self->code = NULL;
    self->headers = NULL;
    self->body = NULL;
    return (PyObject *)self;
}

static void Res_dealloc(Res *self) {
    Py_XDECREF(self->code);
    Py_XDECREF(self->headers);
    Py_XDECREF(self->body);
    Py_TYPE(self)->tp_free((PyObject *)self);
}

void Res_set_length_header(Res *self) {

}

static PyObject *Res_get_code(Res *self, void *closure) {
    if (!self->code) {
        self->code = PyLong_FromUnsignedLong((unsigned long)self->response->code);
    }
    Py_INCREF(self->code);
    return self->code;
}

static int Res_set_code(Res *self, PyObject *value, void *closure) {
    Py_INCREF(value);
    self->code = value;
    self->response->code = PyLong_AsUnsignedLong(value);
    return 0;
}

static PyObject *Res_get_headers(Res *self, void *closure) {
    if (!self->headers) {
        self->headers = ResHeaders_new(self->headers);
    }
    Py_INCREF(self->headers);
    return self->headers;
}

static PyGetSetDef Res_getset[] = {
    {"code", (getter)Res_get_code, (setter)Res_set_code, NULL, NULL},
    {"headers", (getter)Res_get_headers, NULL, NULL, NULL},
    {"body", (getter)Res_get_body, (setter)Res_set_body, NULL, NULL},
    {NULL}
};

static PyTypeObject ReqType = {
    PyObject_HEAD_INIT(NULL)
    .tp_name = "res.Res",
    .tp_basicsize = sizeof(Res),
    .tp_dealloc = (destructor)Res_dealloc,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_getset = Res_getset,
};
