#include "state.h"


static PyTypeObject StateType;

PyObject *State_new(Duostate *duostate) {
    State *self = NULL;
    self = (State *)StateType.tp_alloc(&StateType, 0);
    self->duostate = duostate;
    return (PyObject *)self;
}

void State_dealloc(State *self) {
    Py_TYPE(self)->tp_free((PyObject *)self);
}

PyObject *State_length(State *self, void *closure) {
    PyObject *value = PyLong_FromSize_t(self->duostate->len);
    Py_INCREF(value);
    return value;
}

int State_ass_subscript(PyObject *self, PyObject *key, PyObject *value) {
    Py_ssize_t key_size;
    const char *string_key = PyUnicode_AsUTF8AndSize(key, &key_size);
    Py_ssize_t value_size;
    const char *string_value = PyUnicode_AsUTF8AndSize(value, &value_size);
    char *copied_key = malloc(key_size);
    strcpy(copied_key, string_key);
    char *copied_value = malloc(value_size);
    strcpy(copied_value, string_value);
    HeaderMap_set(((ResHeaders *)self)->header_map, copied_key, copied_value, true, true);
    return 0;
}

PyObject *State_subscript(PyObject *self, PyObject *key) {
    const char *string_key = PyUnicode_AsUTF8(key);
    char *value = HeaderMap_get(((ResHeaders *)self)->header_map, (char *)string_key);
    if (value == NULL) {
        Py_RETURN_NONE;
    } else {
        PyObject *str = PyUnicode_FromStringAndSize(value, strlen(value));
        Py_INCREF(str);
        return str;
    }
}

static PyMappingMethods State_mapping_methods = {
    .mp_length = State_length,
    .mp_subscript = State_subscript,
    .mp_ass_subscript = State_ass_subscript
};

static PyTypeObject StateType = {
    PyObject_HEAD_INIT(NULL)
    .tp_name = "state.State",
    .tp_basicsize = sizeof(State),
    .tp_dealloc = (destructor)State_dealloc,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_as_mapping = &State_mapping_methods
};
