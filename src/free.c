#include <stddef.h> // size_t
#include <stdlib.h> // free()

#ifdef BALLOC_SAFE
 #include <string.h> // memset()
#endif

#include "balloc.h"

void* ba_free(void* ptr) {
    if (ptr == NULL) return ptr;

    // re-adjust pointer back to where we allocated it
    ptr = (void*) ptr - BALLOC_PREFIX;

#ifdef BALLOC_SAFE
    memset(ptr, '\0', (size_t) *((char*) ptr) + BALLOC_PREFIX);
#endif

    free(ptr);

    // return NULL, which will replace old ptr value
    return NULL;
}
