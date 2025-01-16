//
// Created by AIDAN on 7/3/2024.
//

#ifndef KITTY_ASCII_H
#define KITTY_ASCII_H
#include <stdint.h>
/*
 * From int takes an int argument n, destination array which must be at least length 12.
 */

void decimal_from_int32(int32_t n, char dest[12]);

void decimal_from_uint64(uint64_t n, char dest[20]);
#endif //KITTY_ASCII_H
