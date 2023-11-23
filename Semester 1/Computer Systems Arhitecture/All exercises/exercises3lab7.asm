bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
    sir DW 1045, 235, 1123
    len equ ($-sir)/2
    ten db 10
    b times len*3 db 0
    r times len db 0
segment  code use32 class=code ; code segment
    start:
    ;Being given a string of words, obtain the string (of bytes) of the digits in base 10 of each word from this string
    ;the result will be 1, 0, 4, 5, 2, 3, 5, 1, 1, 2, 3
    mov ecx, len
    mov esi, sir+len+1      ;index for sir
    mov edi, 0              ;index for the new string
    jecxz end_loop
    add_elem_digit:
        std
        lodsw           ;AX->DS:ESI
        while_1:
        div byte [ten]  ;AL=AX/10   AH=AX%10
        mov [b+edi], AH
        add edi,1
        mov AH, 0
        cmp AX, 0
        ja while_1
    loop add_elem_digit
    end_loop:
    mov ecx, edi
    mov esi, b    ;index for b
    cld
    jecxz end_loop_1
    reverse_order:
        lodsb
        mov [r+edi], AL  ;we add the elements from b in a reverse order
        dec edi
    loop reverse_order
    end_loop_1:
    call [exit]   
    