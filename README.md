# PTL - Perky Template Library

PTL aims to be a lightweight and simple implementation of a templated standard library.
Templates are implemented via macros defining type-safe wrappers around type-unsafe functions.

## Example
```c
#include "ptl/array.h"
#include "ptl/hash.h"
#include "ptl/map.h"
#include "ptl/string.h"

#include <stdio.h>

PTL_TEMPLATE_MAP(struct ptl_static_string, int, map_from_string_to_int)
PTL_TEMPLATE_ARRAY(struct ptl_static_string, array_of_strings)

int main() {
    struct array_of_strings strings = array_of_strings();
    array_of_strings_push(&strings, &ptl_static_string("1"));
    array_of_strings_push(&strings, &ptl_static_string("2"));
    array_of_strings_push(&strings, &ptl_static_string("3"));
    array_of_strings_push(&strings, &ptl_static_string("4"));
    array_of_strings_push(&strings, &ptl_static_string("5"));

    struct map_from_string_to_int map = map_from_string_to_int();
    map_from_string_to_int_resize(&map, 32);
    for (size_t i = 0; i < strings.info.len; i++) {
        int val = (int)(i + 1);
        map_from_string_to_int_set(&map, &strings.elems[i], &val);
    }

    for (size_t i = 0; i < strings.info.len; i++) {
        printf("%d\n", *map_from_string_to_int_get(&map, &strings.elems[i]));
    }
}

inline static uint64_t
map_from_string_to_int_hash(const struct ptl_static_string *string) {
    return ptl_hash_cstring_djb2(string->characters);
}
```