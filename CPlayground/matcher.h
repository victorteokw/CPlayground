#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <Python.h>
#include "handler.h"


#define INLINE_MATCHER_LIST_SIZE 32

typedef struct {
    char *route;
    Handler handler;
//    bool is_static;
//    uint8_t ele_num;
} Matcher;

typedef struct {
    Matcher *buffer;
    Matcher inline_buffer[INLINE_MATCHER_LIST_SIZE];
    size_t length;
    size_t capacity;
} MatcherList;

void Matcher_init(Matcher *self, char *route, Handler handler);

void MatcherList_init(MatcherList *self);

void MatcherList_append(MatcherList *self, Matcher matcher);

void MatcherList_dealloc(MatcherList *self);

#ifdef __cplusplus
}
#endif
