; kitty kernel boot sector file
;
; Authors: 	BYU-I OS development team
; Git:		https://github.com/BYUi-OSDevelopment/kitty/
; Date:		2023-10-24

[org 0x7c00]			; boot sector starts at address 0x7c00

mov [BOOT_DRIVE], dl		; set boot drive to DL


load_bootsect: ; load the remaining part of the boot sector (just the text we print) because it's too large to fit in 512 bytes!
    xor ax, ax			; set ax to 0
    mov ds, ax			; set data segment (ds) to value of ax (0)
    cld				; clear direction flag
    mov ah, 0x02			; read sectors from drive
    mov al, 1			; specify numbers of sectors in decimal
    mov dh, 0			; specify drive head
    mov ch, 0			; start at cylinder 0
    mov cl, 2			; start at sector 2
    xor bx, bx			; make entire register 0s
    mov es, bx			; now bx is starting point in RAM
    mov bx, 0x7e00			; set bx to end of drive (address 0x7e00)

    int 0x13			; load bios interrupt calls

mov cl, 0

; clears the screen, sets cursor position + page number
print_clear:
    mov ah, 0x00
    mov al, 0x03
    int 0x10
    mov ah, 0x02
    mov bh, 0
    mov dh, 0
    mov dl, 0
    int 0x10
mov bx, LOAD_TEXT
print_drive_menu: ; put address of LOAD_TEXT into bx!
    mov ah, 0x0e
    mov al, [bx]
    int 0x10
    inc bx
    cmp [bx], byte 0
    jne print_drive_menu
check_and_print_x:
    cmp cl, byte 0 ; figure out what is selected, and put the cursor in the right place
    jne check_1
    mov dh, 2
    jmp print_x
    check_1:
    cmp cl, byte 1
    jne check_2
    mov dh, 3
    jmp print_x
    check_2:
    mov dh, 4
    print_x:
    mov ah, 0x02
    mov bh, 0
    mov dl, 4
    int 0x10
    mov ah, 0x0e
    mov al, 'X'
    int 0x10
    jmp get_input
get_input:
    mov ah, 0x00 ; waits until keyboard input and then redraws the screen. Moves up with any non-specified keys
    int 0x16
    cmp ah, 0x48
    je move_up
    cmp ah, 0x50
    je move_down
    cmp ah, 0x1C
    je load_kernel
move_up:
    cmp cl, 0
    je get_input
    dec cl
    jmp clear_x
move_down:
    cmp cl, 2
    je get_input
    inc cl
    jmp clear_x
clear_x:
    mov ah, 0x02
    mov bh, 0
    mov dl, 4
    int 0x10
    mov ah, 0x0e
    mov al, ' '
    int 0x10
    jmp check_and_print_x
; start boot process

load_kernel:
    xor ax, ax			; set ax to 0
    mov ds, ax			; set data segment (ds) to value of ax (0)
    cld				; clear direction flag
    mov ah, 0x02			; read sectors from drive
    mov al, 63			; specify numbers of sectors in decimal
    mov dh, 0			; specify drive head

    cmp cl, byte 0
    je default_drive_set
    cmp cl, byte 1
    je floppy_drive_set
    cmp cl, byte 2
    je hard_drive_set
    default_drive_set:
    mov dl, [BOOT_DRIVE]
    jmp continue_copy
    floppy_drive_set:
    mov dl, 0x00
    jmp continue_copy
    hard_drive_set:
    mov dl, 0x80
    jmp continue_copy
    continue_copy:			; specify drive
    mov ch, 0			; start at cylinder 0
    mov cl, 3			; start at sector 2
    xor bx, bx			; make entire register 0s
    mov es, bx			; now bx is starting point in RAM
    mov bx, 0x8000			; set bx to end of drive (address 0x7e00)

    int 0x13			; load bios interrupt calls

enter_protected:
    cli
    lgdt [gdt_descriptor]
    mov eax, cr0
    or al, 0x1
    mov cr0, eax
    jmp CODE_SEG:segment_switch

; DATA
gdt_start:
    dd 0x0
    dd 0x0

gdt_code:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10011010b
    db 11001111b
    db 0x0

gdt_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

BOOT_DRIVE:	db 0		; define BOOT_DRIVE label

[bits 32] ; code again

segment_switch:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000
    mov esp, ebp
    in al, 0x92 ; enable A20 gate
    or al, 2
    out 0x92, al

check_for_long_mode:
    pushfd ; begin check for CPUID
    pushfd
    xor dword [esp],0x00200000
    popfd
    pushfd
    pop eax
    xor eax,[esp]
    popfd
    xor eax, ecx
    jz jump_to_kernel ; if CPUID doesn't exist, jump to the kernel
    mov eax, 0x80000000
    cpuid
    cmp eax, 0x80000001
    jb jump_to_kernel
    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29
    jz jump_to_kernel

jump_to_long_mode:
    ; setting up paging
    mov edi, 0x1000
    mov cr3, edi
    xor eax, eax
    mov ecx, 4096
    rep stosd
    mov edi, cr3
    mov dword [edi], 0x2007
    add edi, 0x1000
    mov dword [edi], 0x3007
    add edi, 0x1000
    mov dword [edi], 0x4007
    add edi, 0x1000
    mov ebx, 0x000000007
    mov ecx, 512


map_first_two_MB:
    mov DWORD [edi], ebx
    add ebx, 0x1000
    add edi, 8
    loop map_first_two_MB

enable_PAE_paging:
    mov eax, cr4 ; CR4 5th bit is PAE
    or eax, 1 << 5
    mov cr4, eax

enable_paging:
    mov ecx, 0xC0000080 ; This is the IA32_EFER MSR
    rdmsr
    or eax, 1 << 8 ; Enable LME (IA-32e Mode), enabling 4-level paging
    wrmsr
    mov eax, cr0 ; CR0 31st bit is PG (enable paging)
    or eax, 1 << 31
    ; write protection disable
    and eax, 0b11111111111111101111111111111111
    mov cr0, eax
lgdt [GDT.Pointer]
jmp GDT.Code:kernel_64
; Access bits
PRESENT        equ 1 << 7
NOT_SYS        equ 1 << 4
EXEC           equ 1 << 3
DC             equ 1 << 2
RW             equ 1 << 1
ACCESSED       equ 1 << 0

; Flags bits
GRAN_4K       equ 1 << 7
SZ_32         equ 1 << 6
LONG_MODE     equ 1 << 5

; the following code populates the first 512 bytes of the drive
times 510-($-$$) db 0		; for 510 bytes minus the beginning of file, write 0
dw 0xAA55			; magix number
SECTOR_TWO_BEGINS:

GDT: ; 64 bit GDT, taken from https://wiki.osdev.org/Setting_Up_Long_Mode ; CC0 Licensing (Public Domain)
    .Null: equ $ - GDT
        dq 0
    .Code: equ $ - GDT
        dd 0xFFFF                                   ; Limit & Base (low, bits 0-15)
        db 0                                        ; Base (mid, bits 16-23)
        db PRESENT | NOT_SYS | EXEC | RW            ; Access
        db GRAN_4K | LONG_MODE | 0xF                ; Flags & Limit (high, bits 16-19)
        db 0                                        ; Base (high, bits 24-31)
    .Data: equ $ - GDT
        dd 0xFFFF                                   ; Limit & Base (low, bits 0-15)
        db 0                                        ; Base (mid, bits 16-23)
        db PRESENT | NOT_SYS | RW                   ; Access
        db GRAN_4K | SZ_32 | 0xF                    ; Flags & Limit (high, bits 16-19)
        db 0                                        ; Base (high, bits 24-31)
    .TSS: equ $ - GDT
        dd 0x00000068
        dd 0x00CF8900
    .Pointer:
        dw $ - GDT - 1
        dq GDT

LOAD_TEXT:
    db 0xA, 0xD,0xA, 0xD,'   [ ] Default Drive',0xA, 0xD,'   [ ] Floppy Drive',0xA, 0xD,'   [ ] Hard Drive',0xA, 0xD
    db ' _                    ',0xA, 0xD
    db '| | __ _ _______ _ __ ',0xA, 0xD
    db '| |/ _` |_  / _ \  __|',0xA, 0xD
    db '| | (_| |/ /  __/ |   ',0xA, 0xD
    db '|_|\__,_/___\___|_|'
    db 0		; text
jump_to_kernel:
    call 0x8000 ; jump to our kernel :), this probably isn't right

[BITS 64] ; might have to modify this in the future to perform a far return.
kernel_64:
    cli
    mov ax, GDT.Data
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    call 0x8000

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

times 512-($-SECTOR_TWO_BEGINS) db 0