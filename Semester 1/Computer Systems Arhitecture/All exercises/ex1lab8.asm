bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
    n dd 10
    m dd 7
    format db "i have %d ",0
segment  code use32 class=code ; code segment
    start:
    pushad ;saves all the registers on the stack
    push dword[m]
    push dword[n]
    push format
    call [printf]   ;eax
    add esp,4*3
    popad    ;for registers eax,edx,ecx
    ;https://www.cs.ubbcluj.ro/~alinacalin/ASC/Cresources.html
    call [exit]
    