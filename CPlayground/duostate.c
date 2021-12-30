#include "duostate.h"


Duostate *Duostate_alloc(void) {
    return (Duostate *)malloc(sizeof(Duostate));
}

void Duostate_init(Duostate *self) {
    self->len = 0;
    self->capacity = DUOSTATE_INITIAL_CAPACITY;
    self->buffer = self->inline_buffer;
}

void Duostate_dealloc(Duostate *self) {
    if (self->buffer != self->inline_buffer) {
        free(self->buffer);
    }
    free(self);
}
