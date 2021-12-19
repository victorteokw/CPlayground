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
    Response *response;
    HashMap *hash_map;
} Context;
