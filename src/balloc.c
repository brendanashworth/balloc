#include <stddef.h> // size_t
#include <stdlib.h> // malloc()
#include <assert.h> // assert()

#ifdef BALLOC_SAFE
 #include <string.h> // memset()
#endif

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
