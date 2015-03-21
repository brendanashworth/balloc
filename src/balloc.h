#ifndef _BALLOC_H
#define _BALLOC_H

#include <string.h>

#define BALLOC_PREFIX sizeof(size_t)

/**
 * Dynamically allocates a section of memory for access.
 * @param size The size of memory to allocate.
 * @return     A pointer to the newly allocated memory.
 */
void* ba_alloc(size_t size);

/**
 * Dynamically frees a section of memory previously allocated with ba_alloc().
 * @param ptr The pointer to the first index of the memory.
 * @return    A pointer to NULL (should be assigned to the pointer).
 */
void* ba_free(void* ptr);

/**
 * Resize an allocated section of memory to the new size.
 * @param ptr  The pointer of the previously allocated memory.
 * @param size The size of the new allocation (NOT a DIFFERENCE from the
 *             original pointer, i.e. 8 + 4).
 * @return     Newly allocated memory pointer. Might not be at same pointer
 *             as before.
 */
void* ba_resize(void* ptr, size_t size);

/**
 * Retrieve the size of the allocated memory.
 * @param  ptr The pointer to the first index of the memory.
 * @return     The size passed to ba_alloc() when first allocated.
 */
size_t ba_size(void* ptr);

#endif