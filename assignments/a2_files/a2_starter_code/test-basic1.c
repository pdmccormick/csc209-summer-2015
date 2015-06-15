/**
 * Basic Test for 209 Heap
 * =======================
 *
 * Performs a few straight forward allocations and one follow-up deallocation,
 * showing the contains of the heap before and after the later.
 */

#include <stdio.h>
#include <string.h>

#include "heap209.h"
#include "diagnostics.h"

// By default our heap will be sized to 128 KiB
#define DEFAULT_HEAP_SIZE (128 * 1024)

/**
 * Helper function to display every heap diagnostic.
 */
static void show_all()
{
    printf("Allocated Chunks:\n");
    show_allocated();
    printf("\n");

    printf("Free Chunks:\n");
    show_free();
    printf("\n");

    printf("All Allocated Memory:\n");
    hexdump_heap();
    printf("\n");
}

int main(int argc, char *argv[])
{
    // Initialize the heap with the default size
    heap209_init(DEFAULT_HEAP_SIZE);

    // Allocate 5 chunks of memory
    const int num_chunks = 5;
    void *ptrs[num_chunks];
    int i;
    for (i = 0; i < num_chunks; i++) {
        size_t num_bytes = (i + 1) * 4;

        ptrs[i] = malloc209(num_bytes);
        if (!ptrs[i]) {
            printf("ERROR: Failed to allocate %zu bytes, aborting\n", num_bytes);
            return -1;
        }

        // Set each byte in the chunk to an ASCII character.
        unsigned char val = 'A' + i;
        memset(ptrs[i], val, num_bytes);
    }

    // Show the heap after the allocations
    show_all();

    // Free one piece of allocated memory and show again
    i = num_chunks / 2;
    int rc = free209(ptrs[i]);
    printf("Releasing %p with `free209` (rc=%d)\n", ptrs[i], rc);
    printf("\n");

    show_all();

    // We are done now so let's cleanup after ourselves
    heap209_cleanup();

    return 0;
}
