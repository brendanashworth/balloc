// test ba_size
#include <assert.h> // assert()

#include "balloc.h"

int main() {
    // ba_size should return correct size
    {
        void* memory = ba_alloc(13);

        // after allocating, ba_size should return the correct size
        assert(ba_size(memory) == 13);

        memory = ba_free(memory);
    }

    // ba_size should return 0 when checking against NULL
    {
        assert(ba_size(NULL) == 0);
    }

    return 0;
}
