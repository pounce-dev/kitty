//
// Created by AIDAN PRATT on 10/28/2023.
//

#include <stdint.h>
#include "kitty.h"
#include "../driver/video/vga.h"
#include "../cpu/cpu_options.h"
#include "memory.h"
#ifdef x86_64
#include "../cpu/x86_64/idt.h"
#include "../cpu/x86_64/tss.h"
#include "../cpu/x86_64/usermode.h"
#endif

void kitty() {
    // Perform initial setup for CPUs
#ifdef Intel_CPU
    write_string(vga3_color(VGA3_CYAN, VGA3_RED),"Welcome to the Kitty Kernel");
    task_state_segment *tss = (task_state_segment*) kmalloc(sizeof (task_state_segment));
    void* stack_bottom = kzamalloc(sizeof (uint8_t), 8096);
    void* stack_top = stack_bottom + 8095;
    set_kernel_stack(tss, (uint64_t) stack_top);
    setup_tss(tss);
    init_idt();
    write_string_at(VGA3_WHITE, "idt loaded", 0,15);
    free(kmalloc(1));
    enter_usermode(tss);
#endif
#ifdef ARM_CPU

#endif
    while (1);
}