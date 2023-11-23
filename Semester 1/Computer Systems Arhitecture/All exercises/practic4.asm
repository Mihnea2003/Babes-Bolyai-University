bits 32

global start        

; declare extern functions used by the programme
extern exit, printf, scanf ; add printf and scanf as extern functions            
import exit msvcrt.dll    
import printf msvcrt.dll    ; tell the assembler that function printf is found in msvcrt.dll library
import scanf msvcrt.dll     ; similar for scanf
                          
segment data use32 class=data
    a dd 0
    max dd 0
    message1 db "a=",0
    format db "%d",0
segment  code use32 class=code ; code segment
    start:
        citire:
            push dword message1
            call [printf]
            add esp,4
            
            push dword a
            push dword format
            call[scanf]
            add esp,4*2
            
            mov eax,[a]
            cmp eax,0
            je final
            cmp eax,[max]
            jbe nuebun
                mov [max],eax
            nuebun:
            jmp citire
        final:
        mov eax,[max]
        
        push eax
        push dword format
        call[printf]
        add esp,4*2
    call [exit]
            