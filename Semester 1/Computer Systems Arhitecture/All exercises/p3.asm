bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
    a  dw 15
	b  dw 5
    c  dw 5
    d  dw 15
segment  code use32 class=code ; code segment
start: 
    ;a-c+d-7+b-(2+d)   a,b,c,d - word
    mov AX, [a]
    sub AX, [c]  ;AX->>a-c
    add AX, [d]  ;AX->>a-c+d
    sub AX, 7    ;AX->>a-c+d-7
    mov BX, 2
    sub BX, [d]  ;BX->>2+d
    sub AX, BX ;AX->>a-c+d-7+b-(2+d)
    call [exit]
    