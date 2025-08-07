//
// Created by AIDAN on 11/7/2023.
//
#include <stdint.h>
#ifndef KITTY_VGA_H
#define KITTY_VGA_H

/*
 * VGA Mode 3 Color List
 */
#define VGA3_BLACK 0b00000000
#define VGA3_BLUE 0b00000001
#define VGA3_GREEN 0b00000010
#define VGA3_CYAN 0b00000011
#define VGA3_RED 0b00000100
#define VGA3_MAGENTA 0b00000101
#define VGA3_BROWN 0b00000110
#define VGA3_LIGHT_GRAY 0b00000111
#define VGA3_DARK_GRAY 0b00001000
#define VGA3_LIGHT_BLUE 0b00001001
#define VGA3_LIGHT_GREEN 0b00001010
#define VGA3_LIGHT_CYAN 0b00001011
#define VGA3_LIGHT_RED 0b00001100
#define VGA3_LIGHT_MAGENTA 0b00001101
#define VGA3_YELLOW 0b00001110
#define VGA3_WHITE 0b00001111

/*
 * Init vga3, necessary for logging capabilities!
 */
void vga3_init();

/*
 * Compile-time function for computing the vga colors.
 */
#define vga3_color(FORE, BACK) ((BACK << 4) + FORE)

/*
 * Runtime function for computing the vga colors.
 */
uint8_t get_vga3_color(uint8_t fore, uint8_t back);

/*
 * Writes a string at the location 0,0
 */
void write_string(uint8_t color, char *string);

/*
 * Writes a string at the specified location x,y
 */
void write_string_at(uint8_t color, char *string, uint8_t x, uint8_t y);

#endif //KITTY_VGA_H

