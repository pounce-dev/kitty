//
// Created by AIDAN on 2/23/2024.
//

#include "idt.h"
#include "../../driver/video/vga.h"
#include "../../util/ascii.h"
#include "port.h"
#include "../../kernel/memory.h"



/*
 * Map a given IDT gate descriptor entry to its corresponding function (Interrupt vector to interrupt function)
 */

void modify_descriptor_entry(interrupt_gate_descriptor* gate_descriptor, void* function) {
    (*gate_descriptor).offset_bits_0_15 = ((uint64_t) (function)) & 0xFFFF;
    (*gate_descriptor).selector = (uint16_t) 0x08; // code is the 2nd GDT entry, see boot sector
    (*gate_descriptor).ist_offset = 0x00;
    (*gate_descriptor).type_dpl_present = 0x8E;
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
    idt_descriptor.size = 255 * 8 - 1;
    modify_descriptor_entry(&idt.entry_0, isr_0);
    modify_descriptor_entry(&idt.entry_1, isr_1);
    modify_descriptor_entry(&idt.entry_2, isr_2);
    modify_descriptor_entry(&idt.entry_3, isr_3);
    modify_descriptor_entry(&idt.entry_4, isr_4);
    modify_descriptor_entry(&idt.entry_5, isr_5);
    modify_descriptor_entry(&idt.entry_6, isr_6);
    modify_descriptor_entry(&idt.entry_7, isr_7);
    modify_descriptor_entry(&idt.entry_8, isr_8);
    modify_descriptor_entry(&idt.entry_9, isr_9);
    modify_descriptor_entry(&idt.entry_10, isr_10);
    modify_descriptor_entry(&idt.entry_11, isr_11);
    modify_descriptor_entry(&idt.entry_12, isr_12);
    modify_descriptor_entry(&idt.entry_13, isr_13);
    modify_descriptor_entry(&idt.entry_14, isr_14);
    modify_descriptor_entry(&idt.entry_15, isr_15);
    modify_descriptor_entry(&idt.entry_16, isr_16);
    modify_descriptor_entry(&idt.entry_17, isr_17);
    modify_descriptor_entry(&idt.entry_18, isr_18);
    modify_descriptor_entry(&idt.entry_19, isr_19);
    modify_descriptor_entry(&idt.entry_20, isr_20);
    modify_descriptor_entry(&idt.entry_21, isr_21);
    modify_descriptor_entry(&idt.entry_22, isr_22);
    modify_descriptor_entry(&idt.entry_23, isr_23);
    modify_descriptor_entry(&idt.entry_24, isr_24);
    modify_descriptor_entry(&idt.entry_25, isr_25);
    modify_descriptor_entry(&idt.entry_26, isr_26);
    modify_descriptor_entry(&idt.entry_27, isr_27);
    modify_descriptor_entry(&idt.entry_28, isr_28);
    modify_descriptor_entry(&idt.entry_29, isr_29);
    modify_descriptor_entry(&idt.entry_30, isr_30);
    modify_descriptor_entry(&idt.entry_31, isr_31);
    modify_descriptor_entry(&idt.entry_32, isr_32);
    modify_descriptor_entry(&idt.entry_33, isr_33);
    modify_descriptor_entry(&idt.entry_34, isr_34);
    modify_descriptor_entry(&idt.entry_35, isr_35);
    modify_descriptor_entry(&idt.entry_36, isr_36);
    modify_descriptor_entry(&idt.entry_37, isr_37);
    modify_descriptor_entry(&idt.entry_38, isr_38);
    modify_descriptor_entry(&idt.entry_39, isr_39);
    modify_descriptor_entry(&idt.entry_40, isr_40);
    modify_descriptor_entry(&idt.entry_41, isr_41);
    modify_descriptor_entry(&idt.entry_42, isr_42);
    modify_descriptor_entry(&idt.entry_43, isr_43);
    modify_descriptor_entry(&idt.entry_44, isr_44);
    modify_descriptor_entry(&idt.entry_45, isr_45);
    modify_descriptor_entry(&idt.entry_46, isr_46);
    modify_descriptor_entry(&idt.entry_47, isr_47);
    modify_descriptor_entry(&idt.entry_48, isr_48);
    modify_descriptor_entry(&idt.entry_49, isr_49);
    modify_descriptor_entry(&idt.entry_50, isr_50);
    modify_descriptor_entry(&idt.entry_51, isr_51);
    modify_descriptor_entry(&idt.entry_52, isr_52);
    modify_descriptor_entry(&idt.entry_53, isr_53);
    modify_descriptor_entry(&idt.entry_54, isr_54);
    modify_descriptor_entry(&idt.entry_55, isr_55);
    modify_descriptor_entry(&idt.entry_56, isr_56);
    modify_descriptor_entry(&idt.entry_57, isr_57);
    modify_descriptor_entry(&idt.entry_58, isr_58);
    modify_descriptor_entry(&idt.entry_59, isr_59);
    modify_descriptor_entry(&idt.entry_60, isr_60);
    modify_descriptor_entry(&idt.entry_61, isr_61);
    modify_descriptor_entry(&idt.entry_62, isr_62);
    modify_descriptor_entry(&idt.entry_63, isr_63);
    modify_descriptor_entry(&idt.entry_64, isr_64);
    modify_descriptor_entry(&idt.entry_65, isr_65);
    modify_descriptor_entry(&idt.entry_66, isr_66);
    modify_descriptor_entry(&idt.entry_67, isr_67);
    modify_descriptor_entry(&idt.entry_68, isr_68);
    modify_descriptor_entry(&idt.entry_69, isr_69);
    modify_descriptor_entry(&idt.entry_70, isr_70);
    modify_descriptor_entry(&idt.entry_71, isr_71);
    modify_descriptor_entry(&idt.entry_72, isr_72);
    modify_descriptor_entry(&idt.entry_73, isr_73);
    modify_descriptor_entry(&idt.entry_74, isr_74);
    modify_descriptor_entry(&idt.entry_75, isr_75);
    modify_descriptor_entry(&idt.entry_76, isr_76);
    modify_descriptor_entry(&idt.entry_77, isr_77);
    modify_descriptor_entry(&idt.entry_78, isr_78);
    modify_descriptor_entry(&idt.entry_79, isr_79);
    modify_descriptor_entry(&idt.entry_80, isr_80);
    modify_descriptor_entry(&idt.entry_81, isr_81);
    modify_descriptor_entry(&idt.entry_82, isr_82);
    modify_descriptor_entry(&idt.entry_83, isr_83);
    modify_descriptor_entry(&idt.entry_84, isr_84);
    modify_descriptor_entry(&idt.entry_85, isr_85);
    modify_descriptor_entry(&idt.entry_86, isr_86);
    modify_descriptor_entry(&idt.entry_87, isr_87);
    modify_descriptor_entry(&idt.entry_88, isr_88);
    modify_descriptor_entry(&idt.entry_89, isr_89);
    modify_descriptor_entry(&idt.entry_90, isr_90);
    modify_descriptor_entry(&idt.entry_91, isr_91);
    modify_descriptor_entry(&idt.entry_92, isr_92);
    modify_descriptor_entry(&idt.entry_93, isr_93);
    modify_descriptor_entry(&idt.entry_94, isr_94);
    modify_descriptor_entry(&idt.entry_95, isr_95);
    modify_descriptor_entry(&idt.entry_96, isr_96);
    modify_descriptor_entry(&idt.entry_97, isr_97);
    modify_descriptor_entry(&idt.entry_98, isr_98);
    modify_descriptor_entry(&idt.entry_99, isr_99);
    modify_descriptor_entry(&idt.entry_100, isr_100);
    modify_descriptor_entry(&idt.entry_101, isr_101);
    modify_descriptor_entry(&idt.entry_102, isr_102);
    modify_descriptor_entry(&idt.entry_103, isr_103);
    modify_descriptor_entry(&idt.entry_104, isr_104);
    modify_descriptor_entry(&idt.entry_105, isr_105);
    modify_descriptor_entry(&idt.entry_106, isr_106);
    modify_descriptor_entry(&idt.entry_107, isr_107);
    modify_descriptor_entry(&idt.entry_108, isr_108);
    modify_descriptor_entry(&idt.entry_109, isr_109);
    modify_descriptor_entry(&idt.entry_110, isr_110);
    modify_descriptor_entry(&idt.entry_111, isr_111);
    modify_descriptor_entry(&idt.entry_112, isr_112);
    modify_descriptor_entry(&idt.entry_113, isr_113);
    modify_descriptor_entry(&idt.entry_114, isr_114);
    modify_descriptor_entry(&idt.entry_115, isr_115);
    modify_descriptor_entry(&idt.entry_116, isr_116);
    modify_descriptor_entry(&idt.entry_117, isr_117);
    modify_descriptor_entry(&idt.entry_118, isr_118);
    modify_descriptor_entry(&idt.entry_119, isr_119);
    modify_descriptor_entry(&idt.entry_120, isr_120);
    modify_descriptor_entry(&idt.entry_121, isr_121);
    modify_descriptor_entry(&idt.entry_122, isr_122);
    modify_descriptor_entry(&idt.entry_123, isr_123);
    modify_descriptor_entry(&idt.entry_124, isr_124);
    modify_descriptor_entry(&idt.entry_125, isr_125);
    modify_descriptor_entry(&idt.entry_126, isr_126);
    modify_descriptor_entry(&idt.entry_127, isr_127);
    modify_descriptor_entry(&idt.entry_128, isr_128);
    modify_descriptor_entry(&idt.entry_129, isr_129);
    modify_descriptor_entry(&idt.entry_130, isr_130);
    modify_descriptor_entry(&idt.entry_131, isr_131);
    modify_descriptor_entry(&idt.entry_132, isr_132);
    modify_descriptor_entry(&idt.entry_133, isr_133);
    modify_descriptor_entry(&idt.entry_134, isr_134);
    modify_descriptor_entry(&idt.entry_135, isr_135);
    modify_descriptor_entry(&idt.entry_136, isr_136);
    modify_descriptor_entry(&idt.entry_137, isr_137);
    modify_descriptor_entry(&idt.entry_138, isr_138);
    modify_descriptor_entry(&idt.entry_139, isr_139);
    modify_descriptor_entry(&idt.entry_140, isr_140);
    modify_descriptor_entry(&idt.entry_141, isr_141);
    modify_descriptor_entry(&idt.entry_142, isr_142);
    modify_descriptor_entry(&idt.entry_143, isr_143);
    modify_descriptor_entry(&idt.entry_144, isr_144);
    modify_descriptor_entry(&idt.entry_145, isr_145);
    modify_descriptor_entry(&idt.entry_146, isr_146);
    modify_descriptor_entry(&idt.entry_147, isr_147);
    modify_descriptor_entry(&idt.entry_148, isr_148);
    modify_descriptor_entry(&idt.entry_149, isr_149);
    modify_descriptor_entry(&idt.entry_150, isr_150);
    modify_descriptor_entry(&idt.entry_151, isr_151);
    modify_descriptor_entry(&idt.entry_152, isr_152);
    modify_descriptor_entry(&idt.entry_153, isr_153);
    modify_descriptor_entry(&idt.entry_154, isr_154);
    modify_descriptor_entry(&idt.entry_155, isr_155);
    modify_descriptor_entry(&idt.entry_156, isr_156);
    modify_descriptor_entry(&idt.entry_157, isr_157);
    modify_descriptor_entry(&idt.entry_158, isr_158);
    modify_descriptor_entry(&idt.entry_159, isr_159);
    modify_descriptor_entry(&idt.entry_160, isr_160);
    modify_descriptor_entry(&idt.entry_161, isr_161);
    modify_descriptor_entry(&idt.entry_162, isr_162);
    modify_descriptor_entry(&idt.entry_163, isr_163);
    modify_descriptor_entry(&idt.entry_164, isr_164);
    modify_descriptor_entry(&idt.entry_165, isr_165);
    modify_descriptor_entry(&idt.entry_166, isr_166);
    modify_descriptor_entry(&idt.entry_167, isr_167);
    modify_descriptor_entry(&idt.entry_168, isr_168);
    modify_descriptor_entry(&idt.entry_169, isr_169);
    modify_descriptor_entry(&idt.entry_170, isr_170);
    modify_descriptor_entry(&idt.entry_171, isr_171);
    modify_descriptor_entry(&idt.entry_172, isr_172);
    modify_descriptor_entry(&idt.entry_173, isr_173);
    modify_descriptor_entry(&idt.entry_174, isr_174);
    modify_descriptor_entry(&idt.entry_175, isr_175);
    modify_descriptor_entry(&idt.entry_176, isr_176);
    modify_descriptor_entry(&idt.entry_177, isr_177);
    modify_descriptor_entry(&idt.entry_178, isr_178);
    modify_descriptor_entry(&idt.entry_179, isr_179);
    modify_descriptor_entry(&idt.entry_180, isr_180);
    modify_descriptor_entry(&idt.entry_181, isr_181);
    modify_descriptor_entry(&idt.entry_182, isr_182);
    modify_descriptor_entry(&idt.entry_183, isr_183);
    modify_descriptor_entry(&idt.entry_184, isr_184);
    modify_descriptor_entry(&idt.entry_185, isr_185);
    modify_descriptor_entry(&idt.entry_186, isr_186);
    modify_descriptor_entry(&idt.entry_187, isr_187);
    modify_descriptor_entry(&idt.entry_188, isr_188);
    modify_descriptor_entry(&idt.entry_189, isr_189);
    modify_descriptor_entry(&idt.entry_190, isr_190);
    modify_descriptor_entry(&idt.entry_191, isr_191);
    modify_descriptor_entry(&idt.entry_192, isr_192);
    modify_descriptor_entry(&idt.entry_193, isr_193);
    modify_descriptor_entry(&idt.entry_194, isr_194);
    modify_descriptor_entry(&idt.entry_195, isr_195);
    modify_descriptor_entry(&idt.entry_196, isr_196);
    modify_descriptor_entry(&idt.entry_197, isr_197);
    modify_descriptor_entry(&idt.entry_198, isr_198);
    modify_descriptor_entry(&idt.entry_199, isr_199);
    modify_descriptor_entry(&idt.entry_200, isr_200);
    modify_descriptor_entry(&idt.entry_201, isr_201);
    modify_descriptor_entry(&idt.entry_202, isr_202);
    modify_descriptor_entry(&idt.entry_203, isr_203);
    modify_descriptor_entry(&idt.entry_204, isr_204);
    modify_descriptor_entry(&idt.entry_205, isr_205);
    modify_descriptor_entry(&idt.entry_206, isr_206);
    modify_descriptor_entry(&idt.entry_207, isr_207);
    modify_descriptor_entry(&idt.entry_208, isr_208);
    modify_descriptor_entry(&idt.entry_209, isr_209);
    modify_descriptor_entry(&idt.entry_210, isr_210);
    modify_descriptor_entry(&idt.entry_211, isr_211);
    modify_descriptor_entry(&idt.entry_212, isr_212);
    modify_descriptor_entry(&idt.entry_213, isr_213);
    modify_descriptor_entry(&idt.entry_214, isr_214);
    modify_descriptor_entry(&idt.entry_215, isr_215);
    modify_descriptor_entry(&idt.entry_216, isr_216);
    modify_descriptor_entry(&idt.entry_217, isr_217);
    modify_descriptor_entry(&idt.entry_218, isr_218);
    modify_descriptor_entry(&idt.entry_219, isr_219);
    modify_descriptor_entry(&idt.entry_220, isr_220);
    modify_descriptor_entry(&idt.entry_221, isr_221);
    modify_descriptor_entry(&idt.entry_222, isr_222);
    modify_descriptor_entry(&idt.entry_223, isr_223);
    modify_descriptor_entry(&idt.entry_224, isr_224);
    modify_descriptor_entry(&idt.entry_225, isr_225);
    modify_descriptor_entry(&idt.entry_226, isr_226);
    modify_descriptor_entry(&idt.entry_227, isr_227);
    modify_descriptor_entry(&idt.entry_228, isr_228);
    modify_descriptor_entry(&idt.entry_229, isr_229);
    modify_descriptor_entry(&idt.entry_230, isr_230);
    modify_descriptor_entry(&idt.entry_231, isr_231);
    modify_descriptor_entry(&idt.entry_232, isr_232);
    modify_descriptor_entry(&idt.entry_233, isr_233);
    modify_descriptor_entry(&idt.entry_234, isr_234);
    modify_descriptor_entry(&idt.entry_235, isr_235);
    modify_descriptor_entry(&idt.entry_236, isr_236);
    modify_descriptor_entry(&idt.entry_237, isr_237);
    modify_descriptor_entry(&idt.entry_238, isr_238);
    modify_descriptor_entry(&idt.entry_239, isr_239);
    modify_descriptor_entry(&idt.entry_240, isr_240);
    modify_descriptor_entry(&idt.entry_241, isr_241);
    modify_descriptor_entry(&idt.entry_242, isr_242);
    modify_descriptor_entry(&idt.entry_243, isr_243);
    modify_descriptor_entry(&idt.entry_244, isr_244);
    modify_descriptor_entry(&idt.entry_245, isr_245);
    modify_descriptor_entry(&idt.entry_246, isr_246);
    modify_descriptor_entry(&idt.entry_247, isr_247);
    modify_descriptor_entry(&idt.entry_248, isr_248);
    modify_descriptor_entry(&idt.entry_249, isr_249);
    modify_descriptor_entry(&idt.entry_250, isr_250);
    modify_descriptor_entry(&idt.entry_251, isr_251);
    modify_descriptor_entry(&idt.entry_252, isr_252);
    modify_descriptor_entry(&idt.entry_253, isr_253);
    modify_descriptor_entry(&idt.entry_254, isr_254);
    modify_descriptor_entry(&idt.entry_255, isr_255);
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