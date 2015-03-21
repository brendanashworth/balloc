// test ba_alloc
#include <assert.h> // assert()
#include <string.h> // stpcpy()

#include "balloc.h"

int main() {
    void* memory = ba_alloc(10);

    // after allocating, memory should not point to NULL
    assert(memory != NULL);

    // test memory by copying string of length 10
    stpcpy(memory, "123456789");

    memory = ba_free(memory);
    return 0;
}
