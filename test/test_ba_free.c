// test ba_free
#include <assert.h> // assert()

#include "balloc.h"

int main() {
    void* memory = ba_alloc(10);
    memory = ba_free(memory);

    // memory should now be NULL
    assert(memory == NULL);

    // ba_free called on an already free'd pointer should not error
    assert(ba_free(memory) == NULL);

    return 0;
}
