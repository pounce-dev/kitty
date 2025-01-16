//
// Created by AIDAN on 9/17/2024.
//

#ifndef KITTY_TSS_H
#define KITTY_TSS_H

#include "stdint.h"

/*
 * Task State Segment (TSS) Setup
 *
 * The kitty kernel uses software multitasking and a single TSS to
 * switch between ring 3 and ring 0. Since scheduling can (although it might not now)
 * run during a system call (the current process can switch) and a second
 * system call from a different process can switch back to ring 0, the kernel
 * stack pointer in this TSS must be updated when switching processes.
 *
 */


struct task_state_segment {
    uint32_t reserved_0;
    uint64_t rsp0;
    uint64_t rsp1;
    uint64_t rsp2;
    uint64_t reserved_1;
    uint64_t ist1;
    uint64_t ist2;
    uint64_t ist3;
    uint64_t ist4;
    uint64_t ist5;
    uint64_t ist6;
    uint64_t ist7;
    uint64_t reserved_2;
    uint16_t reserved_3;
    uint16_t io_map_base_address;
} __attribute__ ((packed));

typedef struct task_state_segment task_state_segment;

//const tss_base_address = &tss;
//
//const tss_limit = sizeof(tss) - 1;

void setup_tss(task_state_segment* tss);

void set_kernel_stack(task_state_segment* tss, uint64_t stack_address);

#endif //KITTY_TSS_H
