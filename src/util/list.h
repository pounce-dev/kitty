//
// Created by AIDAN on 5/27/2025.
//

#ifndef KITTY_LIST_H
#define KITTY_LIST_H

#include "stdint.h"

struct klist {
    uint64_t length;
    uint64_t size;
    void* pointer;
};

#endif //KITTY_LIST_H
