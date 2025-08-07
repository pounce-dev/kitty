//
// Created by AIDAN on 8/19/2024.
//

#include "memory.h"

char * free_base_address = (char *) 0x10000;
char * kmalloc(uint64_t type_size) {
    char * address = free_base_address;
    free_base_address += type_size;
    return address;
}

char * kzmalloc(uint64_t type_size) {
    char * address = free_base_address;
    free_base_address += type_size;
    return address;
}


char * kamalloc(uint64_t type_size, uint64_t array_size) {
    char * address = free_base_address;
    free_base_address += type_size * array_size;
    return address;
}

char * kzamalloc(uint64_t type_size, uint64_t array_size) {
    uint64_t total_size = type_size * array_size;
    char * address = free_base_address;
    for (uint64_t i = 0; i < total_size; i++) {
        address[i] = 0;
    }
    free_base_address += total_size;
    return address;
}

void kfree(char* mem_address) {
}

void* kmemcpy(void* dest, const void* src, uint64_t size) {
    char* d = (char*)dest;
    const char* s = (const char*)src;
    for (uint64_t i = 0; i < size; i++) {
        d[i] = s[i];
    }
    return dest;
}

void* krealloc(void* old_ptr, uint64_t old_size, uint64_t new_size) {
    void* new_ptr = kmalloc(new_size);
    if (old_ptr != 0 && old_size > 0) {
        kmemcpy(new_ptr, old_ptr, old_size);
        kfree(old_ptr);
    }
    return new_ptr;
}