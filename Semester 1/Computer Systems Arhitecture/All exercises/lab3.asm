bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
    ;signed
    a  dd 125 
	b  db 120
    c dw 12
    d db 2
    e dq 80
segment  code use32 class=code ; code segment
start: 
    ;a+b/c-d*2-e=125+10-4-80=51
    ;b/c
    mov AL, [b]  ;AL->DX:AX
    cbw ;AL->AX
    cwd ;AX->DX:AX 
    mov AH, 0  ;AL-AX
    mov DX, 0   ;AX-DX:AX
    idiv word [c] ;  AX=DX:AX/c=b/c=120/12=10
    mov BX, AX  ;BX=b/c
    
    ;d*2
    mov AL, 2
    imul byte [d] ;AX=d*AL
    
    
    ;b/c-d*2  BX-AX
    sub BX, AX ;BX=b/c-d*2 =10-4=6
    
    ;a+BX
    mov AX, BX 
    cwde ; AX->EAX
    ;EAX=b/c-d*2 =10-4=6
    add EAX, [a]  ;EAX=a+b/c-d*2 =125+6
    
    ;EAX-e
    cdq ;EAX->EDX:EAX -a+b/c-d*2 
    
    sub EAX, [e] ;EAX=EAX-e and set CF
    sbb EDX, [e+4] ; EDX=EDX-[e+4]-CF
    
    ;EDX:EAX=a+b/c-d*2-e
    call [exit]