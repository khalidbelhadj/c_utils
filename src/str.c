#include "../include/str.h"

str str_new(Arena *a, const char *cstr) {
    size_t length = strlen(cstr);
    char *content = (char *)arena_alloc(a, length);
    strncpy(content, cstr, length);
    return (str){content, length};
}

str str_copy(Arena *a, str s) {
    char *content = (char *)arena_alloc(a, s.length);
    memcpy(content, s.content, s.length);

    return (str){
        content,
        s.length,
    };
}

void str_insert_char(Arena *a, str *str, const char ch, uint64_t position) {}

str str_insert(Arena *a, str s, const char ch, uint64_t position) {
    str new_str = {.length = s.length};

    char *new_content = (char *)arena_alloc(a, sizeof(char) * (s.length + 1));
    memcpy(new_content, s.content, s.length);
    memmove(&new_content[position + 1], &new_content[position],
            s.length - position);
    new_content[position] = ch;

    new_str.content = new_content;
    return new_str;
}

str str_concat(Arena *a, str s1, str s2) {
    char *new_content =
        (char *)arena_alloc(a, sizeof(char) * (s1.length + s2.length));
    memcpy(new_content, s1.content, s1.length);
    memcpy(&new_content[s1.length], s2.content, s2.length);
    return (str){.length = s1.length + s2.length, .content = new_content};
}

char str_at(str str, uint64_t position) {
    if (position < 0 || position >= str.length)
        return -1;

    return str.content[position];
}

bool str_equal(str s1, str s2) {
    if (s1.length != s2.length) {
        return false;
    }

    for (uint64_t i = 0; i < s1.length; ++i) {
        if (str_at(s1, i) != str_at(s1, i))
            return false;
    }

    return true;
}
