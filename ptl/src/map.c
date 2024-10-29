#include "ptl/map.h"
#include <assert.h>
#include <stdlib.h>

#define INDEX_RESET (~0U)

struct ptl_map_bucket *
ptl_map_find_or_alloc_bucket(struct ptl_map_bucket_array *bucket_array,
                             uint64_t hash) {
    assert(bucket_array->count != 0);
    struct ptl_map_bucket *bucket =
        &bucket_array->buckets[hash % bucket_array->count];
    while (bucket->value.hash != hash && bucket->next != NULL) {
        bucket = bucket->next;
    }
    if (bucket->value.hash != hash && bucket->value.index != INDEX_RESET) {
        bucket->next = ptl_map_bucket_alloc();
        bucket->next->value.hash = hash;
        bucket->next->value.index = INDEX_RESET;
        bucket = bucket->next;
    }
    bucket->value.hash = hash;
    return bucket;
}

size_t ptl_map_find_index(const struct ptl_map_bucket_array *bucket_array,
                          uint64_t hash) {
    struct ptl_map_bucket *bucket = &bucket_array->buckets[hash % bucket_array->count];
    while (bucket->value.hash != hash && bucket->next != NULL) {
        bucket = bucket->next;
    }
    return bucket->value.hash == hash ? bucket->value.index : INDEX_RESET;
}

void ptl_map_resize(struct ptl_map_bucket_array *bucket_array, size_t count) {
    if (count < bucket_array->count) {
        for (size_t i = count; i < bucket_array->count; i++) {
            ptl_map_bucket_free(bucket_array->buckets[i].next);
        }
    }
    bucket_array->buckets = realloc(bucket_array->buckets,
                                    count * sizeof(bucket_array->buckets[0]));
    for (size_t i = bucket_array->count; i < count; i++) {
        bucket_array->buckets[i].next = NULL;
        bucket_array->buckets[i].value.hash = 0;
        bucket_array->buckets[i].value.index = INDEX_RESET;
    }
    bucket_array->count = count;
}
