#include "ptl/list.h"

void ptl_list_insert(void **list_left, void *list_right) {
    while (*list_left != NULL) {
        list_left = *list_left;
    }
    *list_left = list_right;
}

void ptl_list_free(void **list) {
    while (list != NULL) {
        void **next = *list;
        free(list);
        list = next;
    }
}
