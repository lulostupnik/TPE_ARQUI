GLOBAL cpuVendor
GLOBAL getKey

section .text
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret

;https://wiki.osdev.org/%228042%22_PS/2_Controller
; uint8_t getKey();
getKey:
    push rbp
    mov rbp, rsp

    in al, 60h

    leave
    ret
