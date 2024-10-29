#include "ptl/array.h"
#include <stdlib.h>
#include <string.h>

void *ptl_array_push(void *dest, const void *src, struct ptl_array_info *info) {
    if (info->len >= info->cap) {
        info->cap =
            info->cap ? info->cap * 2 : 8; // TODO: Configurable default cap
        dest = realloc(dest, info->cap * info->elem_size);
    }
    memcpy((uint8_t *)dest + info->len * info->elem_size, src, info->elem_size);
    info->len++;
    return dest;
}
