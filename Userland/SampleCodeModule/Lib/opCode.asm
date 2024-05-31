section .text
global op_code

op_code:
    push rbp
    mov rbp, rsp

    jmp 0x0000000000000000 

    mov rsp, rbp
    pop rbp
    ret
