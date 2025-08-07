//
// Created by AIDAN PRATT on 11/1/2023.
//
/*
 * Controls VGA text mode and graphics modes
 *
 */
#include <stdint.h>
#include "vga.h"
#include "../../kernel/api/logger.h"

void vga3_logger_output(log_message_t* log_message) {
    uint8_t color;
    switch (log_message->level) {
        case DEBUG:
            color = vga3_color(VGA3_GREEN, VGA3_BLACK);
            break;
        case INFO:
            color = vga3_color(VGA3_WHITE, VGA3_BLACK);
            break;
        case WARN:
            color = vga3_color(VGA3_YELLOW, VGA3_BLACK);
            break;
        case ERROR:
            color = vga3_color(VGA3_RED, VGA3_BLACK);
            break;
        case FATAL:
            color = vga3_color(VGA3_RED, VGA3_BLACK);
            break;
    }
    write_string(color, log_message->log_message); // TODO should print the [Logger], time, etc.
}

static logger_handler_t vga3_log_handler = {
        .min_level = DEBUG,
        .logger_output_handler = vga3_logger_output
};

void vga3_init() {
    register_logger_handler(&vga3_log_handler);
}


/*
 * Writes a string starting at 0,0
 */
void write_string(uint8_t color, char *string )
{
    write_string_at(color, string, 0,0);
}

/*
 * Write string at screen location.
 */
void write_string_at(uint8_t color, char *string, uint8_t x, uint8_t y) {
    uint8_t * video = (uint8_t *) 0xb8000 + (y * 160)  + (x * 2);
    while ( *string != 0 && video < (uint8_t *) 0xb8FA0) {
        *video = *string;
        string++;
        video++;
        *video = color;
        video++;
    }
}
/*
 * runtime function for computing the vga colors.
 */
uint8_t inline get_vga3_color(uint8_t fore, uint8_t back) {
    return ((back << 4) + fore);
}