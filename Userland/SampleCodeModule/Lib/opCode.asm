section .text
global op_code

op_code:
    push rbp
    mov rbp, rsp

    ; acá deberíamos hacer algo
    nop

    mov rsp, rbp
    pop rbp
    ret
