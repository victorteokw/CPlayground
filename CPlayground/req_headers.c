#include "req_headers.h"


static PyTypeObject ReqHeadersType;

ReqHeaders *ReqHeaders_new(Request *request) {
    ReqHeaders *self = NULL;
    self = (ReqHeaders *)ReqHeadersType.tp_alloc(&ReqHeadersType, 0);
    self->request = request;
    return self;
}

void ReqHeaders_dealloc(ReqHeaders *self) {
    Py_TYPE(self)->tp_free((PyObject *)self);
}

Py_ssize_t ReqHeaders_length(PyObject *self) {
    return (Py_ssize_t)(((ReqHeaders *)self)->request->header_num);
}

PyObject *ReqHeaders_subscript(PyObject *self, PyObject *key) {
    const char *string_key = PyUnicode_AsUTF8(key);
    for (uint8_t i = 0; i < ((ReqHeaders *)self)->request->header_num; i++) {
        if (strcmp(((ReqHeaders *)self)->request->headers[i].name, string_key) == 0) {
            PyObject *value = PyUnicode_FromStringAndSize(
                ((ReqHeaders *)self)->request->headers[i].value,
                ((ReqHeaders *)self)->request->headers[i].value_len
            );
            Py_INCREF(value);
            return value;
        }
    }
    Py_RETURN_NONE;
}

static PyMappingMethods ReqHeaders_mapping_methods = {
    .mp_length = ReqHeaders_length,
    .mp_subscript = ReqHeaders_subscript,
    .mp_ass_subscript = NULL
};

static PyTypeObject ResHeadersType = {
    PyObject_HEAD_INIT(NULL)
    .tp_name = "req.ReqHeaders",
    .tp_basicsize = sizeof(ReqHeaders),
    .tp_dealloc = (destructor)ReqHeaders_dealloc,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_as_mapping = &ReqHeaders_mapping_methods
};
