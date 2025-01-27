;
; Created by AIDAN PRATT on 7/1/2024.
;

[bits 64]

%macro isr_common 1
    cli
    push rdi
    push rsi
    push rax
    push rcx
    push rdx
    push r8
    push r9
    push r10
    push r11


%endmacro

%macro isr_end 1
    pop r11
    pop r10
    pop r9
    pop r8
    pop rdx
    pop rcx
    pop rax
    pop rsi
    pop rdi
    sti
    push rax
    mov al, 0x20
    out 0x20, al
    %if %1 >= 40
        out 0xA0, al
    %endif
    pop rax
    iretq
%endmacro

%macro isr_complete 2
[extern %2]

global isr_%1
isr_%1:
    isr_common %1
    call %2
    isr_end %1
%endmacro

[extern unmapped_or_reserved_interrupt]

%macro isr_unmapped 1
global isr_%1
isr_%1:
    isr_common %1
    push rdi
    mov rdi, %1
    call unmapped_or_reserved_interrupt
    pop rdi
    isr_end %1
%endmacro

isr_complete 0, divide_by_zero_interrupt
isr_complete 1, debug_interrupt
isr_complete 2, non_maskable_interrupt
isr_complete 3, breakpoint_interrupt
isr_complete 4, overflow_interrupt
isr_complete 5, bound_range_exceeded_interrupt
isr_complete 6, invalid_opcode_interrupt
isr_complete 7, device_not_available_interrupt
isr_complete 8, double_fault_interrupt
isr_complete 9, coprocessor_segment_overrun_interrupt
isr_complete 10, invalid_tss_interrupt
isr_complete 11, segment_not_present_interrupt
isr_complete 12, stack_segment_fault_interrupt
isr_complete 13, general_protection_fault_interrupt
isr_complete 14, page_fault_interrupt
isr_unmapped 15
isr_complete 16, floating_point_error_interrupt
isr_complete 17, alignment_check_interrupt
isr_complete 18, machine_check_interrupt
isr_complete 19, simd_floating_point_exception_interrupt
isr_complete 20, virtualization_exception_interrupt
isr_complete 21, control_protection_exception_interrupt
isr_unmapped 22
isr_unmapped 23
isr_unmapped 24
isr_unmapped 25
isr_unmapped 26
isr_unmapped 27
isr_unmapped 28
isr_unmapped 29
isr_unmapped 30
isr_unmapped 31
isr_complete 32, timer_interrupt
isr_unmapped 33
isr_unmapped 34
isr_unmapped 35
isr_unmapped 36
isr_unmapped 37
isr_unmapped 38
isr_unmapped 39
isr_unmapped 40
isr_unmapped 41
isr_unmapped 42
isr_unmapped 43
isr_unmapped 44
isr_unmapped 45
isr_unmapped 46
isr_unmapped 47
isr_unmapped 48
isr_unmapped 49
isr_unmapped 50
isr_unmapped 51
isr_unmapped 52
isr_unmapped 53
isr_unmapped 54
isr_unmapped 55
isr_unmapped 56
isr_unmapped 57
isr_unmapped 58
isr_unmapped 59
isr_unmapped 60
isr_unmapped 61
isr_unmapped 62
isr_unmapped 63
isr_unmapped 64
isr_unmapped 65
isr_unmapped 66
isr_unmapped 67
isr_unmapped 68
isr_unmapped 69
isr_unmapped 70
isr_unmapped 71
isr_unmapped 72
isr_unmapped 73
isr_unmapped 74
isr_unmapped 75
isr_unmapped 76
isr_unmapped 77
isr_unmapped 78
isr_unmapped 79
isr_unmapped 80
isr_unmapped 81
isr_unmapped 82
isr_unmapped 83
isr_unmapped 84
isr_unmapped 85
isr_unmapped 86
isr_unmapped 87
isr_unmapped 88
isr_unmapped 89
isr_unmapped 90
isr_unmapped 91
isr_unmapped 92
isr_unmapped 93
isr_unmapped 94
isr_unmapped 95
isr_unmapped 96
isr_unmapped 97
isr_unmapped 98
isr_unmapped 99
isr_unmapped 100
isr_unmapped 101
isr_unmapped 102
isr_unmapped 103
isr_unmapped 104
isr_unmapped 105
isr_unmapped 106
isr_unmapped 107
isr_unmapped 108
isr_unmapped 109
isr_unmapped 110
isr_unmapped 111
isr_unmapped 112
isr_unmapped 113
isr_unmapped 114
isr_unmapped 115
isr_unmapped 116
isr_unmapped 117
isr_unmapped 118
isr_unmapped 119
isr_unmapped 120
isr_unmapped 121
isr_unmapped 122
isr_unmapped 123
isr_unmapped 124
isr_unmapped 125
isr_unmapped 126
isr_unmapped 127
isr_complete 128, system_call
isr_unmapped 129
isr_unmapped 130
isr_unmapped 131
isr_unmapped 132
isr_unmapped 133
isr_unmapped 134
isr_unmapped 135
isr_unmapped 136
isr_unmapped 137
isr_unmapped 138
isr_unmapped 139
isr_unmapped 140
isr_unmapped 141
isr_unmapped 142
isr_unmapped 143
isr_unmapped 144
isr_unmapped 145
isr_unmapped 146
isr_unmapped 147
isr_unmapped 148
isr_unmapped 149
isr_unmapped 150
isr_unmapped 151
isr_unmapped 152
isr_unmapped 153
isr_unmapped 154
isr_unmapped 155
isr_unmapped 156
isr_unmapped 157
isr_unmapped 158
isr_unmapped 159
isr_unmapped 160
isr_unmapped 161
isr_unmapped 162
isr_unmapped 163
isr_unmapped 164
isr_unmapped 165
isr_unmapped 166
isr_unmapped 167
isr_unmapped 168
isr_unmapped 169
isr_unmapped 170
isr_unmapped 171
isr_unmapped 172
isr_unmapped 173
isr_unmapped 174
isr_unmapped 175
isr_unmapped 176
isr_unmapped 177
isr_unmapped 178
isr_unmapped 179
isr_unmapped 180
isr_unmapped 181
isr_unmapped 182
isr_unmapped 183
isr_unmapped 184
isr_unmapped 185
isr_unmapped 186
isr_unmapped 187
isr_unmapped 188
isr_unmapped 189
isr_unmapped 190
isr_unmapped 191
isr_unmapped 192
isr_unmapped 193
isr_unmapped 194
isr_unmapped 195
isr_unmapped 196
isr_unmapped 197
isr_unmapped 198
isr_unmapped 199
isr_unmapped 200
isr_unmapped 201
isr_unmapped 202
isr_unmapped 203
isr_unmapped 204
isr_unmapped 205
isr_unmapped 206
isr_unmapped 207
isr_unmapped 208
isr_unmapped 209
isr_unmapped 210
isr_unmapped 211
isr_unmapped 212
isr_unmapped 213
isr_unmapped 214
isr_unmapped 215
isr_unmapped 216
isr_unmapped 217
isr_unmapped 218
isr_unmapped 219
isr_unmapped 220
isr_unmapped 221
isr_unmapped 222
isr_unmapped 223
isr_unmapped 224
isr_unmapped 225
isr_unmapped 226
isr_unmapped 227
isr_unmapped 228
isr_unmapped 229
isr_unmapped 230
isr_unmapped 231
isr_unmapped 232
isr_unmapped 233
isr_unmapped 234
isr_unmapped 235
isr_unmapped 236
isr_unmapped 237
isr_unmapped 238
isr_unmapped 239
isr_unmapped 240
isr_unmapped 241
isr_unmapped 242
isr_unmapped 243
isr_unmapped 244
isr_unmapped 245
isr_unmapped 246
isr_unmapped 247
isr_unmapped 248
isr_unmapped 249
isr_unmapped 250
isr_unmapped 251
isr_unmapped 252
isr_unmapped 253
isr_unmapped 254
isr_unmapped 255