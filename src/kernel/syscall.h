//
// Created by AIDAN on 5/13/2025.
//

#ifndef KITTY_SYSCALL_H
#define KITTY_SYSCALL_H

#include <stdbool.h>
#include "../cpu/cpu_options.h"
#include "stdint.h"

typedef BITS_TYPE node_descriptor;

void open(char* path);
void close(node_descriptor nd);
void read(node_descriptor nd, BITS_TYPE offset, BITS_TYPE buffer, BITS_TYPE length);
void write(node_descriptor nd);
void symlink(node_descriptor nd, char* path, bool writeable);
void create(node_descriptor nd, char* path);

#endif //KITTY_SYSCALL_H
