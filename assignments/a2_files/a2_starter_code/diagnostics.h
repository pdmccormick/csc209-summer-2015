/**
 * diagnostics.h
 * =============
 *
 * These are diagnostic helper functions which will show you the current
 * contents of the heap.
 */

#ifndef __DIAGNOSTICS_H
#define __DIAGNOSTICS_H

/**
 * Shows a summary of all allocated chunks within the heap.
 */
void show_allocated();

/**
 * Shows a summary of all free chunks within the heap.
 */
void show_free();

/**
 * Shows a mixed hexadecimal+ASCII dump for all allocated chunks within the
 * heap.
 */
void hexdump_heap();

#endif /* __DIAGNOSTICS_H */
