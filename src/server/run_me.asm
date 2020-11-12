GLOBAL hideme

section .RUN_ME
nothing:
    mov rax, 10
    ret
    
section .text
hideme:
    mov rax,'E'
    mov rax,'A'
    mov rax,'S'
    mov rax,'T'
    mov rax,'E'
    mov rax,'R'
    mov rax,'E'
    mov rax,'G'
    mov rax,'G'
    ret