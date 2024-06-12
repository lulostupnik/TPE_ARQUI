section .text
global infinite_stack

infinite_stack:
    push rbp
    mov rbp, rsp

    sub rsp, 16 ; es decir rsp es rbp - 16
    mov rcx, 0x0000000080000000

.loop:
    ; mov rax, 0x0000000012345678
    mov rax, 0x1234567890ABCDEF
    mov [rsp], rax
    dec rcx
    jnz .loop


    mov rsp, rbp
    pop rbp
    ret


