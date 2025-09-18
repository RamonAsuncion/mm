#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_

#include <stdio.h>
#include <stdbool.h>

#include "dlist.h"
#include "dnode.h"

extern struct dlist *free_list;
extern struct dlist *allocated_list;

void *malloc(size_t size);
void free(void *ptr);

/* Internal API (used by memory_test) */

/**
 * @brief Allocate a block of memory (best-fit)
 * @param size The size of the block to allocate
 * @return A pointer to the memory if successful, NULL otherwise
 */
void *allocate(size_t size);
/**
 * @brief Initialize the allocator
 * @param size The size of the memory to be allocated
 * @return 0 on success, -1 on failure
 */
int allocator_init(size_t size);
void *best_fit(size_t size);
int deallocate(void *ptr);

#endif /* _ALLOCATOR_H_ */
