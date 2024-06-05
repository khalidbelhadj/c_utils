#include "../include/arena.h"

static Region *region_new(size_t capacity) {
    Region *r = (Region *)calloc(1, sizeof(Region) + sizeof(void *) * capacity);
    *r = (Region){
        .next = NULL,
        .capacity = capacity,
        .size = 0,
    };
    return r;
}

void *arena_alloc(Arena *a, size_t size) {
    if (a->last == NULL) {
        // No regions yet
        assert(a->first == NULL && "First region is non-null when last region is null");
        a->last = region_new(size > REGION_CAPACITY ? size : REGION_CAPACITY);
        a->first = a->last;
    }

    if (a->last->capacity < a->last->size + size) {
        // Not enough space in a->end
        assert(a->last->next == NULL && "Last region is non-null when adding a new region");
        a->last->next =
            region_new(size > REGION_CAPACITY ? size : REGION_CAPACITY);
        a->last = a->last->next;
    }

    void *res = &a->last->data[a->last->size];
    a->last->size += size;

    return res;
}

void arena_free(Arena *a) {
    Region *current = a->first;
    while (current != NULL) {
        Region *tmp = current->next;
        free(current);
        current = tmp;
    }
    *a = (Arena){0};
}
