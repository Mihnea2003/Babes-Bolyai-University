bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
    ;unsigned
    a  db 2 
	b  dw 80
    c dd 125
    d dq 80
segment  code use32 class=code ; code segment
start:    ;a - byte, b - word, c - double word, d - qword - Unsigned representation
            ;(c-a) + (b - d) +d    123+0+80=203
    mov EBX, [c]
    mov AL, [a]
    mov AH, 0  ;AL-AX
    mov DX, 0   ;AX-DX:AX
    push DX
    push AX
    pop EAX     ;DX:AX->EAX
    sub EBX,EAX ;EBX->c-a
    mov AX, [b] ;AX->b
    mov DX, 0   ;AX-DX:AX
    push DX
    push AX
    pop EAX     ;DX:AX->EAX
    mov EDX, 0  ;EAX->EDX:EAX
    sub EAX, [d]   ;EAX=EAX-[d] and set the CF
    sbb EDX, [d+4]     ;EDX=EDX-[d+4]-CF
    add EAX, EBX    ;EDX:EAX->(c-a) + (b - d)
    add EAX, [d]    ;EAX=EAX+[d] and set the CF
    adc EDX, [d+4]  ;EDX=EDX+[d+4]+CF   the result is in the EDX:EAX
call [exit]