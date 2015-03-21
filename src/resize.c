#include <stddef.h> // size_t
#include <stdlib.h> // realloc()

#ifdef BALLOC_SAFE
 #include <string.h> // memset()
#endif

#include "balloc.h"

void* ba_resize(void* ptr, size_t size) {
    if (ptr == NULL) return ba_alloc(size);

#ifdef BALLOC_SAFE
    size_t old = ba_size(ptr);

    // if removing space, must null
    if (old > size)
        memset(ptr + size, '\0', old - size);
#endif

    // shift in prefix
    ptr = (void*) ptr - BALLOC_PREFIX;

    ptr = realloc(ptr, size + BALLOC_PREFIX);

#ifdef BALLOC_SAFE
    // if added new space, must null
    if (size > old)
        memset(ptr + BALLOC_PREFIX + old, '\0', size - old);
#endif

    // set new size
    *((size_t*)ptr) = size;

    return (void*) ptr + BALLOC_PREFIX;
}
