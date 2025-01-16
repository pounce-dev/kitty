//
// Created by AIDAN on 2/23/2024.
//

#include <stdbool.h>
#include "idt.h"
#include "../../driver/video/vga.h"
#include "../../util/ascii.h"
#include "port.h"
#include "../../kernel/memory.h"



/*
 * Map a given IDT gate descriptor entry to its corresponding function (Interrupt vector to interrupt function)
 */

void modify_descriptor_entry(interrupt_gate_descriptor* gate_descriptor, void* function, bool callable_from_userspace) {
    (*gate_descriptor).offset_bits_0_15 = ((uint64_t) (function)) & 0xFFFF;
    (*gate_descriptor).selector = (uint16_t) 0x08; // code is the 2nd GDT entry, see boot sector
    (*gate_descriptor).ist_offset = 0x00;
    uint8_t type_dpl_present = 0x00;
    if (callable_from_userspace) {
        type_dpl_present = 0xE0;
    } else {
        type_dpl_present = 0x80;
    }
    bool trap_gate = false; // may be a parameter in the future
    if (trap_gate) {
        type_dpl_present |= 0x0F;
    } else {
        type_dpl_present |= 0x0E;
    }
    (*gate_descriptor).type_dpl_present = type_dpl_present;
    (*gate_descriptor).offset_bits_16_31 = ( (uint64_t) (function) >> 16) & 0xFFFF;
    (*gate_descriptor).offset_bits_32_63 = ( (uint64_t) (function) >> 32) & 0xFFFFFFFF;
    (*gate_descriptor).zeroes = 0;
}

/*
 * Set PIC interrupt vector offset and mask
 */

#define PIC_MASTER_COMMAND 0x20
#define PIC_SLAVE_COMMAND 0xA0
#define PIC_MASTER_DATA (PIC_MASTER_COMMAND+1)
#define PIC_SLAVE_DATA	(PIC_SLAVE_COMMAND+1)
#define ICW1_ICW4 0x01
#define ICW1_INIT 0x10
#define ICW4_8086 0x01

void set_pic_offset() {
    // Initialize configuration mode
    port_out_byte(PIC_MASTER_COMMAND, ICW1_INIT | ICW1_ICW4);
    port_out_byte(0x80, 0);
    port_out_byte(PIC_SLAVE_COMMAND, ICW1_INIT | ICW1_ICW4);
    port_out_byte(0x80, 0);
    // Interrupt vectors to remap to
    port_out_byte(PIC_MASTER_DATA, 0x20);
    port_out_byte(0x80, 0);
    port_out_byte(PIC_SLAVE_DATA, 0x28);
    port_out_byte(0x80, 0);
    // Offset from each other or something I forgot
    port_out_byte(PIC_MASTER_DATA, 4);
    port_out_byte(0x80, 0);
    port_out_byte(PIC_SLAVE_DATA, 2);
    port_out_byte(0x80, 0);
    // Mode
    port_out_byte(PIC_MASTER_DATA, ICW4_8086);
    port_out_byte(0x80, 0);
    port_out_byte(PIC_SLAVE_DATA, ICW4_8086);
    port_out_byte(0x80, 0);
    // Masks
    port_out_byte(PIC_MASTER_DATA, 0xFE);
    port_out_byte(0x80, 0);
    port_out_byte(PIC_SLAVE_DATA, 0xFE);
    port_out_byte(0x80, 0);
}

/*
 * Set up every IDT entry and the IDT itself.
 */

void init_idt() {
    // Volume 3 Chapter 6.10
    idt_descriptor.offset = (uint64_t) &idt;
    idt_descriptor.size = 255 * 16 - 1;
    modify_descriptor_entry(&idt.entry_0, isr_0, false);
    modify_descriptor_entry(&idt.entry_1, isr_1, false);
    modify_descriptor_entry(&idt.entry_2, isr_2, false);
    modify_descriptor_entry(&idt.entry_3, isr_3, false);
    modify_descriptor_entry(&idt.entry_4, isr_4, false);
    modify_descriptor_entry(&idt.entry_5, isr_5, false);
    modify_descriptor_entry(&idt.entry_6, isr_6, false);
    modify_descriptor_entry(&idt.entry_7, isr_7, false);
    modify_descriptor_entry(&idt.entry_8, isr_8, false);
    modify_descriptor_entry(&idt.entry_9, isr_9, false);
    modify_descriptor_entry(&idt.entry_10, isr_10, false);
    modify_descriptor_entry(&idt.entry_11, isr_11, false);
    modify_descriptor_entry(&idt.entry_12, isr_12, false);
    modify_descriptor_entry(&idt.entry_13, isr_13, false);
    modify_descriptor_entry(&idt.entry_14, isr_14, false);
    modify_descriptor_entry(&idt.entry_15, isr_15, false);
    modify_descriptor_entry(&idt.entry_16, isr_16, false);
    modify_descriptor_entry(&idt.entry_17, isr_17, false);
    modify_descriptor_entry(&idt.entry_18, isr_18, false);
    modify_descriptor_entry(&idt.entry_19, isr_19, false);
    modify_descriptor_entry(&idt.entry_20, isr_20, false);
    modify_descriptor_entry(&idt.entry_21, isr_21, false);
    modify_descriptor_entry(&idt.entry_22, isr_22, false);
    modify_descriptor_entry(&idt.entry_23, isr_23, false);
    modify_descriptor_entry(&idt.entry_24, isr_24, false);
    modify_descriptor_entry(&idt.entry_25, isr_25, false);
    modify_descriptor_entry(&idt.entry_26, isr_26, false);
    modify_descriptor_entry(&idt.entry_27, isr_27, false);
    modify_descriptor_entry(&idt.entry_28, isr_28, false);
    modify_descriptor_entry(&idt.entry_29, isr_29, false);
    modify_descriptor_entry(&idt.entry_30, isr_30, false);
    modify_descriptor_entry(&idt.entry_31, isr_31, false);
    modify_descriptor_entry(&idt.entry_32, isr_32, false);
    modify_descriptor_entry(&idt.entry_33, isr_33, false);
    modify_descriptor_entry(&idt.entry_34, isr_34, false);
    modify_descriptor_entry(&idt.entry_35, isr_35, false);
    modify_descriptor_entry(&idt.entry_36, isr_36, false);
    modify_descriptor_entry(&idt.entry_37, isr_37, false);
    modify_descriptor_entry(&idt.entry_38, isr_38, false);
    modify_descriptor_entry(&idt.entry_39, isr_39, false);
    modify_descriptor_entry(&idt.entry_40, isr_40, false);
    modify_descriptor_entry(&idt.entry_41, isr_41, false);
    modify_descriptor_entry(&idt.entry_42, isr_42, false);
    modify_descriptor_entry(&idt.entry_43, isr_43, false);
    modify_descriptor_entry(&idt.entry_44, isr_44, false);
    modify_descriptor_entry(&idt.entry_45, isr_45, false);
    modify_descriptor_entry(&idt.entry_46, isr_46, false);
    modify_descriptor_entry(&idt.entry_47, isr_47, false);
    modify_descriptor_entry(&idt.entry_48, isr_48, false);
    modify_descriptor_entry(&idt.entry_49, isr_49, false);
    modify_descriptor_entry(&idt.entry_50, isr_50, false);
    modify_descriptor_entry(&idt.entry_51, isr_51, false);
    modify_descriptor_entry(&idt.entry_52, isr_52, false);
    modify_descriptor_entry(&idt.entry_53, isr_53, false);
    modify_descriptor_entry(&idt.entry_54, isr_54, false);
    modify_descriptor_entry(&idt.entry_55, isr_55, false);
    modify_descriptor_entry(&idt.entry_56, isr_56, false);
    modify_descriptor_entry(&idt.entry_57, isr_57, false);
    modify_descriptor_entry(&idt.entry_58, isr_58, false);
    modify_descriptor_entry(&idt.entry_59, isr_59, false);
    modify_descriptor_entry(&idt.entry_60, isr_60, false);
    modify_descriptor_entry(&idt.entry_61, isr_61, false);
    modify_descriptor_entry(&idt.entry_62, isr_62, false);
    modify_descriptor_entry(&idt.entry_63, isr_63, false);
    modify_descriptor_entry(&idt.entry_64, isr_64, false);
    modify_descriptor_entry(&idt.entry_65, isr_65, false);
    modify_descriptor_entry(&idt.entry_66, isr_66, false);
    modify_descriptor_entry(&idt.entry_67, isr_67, false);
    modify_descriptor_entry(&idt.entry_68, isr_68, false);
    modify_descriptor_entry(&idt.entry_69, isr_69, false);
    modify_descriptor_entry(&idt.entry_70, isr_70, false);
    modify_descriptor_entry(&idt.entry_71, isr_71, false);
    modify_descriptor_entry(&idt.entry_72, isr_72, false);
    modify_descriptor_entry(&idt.entry_73, isr_73, false);
    modify_descriptor_entry(&idt.entry_74, isr_74, false);
    modify_descriptor_entry(&idt.entry_75, isr_75, false);
    modify_descriptor_entry(&idt.entry_76, isr_76, false);
    modify_descriptor_entry(&idt.entry_77, isr_77, false);
    modify_descriptor_entry(&idt.entry_78, isr_78, false);
    modify_descriptor_entry(&idt.entry_79, isr_79, false);
    modify_descriptor_entry(&idt.entry_80, isr_80, false);
    modify_descriptor_entry(&idt.entry_81, isr_81, false);
    modify_descriptor_entry(&idt.entry_82, isr_82, false);
    modify_descriptor_entry(&idt.entry_83, isr_83, false);
    modify_descriptor_entry(&idt.entry_84, isr_84, false);
    modify_descriptor_entry(&idt.entry_85, isr_85, false);
    modify_descriptor_entry(&idt.entry_86, isr_86, false);
    modify_descriptor_entry(&idt.entry_87, isr_87, false);
    modify_descriptor_entry(&idt.entry_88, isr_88, false);
    modify_descriptor_entry(&idt.entry_89, isr_89, false);
    modify_descriptor_entry(&idt.entry_90, isr_90, false);
    modify_descriptor_entry(&idt.entry_91, isr_91, false);
    modify_descriptor_entry(&idt.entry_92, isr_92, false);
    modify_descriptor_entry(&idt.entry_93, isr_93, false);
    modify_descriptor_entry(&idt.entry_94, isr_94, false);
    modify_descriptor_entry(&idt.entry_95, isr_95, false);
    modify_descriptor_entry(&idt.entry_96, isr_96, false);
    modify_descriptor_entry(&idt.entry_97, isr_97, false);
    modify_descriptor_entry(&idt.entry_98, isr_98, false);
    modify_descriptor_entry(&idt.entry_99, isr_99, false);
    modify_descriptor_entry(&idt.entry_100, isr_100, false);
    modify_descriptor_entry(&idt.entry_101, isr_101, false);
    modify_descriptor_entry(&idt.entry_102, isr_102, false);
    modify_descriptor_entry(&idt.entry_103, isr_103, false);
    modify_descriptor_entry(&idt.entry_104, isr_104, false);
    modify_descriptor_entry(&idt.entry_105, isr_105, false);
    modify_descriptor_entry(&idt.entry_106, isr_106, false);
    modify_descriptor_entry(&idt.entry_107, isr_107, false);
    modify_descriptor_entry(&idt.entry_108, isr_108, false);
    modify_descriptor_entry(&idt.entry_109, isr_109, false);
    modify_descriptor_entry(&idt.entry_110, isr_110, false);
    modify_descriptor_entry(&idt.entry_111, isr_111, false);
    modify_descriptor_entry(&idt.entry_112, isr_112, false);
    modify_descriptor_entry(&idt.entry_113, isr_113, false);
    modify_descriptor_entry(&idt.entry_114, isr_114, false);
    modify_descriptor_entry(&idt.entry_115, isr_115, false);
    modify_descriptor_entry(&idt.entry_116, isr_116, false);
    modify_descriptor_entry(&idt.entry_117, isr_117, false);
    modify_descriptor_entry(&idt.entry_118, isr_118, false);
    modify_descriptor_entry(&idt.entry_119, isr_119, false);
    modify_descriptor_entry(&idt.entry_120, isr_120, false);
    modify_descriptor_entry(&idt.entry_121, isr_121, false);
    modify_descriptor_entry(&idt.entry_122, isr_122, false);
    modify_descriptor_entry(&idt.entry_123, isr_123, false);
    modify_descriptor_entry(&idt.entry_124, isr_124, false);
    modify_descriptor_entry(&idt.entry_125, isr_125, false);
    modify_descriptor_entry(&idt.entry_126, isr_126, false);
    modify_descriptor_entry(&idt.entry_127, isr_127, false);
    modify_descriptor_entry(&idt.entry_128, isr_128, true);
    modify_descriptor_entry(&idt.entry_129, isr_129, false);
    modify_descriptor_entry(&idt.entry_130, isr_130, false);
    modify_descriptor_entry(&idt.entry_131, isr_131, false);
    modify_descriptor_entry(&idt.entry_132, isr_132, false);
    modify_descriptor_entry(&idt.entry_133, isr_133, false);
    modify_descriptor_entry(&idt.entry_134, isr_134, false);
    modify_descriptor_entry(&idt.entry_135, isr_135, false);
    modify_descriptor_entry(&idt.entry_136, isr_136, false);
    modify_descriptor_entry(&idt.entry_137, isr_137, false);
    modify_descriptor_entry(&idt.entry_138, isr_138, false);
    modify_descriptor_entry(&idt.entry_139, isr_139, false);
    modify_descriptor_entry(&idt.entry_140, isr_140, false);
    modify_descriptor_entry(&idt.entry_141, isr_141, false);
    modify_descriptor_entry(&idt.entry_142, isr_142, false);
    modify_descriptor_entry(&idt.entry_143, isr_143, false);
    modify_descriptor_entry(&idt.entry_144, isr_144, false);
    modify_descriptor_entry(&idt.entry_145, isr_145, false);
    modify_descriptor_entry(&idt.entry_146, isr_146, false);
    modify_descriptor_entry(&idt.entry_147, isr_147, false);
    modify_descriptor_entry(&idt.entry_148, isr_148, false);
    modify_descriptor_entry(&idt.entry_149, isr_149, false);
    modify_descriptor_entry(&idt.entry_150, isr_150, false);
    modify_descriptor_entry(&idt.entry_151, isr_151, false);
    modify_descriptor_entry(&idt.entry_152, isr_152, false);
    modify_descriptor_entry(&idt.entry_153, isr_153, false);
    modify_descriptor_entry(&idt.entry_154, isr_154, false);
    modify_descriptor_entry(&idt.entry_155, isr_155, false);
    modify_descriptor_entry(&idt.entry_156, isr_156, false);
    modify_descriptor_entry(&idt.entry_157, isr_157, false);
    modify_descriptor_entry(&idt.entry_158, isr_158, false);
    modify_descriptor_entry(&idt.entry_159, isr_159, false);
    modify_descriptor_entry(&idt.entry_160, isr_160, false);
    modify_descriptor_entry(&idt.entry_161, isr_161, false);
    modify_descriptor_entry(&idt.entry_162, isr_162, false);
    modify_descriptor_entry(&idt.entry_163, isr_163, false);
    modify_descriptor_entry(&idt.entry_164, isr_164, false);
    modify_descriptor_entry(&idt.entry_165, isr_165, false);
    modify_descriptor_entry(&idt.entry_166, isr_166, false);
    modify_descriptor_entry(&idt.entry_167, isr_167, false);
    modify_descriptor_entry(&idt.entry_168, isr_168, false);
    modify_descriptor_entry(&idt.entry_169, isr_169, false);
    modify_descriptor_entry(&idt.entry_170, isr_170, false);
    modify_descriptor_entry(&idt.entry_171, isr_171, false);
    modify_descriptor_entry(&idt.entry_172, isr_172, false);
    modify_descriptor_entry(&idt.entry_173, isr_173, false);
    modify_descriptor_entry(&idt.entry_174, isr_174, false);
    modify_descriptor_entry(&idt.entry_175, isr_175, false);
    modify_descriptor_entry(&idt.entry_176, isr_176, false);
    modify_descriptor_entry(&idt.entry_177, isr_177, false);
    modify_descriptor_entry(&idt.entry_178, isr_178, false);
    modify_descriptor_entry(&idt.entry_179, isr_179, false);
    modify_descriptor_entry(&idt.entry_180, isr_180, false);
    modify_descriptor_entry(&idt.entry_181, isr_181, false);
    modify_descriptor_entry(&idt.entry_182, isr_182, false);
    modify_descriptor_entry(&idt.entry_183, isr_183, false);
    modify_descriptor_entry(&idt.entry_184, isr_184, false);
    modify_descriptor_entry(&idt.entry_185, isr_185, false);
    modify_descriptor_entry(&idt.entry_186, isr_186, false);
    modify_descriptor_entry(&idt.entry_187, isr_187, false);
    modify_descriptor_entry(&idt.entry_188, isr_188, false);
    modify_descriptor_entry(&idt.entry_189, isr_189, false);
    modify_descriptor_entry(&idt.entry_190, isr_190, false);
    modify_descriptor_entry(&idt.entry_191, isr_191, false);
    modify_descriptor_entry(&idt.entry_192, isr_192, false);
    modify_descriptor_entry(&idt.entry_193, isr_193, false);
    modify_descriptor_entry(&idt.entry_194, isr_194, false);
    modify_descriptor_entry(&idt.entry_195, isr_195, false);
    modify_descriptor_entry(&idt.entry_196, isr_196, false);
    modify_descriptor_entry(&idt.entry_197, isr_197, false);
    modify_descriptor_entry(&idt.entry_198, isr_198, false);
    modify_descriptor_entry(&idt.entry_199, isr_199, false);
    modify_descriptor_entry(&idt.entry_200, isr_200, false);
    modify_descriptor_entry(&idt.entry_201, isr_201, false);
    modify_descriptor_entry(&idt.entry_202, isr_202, false);
    modify_descriptor_entry(&idt.entry_203, isr_203, false);
    modify_descriptor_entry(&idt.entry_204, isr_204, false);
    modify_descriptor_entry(&idt.entry_205, isr_205, false);
    modify_descriptor_entry(&idt.entry_206, isr_206, false);
    modify_descriptor_entry(&idt.entry_207, isr_207, false);
    modify_descriptor_entry(&idt.entry_208, isr_208, false);
    modify_descriptor_entry(&idt.entry_209, isr_209, false);
    modify_descriptor_entry(&idt.entry_210, isr_210, false);
    modify_descriptor_entry(&idt.entry_211, isr_211, false);
    modify_descriptor_entry(&idt.entry_212, isr_212, false);
    modify_descriptor_entry(&idt.entry_213, isr_213, false);
    modify_descriptor_entry(&idt.entry_214, isr_214, false);
    modify_descriptor_entry(&idt.entry_215, isr_215, false);
    modify_descriptor_entry(&idt.entry_216, isr_216, false);
    modify_descriptor_entry(&idt.entry_217, isr_217, false);
    modify_descriptor_entry(&idt.entry_218, isr_218, false);
    modify_descriptor_entry(&idt.entry_219, isr_219, false);
    modify_descriptor_entry(&idt.entry_220, isr_220, false);
    modify_descriptor_entry(&idt.entry_221, isr_221, false);
    modify_descriptor_entry(&idt.entry_222, isr_222, false);
    modify_descriptor_entry(&idt.entry_223, isr_223, false);
    modify_descriptor_entry(&idt.entry_224, isr_224, false);
    modify_descriptor_entry(&idt.entry_225, isr_225, false);
    modify_descriptor_entry(&idt.entry_226, isr_226, false);
    modify_descriptor_entry(&idt.entry_227, isr_227, false);
    modify_descriptor_entry(&idt.entry_228, isr_228, false);
    modify_descriptor_entry(&idt.entry_229, isr_229, false);
    modify_descriptor_entry(&idt.entry_230, isr_230, false);
    modify_descriptor_entry(&idt.entry_231, isr_231, false);
    modify_descriptor_entry(&idt.entry_232, isr_232, false);
    modify_descriptor_entry(&idt.entry_233, isr_233, false);
    modify_descriptor_entry(&idt.entry_234, isr_234, false);
    modify_descriptor_entry(&idt.entry_235, isr_235, false);
    modify_descriptor_entry(&idt.entry_236, isr_236, false);
    modify_descriptor_entry(&idt.entry_237, isr_237, false);
    modify_descriptor_entry(&idt.entry_238, isr_238, false);
    modify_descriptor_entry(&idt.entry_239, isr_239, false);
    modify_descriptor_entry(&idt.entry_240, isr_240, false);
    modify_descriptor_entry(&idt.entry_241, isr_241, false);
    modify_descriptor_entry(&idt.entry_242, isr_242, false);
    modify_descriptor_entry(&idt.entry_243, isr_243, false);
    modify_descriptor_entry(&idt.entry_244, isr_244, false);
    modify_descriptor_entry(&idt.entry_245, isr_245, false);
    modify_descriptor_entry(&idt.entry_246, isr_246, false);
    modify_descriptor_entry(&idt.entry_247, isr_247, false);
    modify_descriptor_entry(&idt.entry_248, isr_248, false);
    modify_descriptor_entry(&idt.entry_249, isr_249, false);
    modify_descriptor_entry(&idt.entry_250, isr_250, false);
    modify_descriptor_entry(&idt.entry_251, isr_251, false);
    modify_descriptor_entry(&idt.entry_252, isr_252, false);
    modify_descriptor_entry(&idt.entry_253, isr_253, false);
    modify_descriptor_entry(&idt.entry_254, isr_254, false);
    modify_descriptor_entry(&idt.entry_255, isr_255, false);
    set_pic_offset();
    asm volatile("lidt %0" : : "m" (idt_descriptor));
    asm volatile("sti");
}


/*
 * INTERRUPT FUNCTION SECTION
 * These are called from interrupts.asm
 * Please, maintain the order of the vectors with the routines defined below.
 */

// 0
void divide_by_zero_interrupt() {
    write_string_at(vga3_color(VGA3_GREEN, VGA3_BLACK), "Divide by Zero", 15, 16);
}

// 1
void debug_interrupt() {
    write_string_at(vga3_color(VGA3_GREEN, VGA3_BLACK), "Debug Interrupt", 15, 16);
}

// 2
void non_maskable_interrupt() {
    write_string_at(vga3_color(VGA3_GREEN, VGA3_BLACK), "Non-Maskable", 15, 16);
}

// 3
void breakpoint_interrupt() {
    write_string_at(vga3_color(VGA3_GREEN, VGA3_BLACK), "Breakpoint", 15, 16);
}

// 4
void overflow_interrupt() {
    write_string_at(vga3_color(VGA3_GREEN, VGA3_BLACK), "Overflow Interrupt", 15, 16);
}

// 5
void bound_range_exceeded_interrupt() {
    write_string_at(vga3_color(VGA3_GREEN, VGA3_BLACK), "Bound Range Exceeded", 15, 16);
}

// 6
void invalid_opcode_interrupt() {
    write_string_at(vga3_color(VGA3_GREEN, VGA3_BLACK), "Invalid Opcode", 15, 16);
}

// 7
void device_not_available_interrupt() {
    write_string_at(vga3_color(VGA3_GREEN, VGA3_BLACK), "Device Not Available", 15, 16);
}

// 8
void double_fault_interrupt() {
    write_string_at(vga3_color(VGA3_GREEN, VGA3_BLACK), "Double Fault", 15, 18);
}

// 9
void coprocessor_segment_overrun_interrupt() {
    write_string_at(vga3_color(VGA3_GREEN, VGA3_BLACK), "Coprocessor Segment Overrun", 15, 16);
}

// 10
void invalid_tss_interrupt() {
    write_string_at(vga3_color(VGA3_GREEN, VGA3_BLACK), "Invalid TSS", 15, 16);
}

// 11
void segment_not_present_interrupt() {
    write_string_at(vga3_color(VGA3_GREEN, VGA3_BLACK), "Segment Not Present", 15, 16);
}

// 12
void stack_segment_fault_interrupt() {
    write_string_at(vga3_color(VGA3_GREEN, VGA3_BLACK), "SS Fault", 15, 16);
}

// 13
void general_protection_fault_interrupt() {
    write_string_at(vga3_color(VGA3_GREEN, VGA3_BLACK), "GP Fault", 15, 16);
}

// 14
void page_fault_interrupt() {
    write_string_at(vga3_color(VGA3_GREEN, VGA3_BLACK), "Page Fault", 15, 16);
}

// 16
void floating_point_error_interrupt() {
    write_string_at(vga3_color(VGA3_GREEN, VGA3_BLACK), "Floating Point Error", 15, 16);
}

// 17
void alignment_check_interrupt() {
    write_string_at(vga3_color(VGA3_GREEN, VGA3_BLACK), "Align Check", 15, 16);
}

// 18
void machine_check_interrupt() {
    write_string_at(vga3_color(VGA3_GREEN, VGA3_BLACK), "Machine Check", 15, 16);
}

// 19
void simd_floating_point_exception_interrupt() {
    write_string_at(vga3_color(VGA3_GREEN, VGA3_BLACK), "SIMD", 15, 16);
}

// 20
void virtualization_exception_interrupt() {
    write_string_at(vga3_color(VGA3_GREEN, VGA3_BLACK), "Virt", 15, 16);
}

// 21
void control_protection_exception_interrupt() {
    write_string_at(vga3_color(VGA3_GREEN, VGA3_BLACK), "ctrl", 15, 16);
}

// 32
int count_interrupts;

void timer_interrupt() {
    char* number = kmalloc(sizeof(char) * 12);
    count_interrupts += 1;
    decimal_from_int32(count_interrupts, number);
    write_string_at(vga3_color(VGA3_GREEN, VGA3_BLACK), "Timer", 15, 17);
    write_string_at(vga3_color(VGA3_WHITE, VGA3_BLACK), number, 30, 17);
    free(number);
}

// 128
void system_call() {
    write_string_at(vga3_color(VGA3_GREEN, VGA3_BLACK), "System Call", 18, 18);
}


/*
 * All unmapped/reserved unmapped interrupts pass the calling number from the isr defined in interrupts.asm!
 */

void unmapped_or_reserved_interrupt(uint64_t interrupt_vector) {
    char* number = kmalloc(sizeof(char[12]));
    decimal_from_int32((int) interrupt_vector, number);
    write_string_at(vga3_color(VGA3_GREEN, VGA3_BLACK), "Unmapped", 15, 17);
    write_string_at(vga3_color(VGA3_WHITE, VGA3_BLACK), number, 30, 17);
    free(number);
}