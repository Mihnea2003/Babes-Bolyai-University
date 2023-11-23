bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
    ;signed
    s1 db 1,2,3,4,5,6,7,8,9,10
    lens1 equ $-s1   ;the length of s1
    
    sum db 0
segment  code use32 class=code ; code segment
    start:
    ;sum of elements(bytes) in s1
    mov bl, 0 ;compute the sum here
    mov ecx, lens1
    mov esi, 0
    jecxz skip_loop
    sum_loop:
        mov AL, [s1+esi]  ;s1[esi]
        add bl, al 
        inc esi 
    loop sum_loop
    skip_loop:
    
    mov [sum], bl
    call [exit]