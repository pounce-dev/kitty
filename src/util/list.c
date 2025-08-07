//
// Created by AIDAN on 5/27/2025.
//

#include "list.h"
#include "../kernel/memory.h"
#include "../driver/video/vga.h"

void klist_init(klist_t* klist, uint64_t type_size) {
    klist->length = 0;
    klist->size = 0;
    klist->type_size = type_size;
    klist->pointer = 0;
}

klist_t* klist_create(uint64_t type_size) {
    klist_t* klist = (klist_t*) kmalloc(sizeof(klist_t));
    klist_init(klist, type_size);
    return klist;
}

void klist_add(klist_t* klist, void* item) {
    if (klist->length >= klist->size) {
        uint64_t old_size = klist->size;
        uint64_t new_size = (old_size == 0) ? 4 : old_size * 2;
        uint64_t old_bytes = old_size * klist->type_size;
        uint64_t new_bytes = new_size * klist->type_size;

        void* new_pointer = krealloc(klist->pointer, old_bytes, new_bytes);
        klist->pointer = new_pointer;
        klist->size = new_size;
    }

    void* destination = (char*)klist->pointer + (klist->length * klist->type_size);
    kmemcpy(destination, item, klist->type_size);
    klist->length++;
}

void* klist_get(klist_t* klist, uint64_t index) {
    if (index >= klist->length) {
        return 0; // Out-of-bounds access
    }

    return (char*)klist->pointer + (index * klist->type_size);
}