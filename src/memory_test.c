#include <stdio.h>
#include <stdlib.h>
#include "allocator.h"

#define NUMBER_OF_TRIALS 10

int main(int argc, char*argv[]) {

  int r = allocator_init(500);
  if (r == -1) {
    printf("allocate init failed\n");
    exit(1);
  }

  printf("attempting to allocate memory blocks ...\n");
  void *memory_block[NUMBER_OF_TRIALS];
  int i;
  srand(0);
  for (i = 0; i < NUMBER_OF_TRIALS; i ++)  { // try allocation operations
    int block_size = rand() % 20 + 1;
    memory_block[i] = allocate(block_size);
    printf("allocate %u bytes...\n", block_size);
    if (memory_block[i] == NULL) {
      printf("alloation failed\n");
    } else {
      printf("memory address = 0x%llx\n", (unsigned long long)memory_block[i]);
    }
  }

  printf("attempting to free a few blocks...\n");
  for (i = 0; i < NUMBER_OF_TRIALS/2; i ++) { // try to free a block that has been allocated
    int which = rand() % NUMBER_OF_TRIALS;    // which block to free
    r = deallocate(memory_block[which]);
    if (r == 1) {
      printf("deallocate 0x%llx successfully\n", (unsigned long long)memory_block[which]);
    } else {
      printf("deallocate 0x%llx unsuccessfully\n", (unsigned long long)memory_block[which]);
    }
  }

  /*
   * print free_list and allocated_list
   */
  printf("Free list:\n");
  dlist_print(free_list);

  printf("Allocated list:\n");
  dlist_print(allocated_list);

  return 0;
}
