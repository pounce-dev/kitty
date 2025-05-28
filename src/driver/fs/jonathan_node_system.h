//
// Created by CARSON on 5/27/2025
//

#ifndef KITTY_JNS_H
#define KITTY_JNS_H

#include "stdint.h"
#include "../../util/list.h"
#include <stdint.h>

struct jon_node {
    char* name;
    klist children;
    uint64_t sector_start;
    uint64_t sector_length;
};

#endif // KITTY_JNS_H
