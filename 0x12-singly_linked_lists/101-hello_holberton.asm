section .data
    hello_msg db "Hello, Holberton,", 0
    format db "%s", 0

section .text
    extern printf

global main

main:
    push rbp
    mov rdi, format
    mov rsi, hello_msg
    call printf
    pop rbp
    ret
