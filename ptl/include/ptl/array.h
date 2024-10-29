#ifndef ARRAY_E051236F_486F_4721_987F_A30A9E238CBA_H
#define ARRAY_E051236F_486F_4721_987F_A30A9E238CBA_H
#include <stddef.h>

struct ptl_array_info {
    size_t cap;
    size_t len;
    const size_t elem_size;
};

void *ptl_array_push(void *dest, const void *src, struct ptl_array_info *info);

#define PTL_ARRAY_INIT(TAG)                                                    \
    { .info.elem_size = sizeof(((struct TAG *)0)->elems[0]) }

#define PTL_TEMPLATE_ARRAY(TYPE, TAG)                                          \
    struct TAG {                                                               \
        struct ptl_array_info info;                                            \
        TYPE *elems;                                                           \
    };                                                                         \
    static inline struct TAG TAG(void) {                                       \
        return (struct TAG)PTL_ARRAY_INIT(TAG);                                \
    }                                                                          \
                                                                               \
    static inline void TAG##_push(struct TAG *array, const TYPE *elem) {       \
        array->elems = ptl_array_push(array->elems, elem, &array->info);       \
    }

#endif /* ARRAY_E051236F_486F_4721_987F_A30A9E238CBA_H */
