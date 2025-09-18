#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <sys/mman.h>

#include "../include/allocator.h"

struct dlist* free_list;
struct dlist* allocated_list;

int allocator_init(size_t size)
{
  free_list = dlist_create();
  allocated_list = dlist_create();
  void* pool = mmap(NULL, size, PROT_READ | PROT_WRITE,
                    MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

  if (pool == MAP_FAILED)
    return -1;

  dlist_add_front(free_list, pool, size);
  return 0;
}

void *allocate(size_t size)
{
  return best_fit(size);
}

void *malloc(size_t size) 
{
  return allocate(size);
}

void free(void *ptr)
{
  deallocate(ptr);
}

int deallocate(void *ptr)
{
  struct dnode* node = allocated_list->front;
  while (node != NULL) {
    if (node->data == ptr) {
      dlist_find_remove(allocated_list, node->data);
      dlist_add_front(free_list, node->data, node->size);
      return 1;
    }
    node=node->next;
  }
  return -1;
}

void* best_fit(size_t size)
{
  struct dnode* node = free_list->front;
  struct dnode* best_node = NULL;
  size_t best_size = SIZE_MAX;

  while (node != NULL) {
    if (node->size >= size && node->size < best_size) {
      best_node = node;
      best_size = node->size;
    }
    node = node->next;
  }

  if (best_node == NULL)
    return NULL;

  /* Remove the chosen free block from the free list */
  void* base = best_node->data;
  size_t original_size = best_node->size;
  dlist_find_remove(free_list, base);

  /* If block is larger than requested, split: allocated part is base,
     leftover is base + size with size original_size - size */
  if (original_size > size) {
    void* leftover = (char*)base + size;
    size_t leftover_size = original_size - size;
    dlist_add_front(free_list, leftover, leftover_size);
    dlist_add_front(allocated_list, base, size);
  } else {
    /* exact fit */
    dlist_add_front(allocated_list, base, original_size);
  }

  return base;
}

