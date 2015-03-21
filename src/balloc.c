#include <stddef.h> // size_t
#include <stdlib.h> // malloc(), free()
#include <assert.h> // assert()

#ifdef BALLOC_SAFE
 #include <string.h>
#endif

#define BALLOC_PREFIX sizeof(size_t)

#include "balloc.h"

void* ba_alloc(size_t size) {
    void* ptr = malloc(size + BALLOC_PREFIX);

    // malloc() returns NULL, ran out of memory
    assert(ptr != NULL);

#ifdef BALLOC_SAFE
    memset(*ptr, '\0', size);
#endif

    // write size before pointer
    *((size_t*)ptr) = size;

    return (void*) ptr + BALLOC_PREFIX;
}

void* ba_free(void* ptr) {
    if (ptr == NULL) return ptr;

    // re-adjust pointer back to where we allocated it
    ptr = (void*) ptr - BALLOC_PREFIX;

#ifdef BALLOC_SAFE
    size_t size = *ptr;
    memset(*ptr, '\0', size);
#endif

    free(ptr);

    // return NULL, which will replace old ptr value
    return NULL;
}

size_t ba_size(void* ptr) {
    if (ptr == NULL) return 0;

    // pointer arithmetic on void* is disallowed, use char* instead
    return (size_t) *((char*) ptr - BALLOC_PREFIX);
}
