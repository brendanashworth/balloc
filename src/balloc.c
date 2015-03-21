#include <stddef.h> // size_t
#include <stdlib.h> // malloc(), free(), realloc()
#include <assert.h> // assert()

#ifdef BALLOC_SAFE
 #include <string.h> // memset()
#endif

#define BALLOC_PREFIX sizeof(size_t)

#include "balloc.h"

void* ba_alloc(size_t size) {
    void* ptr = malloc(size + BALLOC_PREFIX);

    // malloc() returns NULL, ran out of memory
    assert(ptr != NULL);

#ifdef BALLOC_SAFE
    memset(ptr, '\0', size);
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
    memset(ptr, '\0', (size_t) *((char*) ptr) );
#endif

    free(ptr);

    // return NULL, which will replace old ptr value
    return NULL;
}

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

size_t ba_size(void* ptr) {
    if (ptr == NULL) return 0;

    // pointer arithmetic on void* is disallowed, use char* instead
    return (size_t) *((char*) ptr - BALLOC_PREFIX);
}
