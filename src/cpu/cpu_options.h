//
// Created by AIDAN on 2/2/2024.
//

#ifndef KITTY_CPU_OPTIONS_H
#define KITTY_CPU_OPTIONS_H
#include "stdint.h"
/*
 * These variables should be defined for all processors:
 * Bits = (Pointer Bit Width)
 *
 * Other defined variables in this file are for use with processor-specific compilation.
 *
 * All other CPU preprocessor definitions (for use in cpu code) should be put in its corresponding header file.
 */

#if CPU == 1 // x86_64 Processors
    #define Bits == 64
    #define BITS_TYPE uint64_t
    #define Intel_CPU
    #define x86_64
    #include "x86_64/x86_64.h"

#elif CPU == 2 // x86 Processors, i386 Processors, and i686 Processors
    #define Bits == 32
    #define BITS_TYPE uint32_t
    #define Intel_CPU
    #define x86

#elif CPU == 3 // ARMv8 (64-bit ARM) Processors
    #define Bits == 64
    #define BITS_TYPE uint64_t
    #define ARM_CPU
    #define ARMv8

#elif CPU == 4 // ARMv7 (32-bit ARM) Processors
    #define Bits == 32
    #define BITS_TYPE uint32_t
    #define ARM_CPU
    #define ARMv7

#endif

#endif //KITTY_CPU_OPTIONS_H
