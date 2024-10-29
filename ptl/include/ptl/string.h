#ifndef STRING_F2617B73_6416_4467_94C0_16FCB157E1C6_H
#define STRING_F2617B73_6416_4467_94C0_16FCB157E1C6_H
#include <stddef.h>

struct ptl_static_string {
    const char *const characters;
    const size_t length;
};

struct ptl_string {
    char *characters;
    size_t length;
};

#define PTL_STATIC_STRING_INIT(STRING_LITERAL)                                 \
    { .characters = STRING_LITERAL, .length = sizeof(STRING_LITERAL) - 1 }

#define ptl_static_string(string)                                              \
    (struct ptl_static_string) PTL_STATIC_STRING_INIT(string)

#endif /* STRING_F2617B73_6416_4467_94C0_16FCB157E1C6_H */
