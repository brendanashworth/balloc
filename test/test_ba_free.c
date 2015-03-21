// test ba_free
#include <assert.h> // assert()

#include "balloc.h"

int main() {
    void* memory = ba_alloc(10);
    memory = ba_free(memory);

    // memory should now be NULL
    assert(memory == NULL);

    return 0;
}
