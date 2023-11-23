bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
    a  db 15
	b  db 5
    c  db 5
    d  db 15
segment  code use32 class=code ; code segment
start: 
    ;(a-b)+(d-c)  a,b,c,d - byte
    mov AX, [a]
    sub AX, [b] ;  AX ->>a-b 
    mov BX, [d]
    sub BX, [c] ;  BX-->>d-c
    add AX, BX ; AX->>(a-b)+(d-c)
    call [exit]
    