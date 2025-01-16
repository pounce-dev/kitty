//
// Created by AIDAN on 9/26/2024.
//

#ifndef KITTY_GDT_H
#define KITTY_GDT_H

#include "stdint.h"

struct global_descriptor_table {
    uint64_t null;
    uint64_t code;
    uint64_t data;
    uint64_t user_code;
    uint64_t user_data;
    uint32_t tss_0;
    uint32_t tss_1;
    uint32_t tss_2;
    uint32_t tss_3;
    uint16_t size;
    uint64_t offset;
}__attribute__ ((packed));

extern struct global_descriptor_table GDT;

#endif //KITTY_GDT_H
