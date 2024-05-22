GLOBAL syscallRead
Global syscallWrite

section .text

%macro pushState 0
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
%endmacro

%macro popState 0
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax
%endmacro

syscallRead:
    push rbp
    mov rbp, rsp
    pushState
    mov rax, 0
    int 80h
    popState
    mov rsp, rbp
    pop rbp
    ret

syscallWrite:
    push rbp
    mov rbp, rsp
    pushState
    mov rax, 1
    int 80h
    popState
    mov rsp, rbp
    pop rbp
    ret