bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
    ;signed
    a  dw 001110000001100b 
	b  dw 110011101000111b
    c  dd 0
segment  code use32 class=code ; code segment
    start:
    ;Given the words A and B, compute the doubleword C as follows:
    ;the bits 0-3 of C are the same as the bits 5-8 of B
    ;the bits 4-10 of C are the invert of the bits 0-6 of B
    ;the bits 11-18 of C have the value 1
    ;the bits 19-31 of C are the same as the bits 3-15 of B
    
        mov EBX, [c]  ;we compute the result in EDX
        
        mov AX, [b] 
        and AX, 000000111100000b    ;we isolate bits 5-8 of B
        mov CL, 5
        ror AX, CL ;we rotate 10 positions to the right
        mov DX, 0
        push dx
        push ax
        pop eax
        or EBX, EAX ;we put the bits into the result EBX->00000000000000000000000000001010b

        mov AX, [b] 
        XOR AX, 111111111111111b    ;we invert the bits
        and AX, 000000001111111b    ;we isolate bits 0-6 of B
        mov CL, 4
        rol AX, CL  ;rotate to the left 4 positions
        mov DX, 0
        push dx
        push ax
        pop eax
        or EBX,EAX  ;we put the bits into the result EDX->00000000000000000000001110001010b
        
        or EBX,00000000000001111111100000000000b ;we force the value of bits 11-18 of the result to the value 1
        ;EBX-> 00000000000001111111101110001010b
        
        mov AX, [b] 
        mov DX, 0
        push dx
        push ax
        pop eax
        and EAX, 00000000000000001111111111111000b ;we isolate bits 3-15 of B
        mov CL,16
        rol EAX, CL ;rotate to the left 16 positions
        or EBX, EAX ;we put the bits into the result  EBX->1100111010001111111101110001010b 1732770698d
        call [exit]