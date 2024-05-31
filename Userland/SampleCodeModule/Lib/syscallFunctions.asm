GLOBAL sys_read
GLOBAL sys_write
GLOBAL sys_get_register_snapshot
GLOBAL sys_beep
GLOBAL sys_set_font_size
GLOBAL sys_clear_screen
GLOBAL sys_put_pixel
GLOBAL sys_put_rectangle
GLOBAL sys_draw_letter
GLOBAL sys_set_mode
GLOBAL sys_get_screen_information
GLOBAL sys_nano_sleep

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


%macro pushStateMinusRax 0
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

%endmacro

%macro popStateMinusRax 0
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
%endmacro


%macro sys_interrupt 1
        mov rax, %1
        int 80h
%endmacro



%macro simple_sys_handler 1
    push rbp
    mov rbp, rsp
    mov rax, %1
    int 80h
    mov rsp, rbp
    pop rbp
    ret
%endmacro


sys_read:
    push rbp
    mov rbp, rsp
    mov rax, 0
    int 80h
    mov rsp, rbp
    pop rbp
    ret

sys_write:
    push rbp
    mov rbp, rsp
    mov rax, 1
    int 80h
    mov rsp, rbp
    pop rbp
    ret

; int64_t sys_get_register_snapshot(RegisterSet * registers);
sys_get_register_snapshot:
    simple_sys_handler 2

; int64_t sys_beep(uint64_t frequency, uint64_t duration);
sys_beep:
    simple_sys_handler 3

; int64_t sys_set_font_size(uint64_t size);
sys_set_font_size:
    simple_sys_handler 4

; int64_t sys_clear_screen(void);
sys_clear_screen:
    simple_sys_handler 5

; int64_t sys_put_pixel(uint64_t x, uint64_t y, Color * color);
sys_put_pixel:
    simple_sys_handler 6

; int64_t sys_put_rectangle(uint64_t x, uint64_t y, uint64_t width, uint64_t height, Color * color);
sys_put_rectangle:
    simple_sys_handler 7

; int64_t sys_draw_letter(uint64_t x, uint64_t y, char letter, Color * color);
sys_draw_letter:
    simple_sys_handler 8

; int64_t sys_set_mode(uint64_t mode);
sys_set_mode:
    simple_sys_handler 9

; int64_t sys_get_screen_information(ScreenInformation * screen_information);
sys_get_screen_information:
    simple_sys_handler 10

sys_nano_sleep:
    simple_sys_handler 11