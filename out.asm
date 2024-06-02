section .data
   result db '0', 0xA, 0xA  ; buffer to store the result with two newline characters
section .text
   global _start
_start:
    ;; let
    mov rax, 0
    push rax
    ;; /let
    ;; exit
    mov rax, 56
    push rax
    mov rax, 60
    pop rdi
    syscall
    ;; /exit
    mov rax, 60
    mov rdi, 0
    syscall
