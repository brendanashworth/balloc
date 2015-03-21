// test ba_resize
#include <assert.h> // assert()
#include <string.h> // stpcpy()

#include "balloc.h"

int main() {
	// test realloc with less memory
	{
		void* memory = ba_alloc(10);

		// give the memory some value
		stpcpy(memory, "123456789");

		memory = ba_resize(memory, 8);

		// should be reachable memory and preserve same value (go to 8 because
		// this will be missing a null terminator)
		assert(strncmp(memory, "12345678", 8) == 0);

		// size should yield new value
		assert(ba_size(memory) == 8);

		memory = ba_free(memory);
	}
    
    // test with more memory
    {
    	void* memory = ba_alloc(10);

    	// give some value
    	stpcpy(memory, "123456789");

    	// resize to 14
    	memory = ba_resize(memory, 14);

    	// should have copied memory over (including null term)
    	assert(strcmp(memory, "123456789") == 0);
    	assert(strlen(memory) == 9);

		// should have four new memory spaces (+9 for null term)
		stpcpy(memory + 9, "abcd");

		assert(strcmp(memory, "123456789abcd") == 0);
		assert(strlen(memory) == 13);
		
		// free
		memory = ba_free(memory);
    }

    // test with same amount of memory
    {
    	void* memory = ba_alloc(10);

    	stpcpy(memory, "123456789");

    	// don't change memory size
    	memory = ba_resize(memory, 10);

    	// should be same
    	assert(strcmp(memory, "123456789") == 0);
    	assert(strlen(memory) == 9);

    	// free
    	memory = ba_free(memory);
    }

    // test with unallocated pointer
    {
    	void* memory = NULL;
    	memory = ba_resize(memory, 10);

    	// should behave as ba_alloc
    	assert(memory != NULL);

    	memory = ba_free(memory);
    }

    return 0;
}
