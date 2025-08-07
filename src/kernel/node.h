//
// Created by CARSON on 5/27/2025
//

#ifndef KITTY_NODE_H
#define KITTY_NODE_H

#include "stdint.h"
#include "../util/list.h"
#include <stdint.h>

typedef uint64_t node_descriptor;
typedef uint64_t node_type;
extern klist_t node_list;

struct node_interface {
    void* open_func;
    void* close_func;
    void* read_func;
    void* write_func;
    void* symlink_func;
    void* create_func;
};

#endif // KITTY_NODE_H
