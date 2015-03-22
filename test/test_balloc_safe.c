// test BALLOC_SAFE mode
// note: NOT an exposed function
#include <assert.h> // assert()
#include <string.h> // strcpy(), strncmp()
#include <stdio.h> // fprintf()

#include "balloc.h"

// loosely based off of freebsd's strncmp
// like so: charncmp("\0\0\0", '\0', 3) == 0;
int charncmp(char* s1, char s2, size_t n) {
    do {
        if (*s1++ != s2) return 1;
    } while (--n > 0);

    return 0;
}

int main() {
#ifndef BALLOC_SAFE
    // only run if compiled with BALLOC_SAFE defined
    fprintf(stderr, "    --> test_balloc_safe bail, no BALLOC_SAFE\n");
    return 0;
#endif

    void* memory = ba_alloc(10);

    // ensure memory is ten bytes of \0
    assert(charncmp(memory, '\0', 10) == 0);

    // throw some data into the first ten, then resize
    // it should retain the original data
    strcpy(memory, "123456789a");

    memory = ba_resize(memory, 20);

    // ensure it retained the original memory
    assert(strncmp(memory, "123456789a", 10) == 0);
    assert(strlen(memory) == 10);

    // ensure memory+10 is 10 bytes of \0
    assert(charncmp(memory + 10, '\0', 10) == 0);

    // give it some value
    strcpy(memory, "1234567891234567891");

    // free
    void *ptr = memory; // keep a local pointer
    memory = ba_free(memory);

    // this is dangerous because the memory has already been free'd
    assert(charncmp(ptr, '\0', 20) == 0);

    return 0;
}
