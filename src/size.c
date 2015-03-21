#include <stddef.h> // size_t

#include "balloc.h"

size_t ba_size(void* ptr) {
    if (ptr == NULL) return 0;

    // pointer arithmetic on void* is disallowed, use char* instead
    return (size_t) *((char*) ptr - BALLOC_PREFIX);
}
