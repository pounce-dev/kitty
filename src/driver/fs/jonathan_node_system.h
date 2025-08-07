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
    klist_t children;
    uint64_t sector_start;
    char symlinked;
};

struct meta_jon {
    uint64_t next_sector;
    uint64_t data_stop;
};

#endif // KITTY_JNS_H
