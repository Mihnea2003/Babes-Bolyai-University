bits 32
global start

extern exit, printf, conversion ; add printf and scanf as extern functions            
import exit msvcrt.dll    
import printf msvcrt.dll    ; tell the assembler that function printf is found in msvcrt.dll library
import scanf msvcrt.dll     ; similar for scanf
segment data use32 class=data
	number dd 000111100111b       
    format1 db "%x", 0 ;hexa
    r dd 0
    
segment code use32 class=code
    start:
    ;main program
        mov edi,r
        push dword[number]
        call [conversion]
        add esp,4 * 1
        sub edi,4
        mov esi,edi
        std
        mov ebx,ecx
        print_the_string:
            lodsd
            cmp eax,-1
            je end_loop
            push eax
            push dword format1
            call [printf]
            add esp,4 * 2
        jmp print_the_string
        end_loop:
    call[exit]
                
                
    