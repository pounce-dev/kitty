[bits 64]
function:
    int 0x80
    int 0x80
    int 0x80
    int 0x80
    ;mov [0x8000], byte 15
    jmp $
; returning from this causes a page fault??? what is even happening...
extern set_kernel_stack
global enter_usermode
enter_usermode:
    mov ax, 0x20 | 3
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov rax, rsp
    push 0x20 | 3
    push rax
    pushfq
    push 0x18 | 3
    push function
    ;mov rsi, rsp
    ;call set_kernel_stack
    ;jmp set_kernel_stack
    iretq