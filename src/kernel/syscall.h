//
// Created by AIDAN on 5/13/2025.
//

#ifndef KITTY_SYSCALL_H
#define KITTY_SYSCALL_H

#include <stdbool.h>
#include "stdint.h"

/*
 * bits definitions are to ensure that the parameters are
 * consistent across all systems
 */

typedef uint64_t node_descriptor;
typedef uint64_t pointer;
typedef uint64_t number;
typedef uint64_t boolean;
typedef uint64_t node_type;

/*
 * open(pointer path)
 *
 * opens a file and retrieves a node descriptor.
 *
 * path is a pointer to a null terminated string containing the path
 * to the child node.
 */
void open(pointer path, pointer nd);

/*
 * close(node_descriptor nd)
 *
 * close a node, invalidating the node descriptor.
 *
 * nd is the node descriptor to be terminated.
 */
void close(node_descriptor nd);

/*
 * read(node_descriptor nd, pointer offset, pointer buffer, number length)
 *
 * reads from a node, putting the data at the offset specified to the buffer
 */
void read(node_descriptor nd, number offset, pointer buffer, number length);

/*
 * write(node_descriptor nd, number offset, pointer buffer, number length)
 *
 * write to a given node.
 *
 * nd is the node to be written to.
 * offset is the offset in node where the buffer will be written to.
 * length is the length to write from.
 */
void write(node_descriptor nd, number offset, pointer buffer, number length);

/*
 * symlink(node_descriptor nd, pointer path, boolean writeable)
 *
 * nd is the node to symlink, pointer path is the
 */
void symlink(node_descriptor nd, pointer path, boolean writeable);

/*
 * create(pointer nd, pointer path, node_type type)
 *
 * nd - the pointer to the new node descriptor
 *
 * path - the pointer to the string with the path the new node is to be created at
 *
 * type - the type of the new node to create
 */
void create(pointer nd, pointer path, node_type type);

#endif //KITTY_SYSCALL_H
