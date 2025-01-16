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
    char * address = free_base_address;
    // zero the memory TODO verify that this actually works...
    for (uint64_t i = 0; i < (type_size * array_size); i++) {
        *(free_base_address + i) = 0;
    }
    free_base_address += type_size * array_size;
    return address;
}

void free(char* mem_address) {
}