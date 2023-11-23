bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
    a  dq 1122334455667788
	b  dq 0abcdef1a2b3c4d5e 
segment  code use32 class=code ; code segment
start: 
    mov EAX, [a]
    mov EDX, [a+4]
    
    add EAX, [b]
    adc EDX, [b+4]
    
    mov ECX, [b] ; ECX-2b3c4d5e
    mov EBX, [b+4]  ;ebx-2b3c4d5e
    
    add EAX, ECX ;EAX=EAX+ECX and set the CF
    adc EDX, EBX ;EDX=EDX+EBX+CF
    call[exit]