section .data
    result db '0', 0xA, 0xA  ; buffer to store the result with two newline characters

section .text
    global _start

_start:
    ; Initialize variables
    mov dword [x], 5        ; Initialize x to 5
    mov ecx, 0              ; Initialize loop counter i to 0

loop_start:
    ; Check loop condition (i < 5)
    cmp ecx, 5
    jge loop_end            ; Jump to loop_end if i >= 5

    ; Execute loop body (x = x + 1)
    mov eax, [x]            ; Load x into eax
    add eax, 1              ; Increment x by 1
    mov [x], eax            ; Store the result back to x

    ; Increment loop counter (i = i + 1)
    inc ecx

    ; Continue looping
    jmp loop_start

loop_end:
    ; Convert x to ASCII
    mov eax, [x]            ; Load x into eax
    mov ebx, 10             ; Base 10
    call convert_to_ascii   ; Call subroutine to convert x to ASCII

    ; Write result to console with a line gap
    mov eax, 1              ; syscall number for sys_write
    mov edi, 1              ; file descriptor 1 is stdout
    mov edx, 3              ; number of bytes to write (1 digit + 2 newlines)
    mov esi, result         ; pointer to string to output
    syscall                 ; call kernel

    ; Exit the program
    mov eax, 60             ; syscall number for sys_exit
    xor edi, edi            ; exit code 0
    syscall                 ; call kernel

convert_to_ascii:
    ; Convert number in eax to ASCII and store in result buffer
    mov ecx, 0              ; Initialize counter
    mov byte [result + 2], 0xA ; Add a newline character at the end
    add ecx, 2              ; Move to the end of the buffer (before newline)
convert_loop:
    dec ecx                 ; Move back one position
    mov edx, 0              ; Clear the upper bits of edx
    mov ebx, 10             ; Set base 10
    div ebx                 ; Divide by 10
    add dl, '0'             ; Convert remainder to ASCII
    mov [result + ecx], dl  ; Store ASCII character in result buffer
    test eax, eax           ; Check if quotient is zero
    jnz convert_loop        ; If not zero, continue the loop
    ret

section .bss
    x resd 1                ; Reserve space for x (4 bytes)
