bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  conversion 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
segment  code use32 class=code ; code segment
    conersion:
    ;the subprogram of ex1lab 10 wich convert a number from base 2 in base 16
    ;we use esi and ebx from the main program
    ;it returns every digit in base 16 in a string r
    ;modifies ecx,eax,ebx,esi
        mov ebx,[esp+4]
        mov ecx,0
        cld
        mov eax,-1
        stosd
        loop_1:
            mov eax,ebx
            and eax, 0xF ; Mask lower 4 bits
            ;add the digit in base 16
            stosd
            add ecx,1
            shr ebx, 4
        cmp ebx,0
        jne loop_1
    ret