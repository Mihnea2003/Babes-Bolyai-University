bits 32

global start        

; declare extern functions used by the programme
extern exit, printf, scanf ; add printf and scanf as extern functions            
import exit msvcrt.dll    
import printf msvcrt.dll    ; tell the assembler that function printf is found in msvcrt.dll library
import scanf msvcrt.dll     ; similar for scanf
                          
segment data use32 class=data
    s DD 12345678h, 1A2B3C4Dh, 0FE98DC76h
    len equ ($-s)/4
    ten db 10
    d db 0
segment  code use32 class=code ; code segment
    start:
        mov ecx,len
        mov esi,s
        mov edi,d
        cld
        loop_1:
            lodsb
            lodsb    ;in al e numarul
            mov dl,al
            mov Ah,0         ;in ax e nr
            div byte[ten]    ;al e catul  ah e restul
            cmp ah,0
            jne final
                mov al,dl
                stosb
            final:
            lodsw
        loop loop_1
    call [exit]