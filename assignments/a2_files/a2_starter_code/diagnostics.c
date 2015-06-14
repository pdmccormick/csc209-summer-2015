/*
 * diagnostics.c
 * =============
 *
 * These are diagnostic helper functions which will show you the current
 * contents of the heap.
 */

#include <ctype.h>
#include <stdio.h>
#include <stddef.h>

#include "heap209.h"
#include "diagnostics.h"

// Local helper functions
static void show_list(Chunk *list);
static void dump_memory(void *buf, size_t size);

/**
 * Helper function to show each element of a linked list of Chunk's.
 */
static void show_list(Chunk *list)
{
    // TODO FIXME: Implement this function using the following `printf` format string:
    //printf("    addr=%p size=%lu\n", ... , ... );
}

/**
 * Shows a summary of all allocated chunks within the heap.
 */
void show_allocated()
{
    show_list(alloc_list);
}

/**
 * Shows a summary of all free chunks within the heap.
 */
void show_free()
{
    show_list(free_list);
}

/**
 * Shows a mixed hexadecimal+ASCII dump for all allocated chunks within the
 * heap.
 */
void hexdump_heap()
{
    Chunk *cur = alloc_list;

    while (cur) {
        printf("SIZE = %lu:\n", cur->size);
        dump_memory(cur->addr, cur->size);

        if (cur->next) {
            printf("\n");
        }

        cur = cur->next;
    }
}

/**
 * Helper function to print the contents of memory in the same format as
 * hexdump(1) with the `-C` option.
 */
static void dump_memory(void *buf, size_t size)
{
    const int bytes_per_line = 16;
    const int bytes_per_group = bytes_per_line / 2;

    void *line;
    void *end = buf + size;

    for (line = buf; line < end; line += bytes_per_line) {
        printf("%p  ", line);

        /* Print groups of hex digits */
        int i;
        void *cur;
        for (cur = line, i = 1; cur < (line + bytes_per_line); cur++, i++) {
            if (cur < end) {
                printf("%02x ", *((unsigned char *) cur));
            }
            else {
                printf("   ");
            }

            if (i % bytes_per_group == 0) {
                printf(" ");
            }
        }

        /* Print the printable ASCII characters */
        printf("|");
        for (cur = line, i = 1; cur < (line + bytes_per_line) && cur < end; cur++, i++) {
            unsigned char ch = *((unsigned char *) cur);
            if (isprint(ch)) {
                printf("%c", ch);
            }
            else {
                printf(".");
            }
        }
        printf("|\n");
    }
}
