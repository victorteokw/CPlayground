#include "response.h"

void Response_init(Response *self) {
    self->code = 200;
    HeaderMap_init(&(self->headers));
    self->body = NULL;
    self->body_len = 0;
}
