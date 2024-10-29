#ifndef HASH_CC3F1BDE_ADCB_4436_9423_D2F077580456_H
#define HASH_CC3F1BDE_ADCB_4436_9423_D2F077580456_H
#include <stdint.h>
#include <stddef.h>

uint64_t ptl_hash_djb2(const void *data, size_t size);
uint64_t ptl_hash_cstring_djb2(const char *string);

#endif /* HASH_CC3F1BDE_ADCB_4436_9423_D2F077580456_H */
