bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
    ;signed
    a  db 2 
	b  dw 80
    c dd 125
    d dq 80
segment  code use32 class=code ; code segment
start:    ;d-a+(b+a-c)=80-2+(80+2-125)=78-43=35          a - byte, b - word, c - double word, d - qword - Signed representation
    mov AL, [a]  ;AL->a
    cbw         ;AL->AX
    add AX,[b]  ;AX->b+a
    cwde        ;AX->EAX
    sub EAX,[c]  ;EAX->  b+a-c=-43
    cdq             ;EAX->EDX:EAX
    add EAX, [d]   ;EAX=EAX+[d] and set the CF
    adc EDX, [d+4] ;EDX=EDX+[d+4]+CF
    push EAX
    pop ECX
    push EDX
    pop EBX
    mov AL,[a]
    cbw
    cwde
    cdq
    sub ECX,EAX
    sbb EBX,EDX
    call [exit]