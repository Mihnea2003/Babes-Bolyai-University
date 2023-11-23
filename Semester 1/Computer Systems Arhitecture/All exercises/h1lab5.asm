bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
    a db 2,1,-3
    lena equ $-a   ;the length of a
    b db 4,5,7
    lenb equ $-b   ;the length of b
    r times lena+lenb db 0 
segment  code use32 class=code ; code segment
    start:
    ;Two byte strings A and B are given. 
    ;Obtain the string R by concatenating the elements of B in reverse order and the negative elements of A
    ;in R it should be R:  7, 5, 4, -3
    mov ecx, lenb
    mov esi, lenb-1   ;index for b
    mov edi, 0       ;index for r
    jecxz end_loop
    add_elem_b:
        mov AL, [b+esi]
        mov [r+edi], AL  ;we add the elements from b in a reverse order
        dec esi
        inc edi
    loop add_elem_b
    end_loop:
    
    mov esi, 0
    mov ecx, lena
    jecxz end_loop2
    add_neg_elem_a:
        mov AH, [a+esi]
        cmp AH, 0
        jge do_nothing
            mov AL, [a+esi]
            mov [r+edi], AL
            inc edi
        do_nothing:
        inc esi
    loop add_neg_elem_a
    end_loop2:
    
    call [exit]
    