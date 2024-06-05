/*
    Immutable strings.
*/

#ifndef STR_H_
#define STR_H_

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "arena.h"

typedef struct {
    const char *content;
    const size_t length;
} str;

str str_empty(Arena *a);
str str_new(Arena *a, const char *cstr);
str str_copy(Arena *a, str str);
str str_insert(Arena *a, str str, const char ch, size_t position);
str str_concat(Arena *a, str s1, str s2);
char str_at(str str, size_t position);
bool str_equal(str s1, str s2);

#endif // STR_H_
