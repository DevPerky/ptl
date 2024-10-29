#ifndef LIST_B9A87D11_0DD8_4C06_913E_7814D68717C1_H
#define LIST_B9A87D11_0DD8_4C06_913E_7814D68717C1_H
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

void ptl_list_insert(void **list_left, void *list_right);
void ptl_list_free(void **list);

#define PTL_LIST_INIT(VALUE)                                                   \
    { .next = NULL, .value = VALUE }

#define PTL_TEMPLATE_LIST(TYPE, TAG)                                           \
    struct TAG {                                                               \
        struct TAG *next;                                                      \
        TYPE value;                                                            \
    };                                                                         \
    static inline struct TAG *TAG##_alloc(void) {                              \
        struct TAG *result = calloc(1, sizeof(struct TAG));                    \
        return result;                                                         \
    }                                                                          \
    static inline struct TAG *TAG##_insert(struct TAG *left,                   \
                                           struct TAG *right) {                \
        ptl_list_insert((void **)left, right);                                 \
        return left;                                                           \
    }                                                                          \
    static inline struct TAG *TAG##_prepend(struct TAG *list,                  \
                                            const TYPE *value) {               \
        struct TAG *link = TAG##_alloc();                                      \
        link->value = *value;                                                  \
        return TAG##_insert(link, list);                                       \
    }                                                                          \
    static inline void TAG##_free(struct TAG *TAG) {                           \
        ptl_list_free((void **)TAG);                                           \
    }                                                                          \
    static inline struct TAG *TAG##_find(                                      \
        struct TAG *list, bool (*predicate)(const TYPE *value)) {              \
        while (list != NULL) {                                                 \
            if (predicate(&list->value)) {                                     \
                return list;                                                   \
            } else {                                                           \
                list = list->next;                                             \
            }                                                                  \
        }                                                                      \
        return NULL;                                                           \
    }

#endif /* LIST_B9A87D11_0DD8_4C06_913E_7814D68717C1_H */
