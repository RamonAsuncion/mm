#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "allocator.h"

void test_allocate(int block_size, int expect_fail)
{
  void *memory_block = allocate(block_size);
  printf("Attempting to allocate %u bytes...\n", block_size);
  if (memory_block == NULL) {
    printf("Allocation failed\n");
    if (!expect_fail) exit(1);
  } else {
    printf("Memory address = 0x%llx\n", (unsigned long long)memory_block);
  }
  deallocate(memory_block);
}

void test_deallocate(void *memory_block, int expect_fail)
{
  int r = deallocate(memory_block);
  if (r != 1) {
    printf("Deallocate 0x%llx unsuccessfully\n", (unsigned long long)memory_block);
    if (!expect_fail) exit(1);
  } else {
    printf("Deallocate 0x%llx successfully\n", (unsigned long long)memory_block);
  }
}

int main(void)
{
  int r = allocator_init(500);
  if (r == -1) {
    printf("Allocator init failed\n");
    exit(1);
  }

  // Test allocating zero bytes
  test_allocate(0, 0);

  // Test allocating more memory than available
  test_allocate(1000, 1);

  // Test allocating exact memory size
  test_allocate(500, 0);

  // Test allocating and deallocating in different orders
  void *memory_block1 = allocate(20);
  void *memory_block2 = allocate(40);
  test_deallocate(memory_block2, 0);
  test_deallocate(memory_block1, 0);

  // Test reallocating memory blocks
  void *memory_block3 = allocate(20);
  void *memory_block4 = realloc(memory_block3, 40);
  test_deallocate(memory_block4, 0);

  // Test deallocating a block that was not allocated
  test_deallocate(NULL, 1);

  // Test allocating and deallocating a large number of blocks
  for (int i = 0; i < 10; i++) {
  void *memory_block = allocate(10);
  test_deallocate(memory_block, 0);
  }

  // Print free_list and allocated_list
  printf("Free list:\n");
  dlist_print(free_list);

  printf("Allocated list:\n");
  dlist_print(allocated_list);

  printf("All tests passed\n");

  return 0;
}

