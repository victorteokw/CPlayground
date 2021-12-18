#include "matcher.h"

void Matcher_init(Matcher *self, char *route, Handler handler) {
    self->route = route;
    self->handler = handler;
}

void MatcherList_init(MatcherList *self) {
    self->capacity = INLINE_MATCHER_LIST_SIZE;
    self->buffer = self->inline_buffer;
    self->length = 0;
}

void MatcherList_dealloc(MatcherList *self) {
    if (self->buffer != self->inline_buffer) {
        free(self->buffer);
    }
}

void MatcherList_append(MatcherList *self, Matcher matcher) {
    size_t index = self->length;
    if (index > self->capacity) { // TODO: unlikely
        self->capacity += 32;
        if (self->buffer == self->inline_buffer) {
            self->buffer = malloc(self->capacity * sizeof(Matcher));
            memcpy(self->buffer, self->inline_buffer, INLINE_MATCHER_LIST_SIZE * sizeof(Matcher));
        } else {
            self->buffer = realloc(self->buffer, self->capacity * sizeof(Matcher));
        }
    }
    self->buffer[index] = matcher;
    self->length++;
}
