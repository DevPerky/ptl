#ifndef MAP_D8A011B1_50B6_4258_B821_C7AEC6BE0C29_H
#define MAP_D8A011B1_50B6_4258_B821_C7AEC6BE0C29_H
#include "ptl/array.h"
#include "ptl/list.h"
#include <stddef.h>
#include <stdint.h>

struct ptl_map_entry {
    uint64_t hash;
    size_t index;
};

PTL_TEMPLATE_LIST(struct ptl_map_entry, ptl_map_bucket)

struct ptl_map_bucket_array {
    struct ptl_map_bucket *buckets;
    size_t count;
};

struct ptl_map_bucket *
ptl_map_find_or_alloc_bucket(struct ptl_map_bucket_array *bucket_array,
                             uint64_t hash);

size_t ptl_map_find_index(const struct ptl_map_bucket_array *bucket_array,
                          uint64_t hash);

void ptl_map_resize(struct ptl_map_bucket_array *bucket_array, size_t count);

#define PTL_MAP_INIT(TAG)                                                      \
    { .array = TAG##_array() }

#define PTL_TEMPLATE_MAP(KEY_TYPE, VALUE_TYPE, TAG)                            \
    PTL_TEMPLATE_ARRAY(VALUE_TYPE, TAG##_array)                                \
    static inline uint64_t TAG##_hash(const KEY_TYPE *key);                    \
                                                                               \
    struct TAG {                                                               \
        struct TAG##_array array;                                              \
        struct ptl_map_bucket_array bucket_array;                              \
    };                                                                         \
                                                                               \
    static inline struct TAG TAG(void) {                                       \
        return (struct TAG)PTL_MAP_INIT(TAG);                                  \
    }                                                                          \
                                                                               \
    static inline void TAG##_set(struct TAG *map, const KEY_TYPE *key,         \
                                 const VALUE_TYPE *value) {                    \
        struct ptl_map_bucket *bucket =                                        \
            ptl_map_find_or_alloc_bucket(&map->bucket_array, TAG##_hash(key)); \
        if (bucket->value.index < map->array.info.len) {                       \
            map->array.elems[bucket->value.index] = *value;                    \
        } else {                                                               \
            TAG##_array_push(&map->array, value);                              \
            bucket->value.index = map->array.info.len - 1;                     \
        }                                                                      \
    }                                                                          \
                                                                               \
    static inline VALUE_TYPE *TAG##_get(struct TAG *map,                       \
                                        const KEY_TYPE *key) {                 \
        const size_t index =                                                   \
            ptl_map_find_index(&map->bucket_array, TAG##_hash(key));           \
        return index < map->array.info.len ? &map->array.elems[index] : NULL;  \
    }                                                                          \
                                                                               \
    static inline void TAG##_resize(struct TAG *map, size_t count_buckets) {   \
        ptl_map_resize(&map->bucket_array, count_buckets);                     \
    }

#endif /* MAP_D8A011B1_50B6_4258_B821_C7AEC6BE0C29_H */
