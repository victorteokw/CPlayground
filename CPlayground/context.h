#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "request.h"
#include "response.h"
#include "duostate.h"


typedef struct {
    Request *request;
    Response *response;
    Duostate *duostate;
} Context;

#ifdef __cplusplus
}
#endif
