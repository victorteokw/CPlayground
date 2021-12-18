#include "req.h"


PyObject *Req_new(PyTypeObject *type, Request *request) {
    Req *self = NULL;
    self = (Req *)type->tp_alloc(type, 0);
    self->request = request;
    self->method = NULL;
    self->path = NULL;
    self->query = NULL;
    self->version = NULL;
    return (PyObject *)self;
}

static void Req_dealloc(Req *self) {
    Py_XDECREF(self->method);
    Py_XDECREF(self->path);
    Py_XDECREF(self->query);
    Py_XDECREF(self->version);
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *Req_get_method(Req *self, void *closure) {
    if (!self->method) {
        self->method = PyUnicode_DecodeLatin1(self->request->method,
                                              self->request->method_len,
                                              NULL);
    }
    Py_INCREF(self->method);
    return self->method;
}

static PyObject *Req_get_path(Req *self, void *closure) {
    if (!self->path) {
        self->path = PyUnicode_DecodeLatin1(self->request->path,
                                            self->request->path_len,
                                            NULL);
    }
    Py_INCREF(self->path);
    return self->path;
}

static PyObject *Req_get_query(Req *self, void *closure) {
    if (self->request->query_len == 0) {
        Py_RETURN_NONE;
    }
    if (!self->query) {
        self->query = PyUnicode_DecodeLatin1(self->request->query,
                                             self->request->query_len,
                                             NULL);
    }
    Py_INCREF(self->query);
    return self->query;
}

static PyObject *Req_get_version(Req *self, void *closure) {
    if (!self->version) {
        self->version = PyUnicode_DecodeLatin1(self->request->version,
                                               self->request->version_len,
                                               NULL);
    }
    Py_INCREF(self->version);
    return self->version;
}

static PyGetSetDef Req_getset[] = {
    {
        "method",  /* name */
        (getter)Req_get_method, /* getter */
        NULL, /* setter */
        NULL,  /* doc */
        NULL /* closure */
    },
    {
        "path",  /* name */
        (getter)Req_get_path, /* getter */
        NULL, /* setter */
        NULL,  /* doc */
        NULL /* closure */
    },
    {
        "query",  /* name */
        (getter)Req_get_query, /* getter */
        NULL, /* setter */
        NULL,  /* doc */
        NULL /* closure */
    },
    {
        "version",  /* name */
        (getter)Req_get_version, /* getter */
        NULL, /* setter */
        NULL,  /* doc */
        NULL /* closure */
    },
    {NULL}
};

// args
// headers
// body

static PyTypeObject ReqType = {
    PyObject_HEAD_INIT(NULL)
    .tp_name = "req.Req",
    .tp_basicsize = sizeof(Req),
    .tp_dealloc = (destructor)Req_dealloc,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_getset = Req_getset,
};
