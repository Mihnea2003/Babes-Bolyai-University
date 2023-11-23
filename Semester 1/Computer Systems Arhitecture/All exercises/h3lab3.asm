bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
    ;unsigned
    a  db 8 
	b  dw 2
    e dd 125
    x dq 80
segment  code use32 class=code ; code segment
    start:  ;(a*a/b+b*b)/(2+b)+e-x=(8 * 8 / 2+2*2)/(2+2)+125-80=36/4+125-80=9+125-80=54; a-byte; b-word; e-doubleword; x-qword  
        mov AL, [a]
        mul byte [a]   ;AX->a*a

        mov DX, 0

        div word [b]    

        mov BX, AX
        mov CX, 0 ; from AX:DX -> CX:BX now

        mov AX, [b]
        mul word [b] ; result in DX:AX

        add AX, BX
        adc DX, CX ; CX:BX + DX:AX

        mov BX, [b]
        add BX, 2
        div BX ; result in AX
        
        mov BX, AX
        mov EAX, 0
        mov AX, BX ; AX -> EAX unsigned

        mov EBX, [e]
        add EAX, EBX
        
        mov EDX, 0 ; EDX:EAX is my number
        sub EAX, [x]
        sbb EDX, [x + 4] ; result in EDX:EAX
        call [exit]
    
    