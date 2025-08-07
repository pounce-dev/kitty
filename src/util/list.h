//
// Created by AIDAN on 5/27/2025.
//

#ifndef KITTY_LIST_H
#define KITTY_LIST_H

#include "stdint.h"

typedef struct {
    uint64_t length;
    uint64_t size;
    uint64_t type_size;
    void* pointer;
} klist_t;

/*
 * init(klist_t* klist, uint64_t size)
 *
 * Initializes the values in a new klist.
 *
 * size - the size of the data type to store in the list, in bytes.
 *
 * klist - pointer for klist, you must allocate.
 */
void klist_init(klist_t* klist, uint64_t type_size);

/*
 * create(uint64_t type_size)
 *
 * Creates a new klist and returns a pointer to it, allocated in kernel heap.
 *
 * type_size - the size of the data type to store in the list, in bytes.
 *
 *
 */

klist_t* klist_create(uint64_t type_size);

/*
 * klist_add(klist_t* klist, void* item)
 *
 * Adds a new item to the list.
 */
void klist_add(klist_t* klist, void* item);

/*
 * void* klist_get(klist_t* klist, uint64_t index)
 *
 * returns the pointer to the item at the specified index in the list.
 *
 * 0 if out of bounds.
 */
void* klist_get(klist_t* klist, uint64_t index);

#endif //KITTY_LIST_H
