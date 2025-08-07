//
// Created by AIDAN on 8/19/2024.
//

#ifndef KITTY_MEMORY_H
#define KITTY_MEMORY_H
#include "stdint.h"

/*
 * Kernel Memory Allocation Functions:
 *
 * All kernel memory allocation functions have the suffix "malloc", which stands for memory allocate.
 * The following prefix characters (added in the order they appear here) determines the type of allocation to take place:
 *
 * "k" - Allocate kernel memory.
 * "z" - Zero the memory to be allocated.
 * "a" - Allocate an array.
 *
 * Parameters:
 *
 * "type_size" determines the size of the type in bytes.
 * "array_size" determines the size of the array. Memory to be allocated is multiplied by type_size.
 */

char * kmalloc(uint64_t type_size);
char * kamalloc(uint64_t type_size, uint64_t array_size);
char * kzamalloc(uint64_t type_size, uint64_t array_size);
void kfree(char* mem_address);
void* kmemcpy(void* dest, const void* src, uint64_t size);
void* krealloc(void* old_ptr, uint64_t old_size, uint64_t new_size);
#endif //KITTY_MEMORY_H
