bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
    ;unsigned
    s1 db 1,2,3,4,5,6,7,8,9,10
    lens1 equ $-s1   ;the length of s1
    two db 2
    s2 times lens1 dw 0 ;add digit 7 to each element of s1 17,27,37...
    sum db 0
    ten db 10
segment  code use32 class=code ; code segment
    start:
    
    ;construct s2 by adding digit 7 at the end of elements from s1
    
    mov ecx, lens1
    mov esi, 0   ;index for s1
    mov edi, 0   ;index for s2
    jecxz end_loop
    add_7:
        mov al, [s1+esi]
        mul byte[ten]   ;ax=al*10
        add AX, 7   ;ax=al*10+7
        cbw   ;al->ax signed
        mov [s2+edi], ax
        inc esi
        add edi, 2 ;because it is an array of words
    loop add_7
    end_loop:
    
    
    ;sum of even elements(bytes) in s1
    mov bl, 0 ;compute the sum of even here
    mov bh, 0  ;sum of odd
    mov ecx, lens1
    mov esi, 0
    jecxz skip_loop
    sum_loop:
        mov AL, [s1+esi]  ;s1[esi]
        mov ah, 0  ;al->ax 
        div byte [two]  ;al=ax/2  ah=ax%2
        cmp ah, 0
        jne donotadd
            add bl, [s1+esi] 
            jmp over_odd
        donotadd:
            add bh, [s1+esi]
        over_odd
        inc esi 
    loop sum_loop
    skip_loop:
    
    mov [sum], bl
    call [exit]
     std
        lodsw          ;AX->DS:ESI
        while_1:
        div byte [ten]  ;AL=AX/10   AH=AX%10
        mov [b+edi], AH
        add edi,1
        mov AH, 0
        cmp AX, 0
        ja while_1