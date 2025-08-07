//
// Created by AIDAN PRATT on 10/28/2023.
//

#include <stdint.h>
#include "kitty.h"
#include "../driver/video/vga.h"
#include "../cpu/cpu_options.h"
#include "memory.h"
#include "syscall.h"
#include "../util/list.h"
#include "api/logger.h"
#ifdef x86_64
#include "../cpu/x86_64/idt.h"
#include "../cpu/x86_64/tss.h"
#include "../cpu/x86_64/usermode.h"


#endif

char kitty_process_name[] = "kitty";
logger_t kitty_main_logger = {
        .logger_name = kitty_process_name
};
void kitty() {
    register_logger(&kitty_main_logger);

    // Perform initial setup for CPUs
#ifdef Intel_CPU
    vga3_init();
    log_message_t logMessage = {
            .log_message = "Starting Kitty",
            .level = INFO,
            .logger = &kitty_main_logger
    };
    klog(&logMessage);
    task_state_segment *tss = (task_state_segment*) kmalloc(sizeof (task_state_segment));
    void* stack_bottom = kmalloc(8096);
    void* stack_top = stack_bottom + 8096;
    set_kernel_stack(tss, (uint64_t) stack_top);
    setup_tss(tss);
    init_idt();
    write_string_at(VGA3_WHITE, "idt loaded", 0,15);
    kfree(kmalloc(1));
    enter_usermode(tss);
#endif
#ifdef ARM_CPU

#endif
    while (1);
}