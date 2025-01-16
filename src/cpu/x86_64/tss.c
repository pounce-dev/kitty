//
// Created by AIDAN on 9/17/2024.
//

#include "tss.h"
#include "../../kernel/memory.h"
#include "gdt.h"

void setup_tss(task_state_segment* tss) {
    tss->io_map_base_address = (uint16_t) sizeof (task_state_segment);
    uint64_t address = (uint64_t) tss;
    GDT.tss_0 = ((uint32_t) sizeof (task_state_segment) & 0xFFFF) | ((address & 0xFFFF) << 16);
    GDT.tss_1 = (((address) >> 16) & 0xFF) | 0x8000 | 0x0900 | ((uint32_t)sizeof (task_state_segment) & 0x000F0000) | (address & 0xFF000000);
    GDT.tss_2 = address >> 32;
    GDT.tss_3 = 0;
    asm volatile("lgdt %0" : : "m" (GDT.size));
    asm inline volatile ("mov $0x28, %ax");
    asm inline volatile ("ltr %ax");
}

void set_kernel_stack(task_state_segment* tss, uint64_t stack_address) {
    tss->ist7 = stack_address;
    tss->ist6 = stack_address;
    tss->ist5 = stack_address;
    tss->ist4 = stack_address;
    tss->ist3 = stack_address;
    tss->ist2 = stack_address;
    tss->ist1 = stack_address;
    tss->rsp0 = stack_address;
    tss->rsp1 = stack_address;
    tss->rsp2 = stack_address;

}