/*
    Arena allocator
*/

#ifndef ARENA_H_
#define ARENA_H_
#include <stdlib.h>

#define REGION_CAPACITY ((size_t)1 << 16)
#define MAX(a, b) (a > b ? a : b)

typedef struct Region {
    struct Region *next;
    size_t capacity;
    size_t size;
    void *data[];
} Region;

typedef struct {
    Region *first;
    Region *last;
} Arena;

void *arena_alloc(Arena *a, size_t size);
void arena_free(Arena *a);

#endif // ARENA_IMPLEMEMTATION