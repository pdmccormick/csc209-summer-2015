/**
 * heap209.c
 * =========
 *
 * Implements a small heap space organized into chunks of free and allocated
 * space (maintained through linked lists.)
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/mman.h>

#include "heap209.h"

void *heap_region = NULL;
Chunk *free_list = NULL;
Chunk *alloc_list = NULL;

/**
 * Allocate `nbytes` from the heap, and returns a pointer to the start of the
 * freshly allocated memory. Returns NULL if there is insufficient free
 * contiguous space.
 */
void *malloc209(size_t nbytes)
{
    /* TODO FIXME: Implement this function. */
    return NULL;
}

/**
 * Release the previously allocated memory pointed to by `addr` back into the
 * heap. Returns 0 on success, or -1 if `addr` was not found in the allocated
 * chunk list.
 */
int free209(void *addr)
{
    /* TODO FIXME: Implement this function. */
    return -1;
    return 0;
}

/**
 * Initialize a large piece of contiguous memory to serve as the heap region.
 *
 * NB: mmap(1) is a system call that is used to create new regions within the
 * virtual (logical) address space of the calling process. It can be used to
 * map the contents of files into memory, so that you can directly access the
 * file data through memory pointers instead of requiring explicit read and
 * write function calls. Here we are using it in a slightly different way in
 * order to negotiate with the operating system to give us a large region of
 * memory for our private use (without any files being involved.)
 *
 * The `mmap` call will return a `void *` pointer to the allocated memory. It's
 * arguments are:
 *
 *  - NULL: let the kernel choose where to place the memory in the address
 *      space.
 *  - PROT_READ | PROT_WRITE: bitmask to indicate memory will be used for
 *      reading and writing
 *  - MAP_PRIVATE | MAP_ANON: create an anonymous mapping that is private (only
 *      visible) to this process
 *  - -1: no file descriptor as this mapping is not backed by a file
 *  - 0: no offest, again because no files are involved
 */
void heap209_init(size_t heap_size)
{
    if (heap_region) {
        fprintf(stderr, "ERROR: Cannot re-initialize the 209 heap\n");
        return;
    }

    heap_region = mmap(NULL, heap_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);

    if (heap_region == MAP_FAILED) {
        perror("mmap");
        exit(-1);
    }

    // TODO FIXME: Initialize the heap metadata lists
}

/**
 * Clean up all chunk metadata associated with the heap.
 */
void heap209_cleanup(void)
{
    // TODO FIXME: Implement cleanup of all heap metadata
}
