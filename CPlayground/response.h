#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "response_headers.h"

typedef struct {
    uint16_t code;
    HeaderMap headers;
    char *body;
    size_t body_len;
} Response;

void Response_init(Response *self);

#ifdef __cplusplus
}
#endif
