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
    d  dw 15
segment  code use32 class=code ; code segment
start: 
    ;d-[3*(a+b+2)-5*(c+2)] a,b,c - byte, d - word
    mov AL, [a]
    add AL, [b]  ;AL->>a+b 
    
    add AL, 2  ;AL->>a+b+2
    
    mov BL, 3
    mul BL 
    mov CX, AX ; AL*BL-->AL=3*(a+b+2)
    
    mov BL, [c]
    add BL, 2
    mov AL, 5
    mul BL   ;BL->5*(c+2)
    
    sub CX, AX  ;CX->>3*(a+b+2)-5*(c+2)
    
    mov AX, [d]
    sub AX, CX  ;AX->>d-[3*(a+b+2)-5*(c+2)]
    call[exit]