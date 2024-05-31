
GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
GLOBAL _hlt

GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler
GLOBAL _irq80Handler

GLOBAL _exception0Handler
GLOBAL _exception6Handler

GLOBAL regs_shot

EXTERN irqDispatcher
EXTERN exceptionDispatcher
EXTERN sysCallHandler
EXTERN should_take_reg_shot

SECTION .text

%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
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
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

%macro pushStateMinusRax 0
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
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
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
%endmacro

%macro irqHandlerMaster 1
	pushState

	mov rdi, %1 ; pasaje de parametro
	call irqDispatcher

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popState
	iretq
%endmacro

;   HACER macro saveRegs
;
;
;

%macro exceptionHandler 1
	pushState

	mov rdi, %1 ; pasaje de parametro
	call exceptionDispatcher

	popState
	iretq
%endmacro


_hlt:
	sti
	hlt
	ret

_cli:
	cli
	ret


_sti:
	sti
	ret

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di  ; ax = mascara de 16 bits
    out	0A1h,al
    pop     rbp
    retn


;8254 Timer (Timer Tick)
_irq00Handler:
	irqHandlerMaster 0

;Keyboard
_irq01Handler:
    pushState

	mov rdi, 1
	call irqDispatcher

	call should_take_reg_shot
	cmp rax, 1

	jne .keyboard_end
	popState
	pushState

	; CAMBIAR!!!
    ; mov rax, 0x21
    ; mov rbx, 0x02
    ; mov rcx, 0x03
    ; mov rdx, 0x04
    ; mov rsi, 0x05
    ; mov rdi, 0x06
    ; mov rbp, 0x07
    ; mov rsp, 0x08
    ; mov r8, 0x09
    ; mov r9, 0x0A
    ; mov r10, 0x0B
    ; mov r11, 0x0C
    ; mov r12, 0x0D
    ; mov r13, 0x0E
    ; mov r14, 0x0F
    ; mov r15, 0x10
	; save registers
    mov [regs_shot + 8 * 0 ], rax
    mov [regs_shot + 8 * 1 ], rbx
    mov [regs_shot + 8 * 2 ], rcx
    mov [regs_shot + 8 * 3 ], rdx
    mov [regs_shot + 8 * 4 ], rsi
    mov [regs_shot + 8 * 5 ], rdi
    mov [regs_shot + 8 * 6 ], rbp
    mov rax, [rsp+18*8]
    ;add rax, 16 * 8 ; es lo que se decremento rsp con la macro pushState y el pusheo de la dir. de retorno
    mov [regs_shot + 8 * 7 ], rax             ;rsp
    mov [regs_shot + 8 * 8 ], r8
    mov [regs_shot + 8 * 9 ], r9
    mov [regs_shot + 8 * 10], r10
   	mov [regs_shot + 8 * 11], r11
   	mov [regs_shot + 8 * 12], r12
   	mov [regs_shot + 8 * 13], r13
   	mov [regs_shot + 8 * 14], r14
   	mov [regs_shot + 8 * 15], r15
   	mov rax, [rsp+15*8]; posicion en el stack de la dir. de retorno (valor del rip previo al llamado de la interrupcion)
   	; mov rax, 0x40               ; CAMBIAR!!!
   	mov [regs_shot + 8 * 16], rax

.keyboard_end:
	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popState
	iretq

;Cascade pic never called
_irq02Handler:
	irqHandlerMaster 2

;Serial Port 2 and 4
_irq03Handler:
	irqHandlerMaster 3

;Serial Port 1 and 3
_irq04Handler:
	irqHandlerMaster 4

;USB
_irq05Handler:
	irqHandlerMaster 5

;SYSCALL
_irq80Handler:
	pushState
	mov rdi, rsp ; Pasaje de Registros

	call sysCallHandler
	


	popStateMinusRax
	add rsp, 8 ; Restore the stack pointer

	iretq

;	push rax
;	push rbx
;	push rcx
;	push rdx
;	push rdi
;	push rsi
;   call sysHandler
;   pop rsi
;   pop rdi
;   pop rdx
;   pop rcx
;   pop rbx
;   pop rax
;   iretq



;Zero Division Exception
_exception0Handler:
	exceptionHandler 0

;Invalid operation code exception
_exception6Handler:
	exceptionHandler 6


haltcpu:
	cli
	hlt
	ret



SECTION .bss
	aux resq 1


SECTION .data
    regs_shot dq 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ; 17 zeros
	; %define REGS_AMOUNT 17