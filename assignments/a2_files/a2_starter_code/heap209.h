/**
 * heap209.h
 * =========
 *
 * Implements a small heap space organized into chunks of free and allocated
 * space (maintained through linked lists.)
 */

#ifndef __HEAP209_H
#define __HEAP209_H

#include <stddef.h>

typedef struct _Chunk Chunk;

/**
 * A chunk is a piece of heap metadata used to track a sub-region as either
 * free or allocated.
 */
struct _Chunk {
    /** Starting address of the memory for this chunk. */
    void *addr;

    /** The number of bytes available for use starting at address `addr`. */
    size_t size;

    /** Link to the next chunk in the list */
    Chunk *next;
};

/**
 * NB: These global variables will be instantiated inside of and thus available
 * from `heap209.c`.
 */
extern void *heap_region;
extern Chunk *free_list;
extern Chunk *alloc_list;

/**
 * Allocate `nbytes` from the heap, and returns a pointer to the start of the
 * freshly allocated memory. Returns NULL if there is insufficient free
 * contiguous space.
 */
void *malloc209(size_t nbytes);

/**
 * Release the previously allocated memory pointed to by `addr` back into the
 * heap. Returns 0 on success, or -1 if `addr` was not found in the allocated
 * chunk list.
 */
int free209(void *addr);

/**
 * Initialize a large piece of contiguous memory to serve as the heap region.
 */
void heap209_init(size_t heap_size);

/**
 * Clean up all chunk metadata associated with the heap.
 */
void heap209_cleanup(void);

#endif /* __HEAP209_H */
