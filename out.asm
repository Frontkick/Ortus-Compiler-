section .data
   result db '0', 0xA, 0xA  ; buffer to store the result with two newline characters
section .text
   global _start
_start:
    ;; let
    mov rax, 100
    push rax
    ;; /let
    ;; exit
    push QWORD [rsp + 0]
    mov rax, 60
    pop rdi
    syscall
    ;; /exit
    mov rax, 60
    mov rdi, 0
    syscall
