#pragma once

#include <stdio.h>
#include "request.h"
#include "req.h"
#include "response.h"
#include "res.h"
#include "hashmap.h"
#include "state.h"

typedef struct {
    Request *request;
    Req *req;
    Response *response;
    Res *res;
    HashMap *hash_map;
    State *state;
} Context;
