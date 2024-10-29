#include "ptl/hash.h"
#include <stdint.h>

#define DJB2_INIT (5381LLu)

uint64_t ptl_hash_djb2(const void *data, size_t size) {
    uint64_t hash = DJB2_INIT;
    for (size_t i = 0; i < size; i++) {
        hash = ((hash << 5) + hash) + *((uint8_t*)data + i);
    }
    return hash;
}

uint64_t ptl_hash_cstring_djb2(const char *string) {
    uint64_t hash = DJB2_INIT;
    uint64_t c = 0;
    while ((c = *string++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}
